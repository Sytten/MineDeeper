// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SellBuilding.cpp
// SellBuilding manages the building where the player can sell his ores.
//
// Author: Sytten
// Creation date: 23/02/2013
// Last modification date: 09/03/2013
// ---------------------------------------------------------------------------

#include <sstream>

#include "SellBuilding.h"
#include "Character.h"
#include "ImageException.h"
#include "ResourcesInventory.h"

using namespace std;

SellBuilding::SellBuilding(sf::Vector2f const& windowSize, unsigned const& ID): Building(ID), m_wantToExit(false), m_totalToSell(0), m_ptrCharacter(nullptr)
{
// Create the labels and set their properties
    m_titleLabel = sfg::Label::Create("Stock exchange");
        m_titleLabel->SetId("sellTitleLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#sellTitleLabel", "FontSize", 50.f);
    m_moneyLabel = sfg::Label::Create("Money : 0");
        m_moneyLabel->SetId("moneyLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#moneyLabel", "FontSize", 25.f);

// Set the font of the labels
    sfg::Context::Get().GetEngine().SetProperty("Label", "FontName", "data/Eastwood.ttf");
    sfg::Context::Get().GetEngine().SetProperty("Label", "FontSize", 20.f);

// Create the buttons
    m_exitButton = sfg::Button::Create("Exit");
    {
        sf::Image closeImage;
        if(closeImage.loadFromFile("data/delete.png"))
        {
            sfg::Image::Ptr image(sfg::Image::Create(closeImage));
            m_exitButton->SetImage(image);
        }
        else
            throw ImageException("delete.png");
    }
        m_exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &SellBuilding::exitButtonClick, this );

    m_sellButton = sfg::Button::Create("Sell");
        m_sellButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &SellBuilding::sellButtonClick, this );

// Set the properties of the buttons
    sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 25.f);
    sfg::Context::Get().GetEngine().SetProperty("Button", "FontName", "data/Eastwood.ttf");
    m_sellButton->SetRequisition(sf::Vector2f(130,80));

// Align the sell button
    m_sellButtonAlignment = sfg::Alignment::Create();
        m_sellButtonAlignment->Add( m_sellButton );
        m_sellButtonAlignment->SetScale( sf::Vector2f( .0f, .0f) );
        m_sellButtonAlignment->SetAlignment( sf::Vector2f( 1.0f, .0f ) );

    m_horizontalAlignmentLayout = sfg::Box::Create( sfg::Box::HORIZONTAL );
        m_horizontalAlignmentLayout->Pack(m_sellButtonAlignment, true, true);

// Create the main frame
    m_mainFrame = sfg::Frame::Create("Ressources");
        m_mainFrame->SetAlignment( sf::Vector2f( .5f, .0f ) );
        m_mainFrame->SetRequisition(sf::Vector2f(600.f, 300.f));

// Create the main layout
    m_mainVerticalLayout = sfg::Box::Create( sfg::Box::VERTICAL, 20 );
        m_mainVerticalLayout->Pack(m_titleLabel, false);
        m_mainVerticalLayout->Pack(m_moneyLabel, false);
        m_mainVerticalLayout->Pack(m_mainFrame, false);
        m_mainVerticalLayout->Pack(m_horizontalAlignmentLayout, false);
        m_mainVerticalLayout->Pack(m_exitButton, false);

// Create the window and add the main layout
    m_window = sfg::Window::Create(sfg::Window::BACKGROUND);
        m_window->Add(m_mainVerticalLayout);

