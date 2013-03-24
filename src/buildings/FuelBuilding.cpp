// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FuelBuilding.cpp
// FuelBuilding manages the building where the player can buy fuel.
//
// Author: Sytten
// Creation date: 21/02/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#include "FuelBuilding.h"
#include "../character/Character.h"
#include "../exceptions/ImageException.h"

FuelBuilding::FuelBuilding(sf::Vector2f const& windowSize, unsigned const& ID) : Building(ID), m_fuelPrice(1), m_wantToExit(false), m_ptrCharacter(nullptr)
{
// Temporary
    m_tank = sfg::ProgressBar::Create(sfg::ProgressBar::HORIZONTAL);

// Create the buttons
    m_5Button = sfg::Button::Create("5$");
        m_5Button->SetRequisition(sf::Vector2f(130,80));
        m_5Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::button5Click, this );

    m_10Button = sfg::Button::Create("10$");
        m_10Button->SetRequisition(sf::Vector2f(130,80));
        m_10Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::button10Click, this );

    m_25Button = sfg::Button::Create("25$");
        m_25Button->SetRequisition(sf::Vector2f(130,80));
        m_25Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::button25Click, this );

    m_50Button = sfg::Button::Create("50$");
        m_50Button->SetRequisition(sf::Vector2f(130,80));
        m_50Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::button50Click, this );

    m_fullButton = sfg::Button::Create("Full");
        m_fullButton->SetRequisition(sf::Vector2f(200,80));
        m_fullButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::fullButtonClick, this );

    m_exitButton = sfg::Button::Create("Exit");
        m_exitButton->SetRequisition(sf::Vector2f(80,80));
        m_exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &FuelBuilding::exitButton, this);
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

// Set the properties of the buttons
    sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 25.f);
    sfg::Context::Get().GetEngine().SetProperty("Button", "FontName", "data/Eastwood.ttf");

// Create the labels and set their properties
    m_titleLabel = sfg::Label::Create("Fuel Station");
        m_titleLabel->SetId("fuelTitleLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#fuelTitleLabel", "FontSize", 50.f);
        sfg::Context::Get().GetEngine().SetProperty("Label", "FontName", "data/Eastwood.ttf");

    m_moneyLabel = sfg::Label::Create();
        m_moneyLabel->SetId("moneyLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#moneyLabel", "FontSize", 25.f);

// Load the pump image
    if(!m_fuelPumpImage.loadFromFile("data/pump.png"))
        throw ImageException("pump.png");

        m_fuelPump = sfg::Image::Create(m_fuelPumpImage);

    // For future implementation
    /*m_mainTable = sfg::Table::Create();
        m_mainTable->Attach(m_fuelPump, sf::Rect<sf::Uint32>(0, 0, 1, 3), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_5Button, sf::Rect<sf::Uint32>(1, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_10Button, sf::Rect<sf::Uint32>(2, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_25Button, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_50Button, sf::Rect<sf::Uint32>(2, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_fullButton, sf::Rect<sf::Uint32>(1, 2, 2, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));
        m_mainTable->Attach(m_exitButton, sf::Rect<sf::Uint32>(2, 3, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ));*/

// Create all the layouts
    // Buttons layouts
        m_buttonHorizontalLayout1 = sfg::Box::Create(sfg::Box::HORIZONTAL, 30.f);
            m_buttonHorizontalLayout1->Pack(m_5Button);
            m_buttonHorizontalLayout1->Pack(m_10Button);

        m_buttonHorizontalLayout2 = sfg::Box::Create(sfg::Box::HORIZONTAL, 30.f);
            m_buttonHorizontalLayout2->Pack(m_25Button);
            m_buttonHorizontalLayout2->Pack(m_50Button);

        m_buttonVerticalLayout = sfg::Box::Create(sfg::Box::VERTICAL, 20.f);
            m_buttonVerticalLayout->Pack(m_buttonHorizontalLayout1);
            m_buttonVerticalLayout->Pack(m_buttonHorizontalLayout2);
            m_buttonVerticalLayout->Pack(m_fullButton);
            m_buttonVerticalLayout->Pack(m_exitButton);

    // Main horizontal layout (pump image + buttons)
        m_mainHorizontalLayout = sfg::Box::Create(sfg::Box::HORIZONTAL, 30.f);
            m_mainHorizontalLayout->Pack(m_fuelPump);
            m_mainHorizontalLayout->Pack(m_buttonVerticalLayout);

    // Main vertical layout
        m_mainVerticalLayout = sfg::Box::Create(sfg::Box::VERTICAL, 20.f);
            m_mainVerticalLayout->Pack(m_titleLabel, false);
            m_mainVerticalLayout->Pack(m_tank, false);
            m_mainVerticalLayout->Pack(m_moneyLabel, false);
            m_mainVerticalLayout->Pack(m_mainHorizontalLayout, false);