// Set The position of the window in the middle of the screen
    m_window->SetRequisition(sf::Vector2f(600.f, 600.f));
    m_window->SetPosition(sf::Vector2f( ((windowSize.x/2)-(m_window->GetRequisition().x/2)), ((windowSize.y/2) - (m_window->GetRequisition().y/2)) ));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SellBuilding::enter(sfg::SFGUI &sfgui, sf::RenderWindow &window, Character *ptrCharacter)
{
// Check if the given pointer is null
    if(ptrCharacter == nullptr)
        throw std::runtime_error( "Problem with the character pointer in the fuel menu" ); //If so, throw an error

// Else, store it in the class
    else
        m_ptrCharacter = ptrCharacter;

// Create our list of resources
    std::map<int, ResourcesInventory::Resource> resourcesList;

// Get the new resources list
    resourcesList = m_ptrCharacter->getResourcesInventory().m_resourcesList;

// Only do if the list is not empty
    if(!resourcesList.empty())
    {
        // Create the layouts
            sfg::Box::Ptr namesLayout =  sfg::Box::Create(sfg::Box::VERTICAL, 10.f);
            sfg::Box::Ptr pricesLayout =  sfg::Box::Create(sfg::Box::VERTICAL, 10.f);
            sfg::Box::Ptr mainHorizontalLayout = sfg::Box::Create(sfg::Box::HORIZONTAL, 50.f);
                mainHorizontalLayout->Pack(namesLayout, false);
                mainHorizontalLayout->Pack(pricesLayout, false);
            m_mainFrame->Add(mainHorizontalLayout);

        // Create our string and converter
            sf::String tempString;
            std::stringstream converter;

        // Create all the labels and add them in the layouts
            for(map<int, ResourcesInventory::Resource>::iterator it (resourcesList.begin()); it != resourcesList.end(); ++it)
            {
                // Create the name (name + number)
                    tempString = it->second.name;
                    tempString += " X ";
                    converter << it->second.number; // Convert the int to a string
                    tempString += converter.str();
                    {
                        // Create a label and add it to the layout
                            sfg::Label::Ptr name = sfg::Label::Create(tempString);
                            namesLayout->Pack(name, false);
                    }
                    converter.str(std::string()); // Flush the buffers
                    tempString.clear();

                // Create the price layout
                    converter << it->second.price; // Convert the int to a string
                    tempString = converter.str();
                    tempString += "$";
                    {
                        // Create a label and add it to the layout
                            sfg::Label::Ptr price = sfg::Label::Create(tempString);
                            pricesLayout->Pack(price, false);
                    }
                    converter.str(std::string()); // Flush the buffers
                    tempString.clear();

                // Add the price to the total
                    m_totalToSell += (it->second.number * it->second.price);
            }

        // Display the total
            sfg::Separator::Ptr separator = sfg::Separator::Create();
            pricesLayout->Pack(separator, false);

            converter << m_totalToSell; // Convert the int to a string
            tempString = converter.str();
            tempString += "$";
            {
                // Create a label and add it to the layout
                    sfg::Label::Ptr total = sfg::Label::Create(tempString);
                    pricesLayout->Pack(total, false);
            }
            converter.str(std::string()); // Flush the buffers
            tempString.clear();
    }

// Create an event and clock object
    sf::Event event;
    sf::Clock clock;

// Set the money Label
    setMoneyLabel();

// Be sure m_wanToQuit is set to false
    m_wantToExit = false;

// Show the gui window
    m_window->Show(true);

    while ( !m_wantToExit )
    {
		while ( window.pollEvent( event ) )
        {
			// Handle events
                m_window->HandleEvent( event );

			// Close window, return false to close the app properly
                if ( event.type == sf::Event::Closed )
                    return false;
		}

		// Update the GUI
            m_window->Update( clock.restart().asSeconds() );

		// Draw the GUI, but don't clear the screen!
            sfgui.Display( window );

		// Update the window
            window.display();
	}

// Reset the pointer to null
    m_ptrCharacter = nullptr;

// Don't show the gui window
    m_window->Show(false);

// Return true, we want to continue the game
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SellBuilding::sellButtonClick()
{
// Add the money to the player
    m_ptrCharacter->getMoney().addMoney(m_totalToSell);

// Clear the resources
    m_ptrCharacter->getResourcesInventory().removeResources();

// Destroy the labels
    m_mainFrame->RemoveAll();

// Set the money Label
    setMoneyLabel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SellBuilding::setMoneyLabel()
{
// Clear stuff
    m_money.clear();
    m_converter.str(std::string());
    m_converter.clear();

// Add the word money
    m_money += "Money : ";

// Convert the int to a string and add it to the money string
    m_converter << m_ptrCharacter->getMoney().m_money;
    m_money += m_converter.str();
    m_moneyLabel->SetText(m_money); // Set the money label
}