// Create the window and add the main layout
    m_window = sfg::Window::Create(sfg::Window::BACKGROUND);
        m_window->Add(m_mainVerticalLayout);

// Set The position of the window in the middle of the screen
    m_window->SetPosition(sf::Vector2f( ((windowSize.x/2)-(m_window->GetRequisition().x/2)), ((windowSize.y/2) - (m_window->GetRequisition().y/2)) ));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FuelBuilding::enter(sfg::SFGUI& sfgui, sf::RenderWindow& window, Character *ptrCharacter)
{
// Check if the given pointer is null
    if(ptrCharacter == nullptr)
        throw std::runtime_error( "Problem with the character pointer in the fuel menu" ); //If so, throw an error

// Else, store it in the class
    else
        m_ptrCharacter = ptrCharacter;

// Set the fraction of the tank who's full
    m_tank->SetFraction( m_ptrCharacter->getFuel().fractionOfFuelFull() );

// Set the money Label
    setMoneyLabel();

// Create an event and clock object
    sf::Event event;
    sf::Clock clock;

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

// Set the member pointer to null to avoid memory leaks
    m_ptrCharacter = nullptr;

// Don't show the gui window
    m_window->Show(false);

// Return true, we want to continue the game
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FuelBuilding::moneyButtonClick(int liters)
{
// Check if we can put all the liters in the tank
    if(liters > m_ptrCharacter->getFuel().fuelNeededToBeFull())
        liters = m_ptrCharacter->getFuel().fuelNeededToBeFull(); // If we can't, put the max

// Check if the player have enough money
    if(m_ptrCharacter->getMoney().enoughMoney( (liters * m_fuelPrice) ))
    {
        // If yes, remove the money and add the fuel
            m_ptrCharacter->getMoney().removeMoney( (liters * m_fuelPrice) );
            m_ptrCharacter->getFuel().addFuel(liters);
    }

    else
    {
        // Reduce by one the number of liter and check if the player can afford it
            for(int i(liters); i > 0; i--)
            {
                if(m_ptrCharacter->getMoney().enoughMoney( (i * m_fuelPrice) ))
                {
                    liters = i;
                    break;
                }
            }
        // If we found a number greater than 0, remove the money and add the fuel
            if(liters > 0)
            {
                m_ptrCharacter->getMoney().removeMoney( (liters * m_fuelPrice) );
                m_ptrCharacter->getFuel().addFuel(liters);
            }
    }

// Set the fraction of the tank who's full
    m_tank->SetFraction( m_ptrCharacter->getFuel().fractionOfFuelFull() );

// Set the money Label
    setMoneyLabel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FuelBuilding::fullButtonClick()
{
// Get the number of liters we need to add to be full
    int liters = m_ptrCharacter->getFuel().fuelNeededToBeFull();

// Check if the player have enough money
    if(m_ptrCharacter->getMoney().enoughMoney( (liters * m_fuelPrice) ))
    {
        // If yes, remove the money and add the fuel
            m_ptrCharacter->getMoney().removeMoney( (liters * m_fuelPrice) );
            m_ptrCharacter->getFuel().addFuel(liters);
    }

    else
    {
        // Reduce by one the number of liter and check if the player can afford it
            for(int i(liters); i > 0; i--)
            {
                if(m_ptrCharacter->getMoney().enoughMoney( (i * m_fuelPrice) ))
                {
                    liters = i;
                    break;
                }
            }
        // If we found a number greater than 0, remove the money and add the fuel
            if(liters > 0)
            {
                m_ptrCharacter->getMoney().removeMoney( (liters * m_fuelPrice) );
                m_ptrCharacter->getFuel().addFuel(liters);
            }
    }

// Set the fraction of the tank who's full
    m_tank->SetFraction( m_ptrCharacter->getFuel().fractionOfFuelFull() );

// Set the money Label
    setMoneyLabel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FuelBuilding::setMoneyLabel()
{
// Clear stuff
    m_money.clear();
    m_converter.str(std::string());

// Add the word money
    m_money += "Money : ";

// Convert the int to a string and add it to the money string
    m_converter << m_ptrCharacter->getMoney().m_money;
    m_money += m_converter.str();
    m_moneyLabel->SetText(m_money); // Set the money label
}
