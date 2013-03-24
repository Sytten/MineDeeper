// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// UpgradeBuilding.cpp
// UpgradeBuilding manages the building where the player can repair is
// vehicule and buy upgrades.
//
// Author: Sytten
// Creation date: 11/03/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#include "UpgradeBuilding.h"
#include "../character/Character.h"

using namespace std;

UpgradeBuilding::UpgradeBuilding(sf::Vector2f const& windowSize, unsigned const& ID) : Building(ID), m_lifePrice(0.5f)
{
// Because we need our notebook to be able to fill it
    m_notebook = sfg::Notebook::Create();

// Open the configuration file
    ifstream upgradesFile("data/upgrades.config");

    if(upgradesFile.is_open() && !upgradesFile.eof())
    {
        try
        {
            unsigned lineError(1);
            vector<string> words;
            string line;
            string word;
            int lastTypeID(1000);
            int actualTypeID(1000);
            sfg::Box::Ptr horizontal;

            while(!upgradesFile.eof())
            {
                // Get a line in the configuration file
                    getline(upgradesFile, line);

                // If the line start with a # or \n or is empty, get a new one
                    while(line.at(0) == '#' || line.at(0) == '\n' || line.empty())
                    {
                        line.clear();
                        getline(upgradesFile, line);
                        ++lineError;
                    }

                // Erase the spaces and the tabs
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

                // Check each numbers in the line
                    while(line.length() != 0)
                    {
                        word = line.substr(0, line.find(';'));
                        line.erase(0, line.find(';')+1);
                        words.push_back(word);
                    }

                 // If we don't have enough words, stop the game
                    if(words.size() < 5)
                        throw runtime_error("Error in the upgrades configuration file");

                // Update the typeIDs
                    lastTypeID = actualTypeID;
                    actualTypeID = to_int(words.at(0));

                    if(actualTypeID != lastTypeID)
                    {
                        horizontal = sfg::Box::Create(sfg::Box::HORIZONTAL, 20.f);
                        m_notebook->AppendPage(horizontal, sfg::Label::Create(words.at(4)));
                    }

                // Create the Upgrade struct and fill it
                    UpgradeBuilding::Upgrade upgrade;

                    if(to_int(words.at(0)) > Property::Drill)
                        throw runtime_error("Error in the upgrades configuration file");

                    else
                        upgrade.upgradeType = static_cast<Property>(to_int(words.at(0)));

                        upgrade.level = to_int(words.at(1));
                        upgrade.price = to_int(words.at(2));

                // Create the objects and add them in the layouts
                    sf::Image image;
                        image.loadFromFile(words.at(3));
                    sfg::Image::Ptr imagePtr = sfg::Image::Create(image);
                    sfg::Label::Ptr text = sfg::Label::Create(words.at(2));
                    sfg::Button::Ptr buyButton = sfg::Button::Create("Buy");
                        buyButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::upgradeButtonClick, this );

                    sfg::Box::Ptr vertical = sfg::Box::Create(sfg::Box::VERTICAL, 10.f);
                        vertical->Pack(imagePtr, false);
                        vertical->Pack(text, false);
                        vertical->Pack(buyButton, false);

                    horizontal->Pack(vertical, false);

                // Insert the button in the map
                    m_upgrades.insert( std::pair<sfg::Button::Ptr, UpgradeBuilding::Upgrade>(buyButton, upgrade) );

                    words.clear();
                    ++lineError;
            }

            upgradesFile.close();
        }

        // If an exception occurred, close the file first and than rethrow it
            catch(std::exception &e)
            {
                upgradesFile.close();
                throw;
            }
    }

// Create all the other objects we need
    m_titleLabel = sfg::Label::Create("Upgrades Building");
        m_titleLabel->SetId("fuelTitleLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#fuelTitleLabel", "FontSize", 50.f);
    m_moneyLabel = sfg::Label::Create();
        m_moneyLabel->SetId("moneyLabel");
        sfg::Context::Get().GetEngine().SetProperty("Label#moneyLabel", "FontSize", 25.f);
    m_separator = sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL);
    m_lifeBar = sfg::ProgressBar::Create(sfg::ProgressBar::Orientation::HORIZONTAL);

    // Create the buttons
        m_5Button = sfg::Button::Create("5$");
            m_5Button->SetRequisition(sf::Vector2f(130,80));
            m_5Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::button5Click, this );

        m_10Button = sfg::Button::Create("10$");
            m_10Button->SetRequisition(sf::Vector2f(130,80));
            m_10Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::button10Click, this );

        m_25Button = sfg::Button::Create("25$");
            m_25Button->SetRequisition(sf::Vector2f(130,80));
            m_25Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::button25Click, this );

        m_50Button = sfg::Button::Create("50$");
            m_50Button->SetRequisition(sf::Vector2f(130,80));
            m_50Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::button50Click, this );

        m_fullButton = sfg::Button::Create("Full");
            m_fullButton->SetRequisition(sf::Vector2f(100,170));
            m_fullButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::fullButtonClick, this );

        m_exitButton = sfg::Button::Create("Exit");
            m_exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &UpgradeBuilding::exitButtonClick, this );
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

// Insert the objects in the layouts
    m_verticalButtonsLayout1 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
        m_verticalButtonsLayout1->Pack(m_5Button, false);
        m_verticalButtonsLayout1->Pack(m_25Button, false);

    m_verticalButtonsLayout2 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
        m_verticalButtonsLayout2->Pack(m_10Button, false);
        m_verticalButtonsLayout2->Pack(m_50Button, false);

    m_horizontalButtonsLayout = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 20.f);
        m_horizontalButtonsLayout->Pack(m_verticalButtonsLayout1, false);
        m_horizontalButtonsLayout->Pack(m_verticalButtonsLayout2, false);
        m_horizontalButtonsLayout->Pack(m_fullButton, false);

    m_mainVerticalLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
        m_mainVerticalLayout->Pack(m_titleLabel, false);
        m_mainVerticalLayout->Pack(m_notebook, false);
        m_mainVerticalLayout->Pack(m_moneyLabel, false);
        m_mainVerticalLayout->Pack(m_separator, false);
        m_mainVerticalLayout->Pack(m_lifeBar, false);
        m_mainVerticalLayout->Pack(m_horizontalButtonsLayout, false);
        m_mainVerticalLayout->Pack(m_exitButton, false);

// Set the properties of the labels
    sfg::Context::Get().GetEngine().SetProperty("Label", "FontName", "data/Eastwood.ttf");
    sfg::Context::Get().GetEngine().SetProperty("Label", "FontSize", 20.f);

// Create the window and add the main layout
    m_window = sfg::Window::Create(sfg::Window::BACKGROUND);
        m_window->Add(m_mainVerticalLayout);

// Set The position of the window in the middle of the screen
    m_window->SetPosition(sf::Vector2f( ((windowSize.x/2)-(m_window->GetRequisition().x/2)), ((windowSize.y/2) - (m_window->GetRequisition().y/2)) ));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UpgradeBuilding::enter(sfg::SFGUI& sfgui, sf::RenderWindow& window, Character *ptrCharacter)
{
// Check if the given pointer is null
    if(ptrCharacter == nullptr)
        throw std::runtime_error( "Problem with the character pointer in the fuel menu" ); //If so, throw an error

// Else, store it in the class
    else
        m_ptrCharacter = ptrCharacter;

// Set the money Label
    setMoneyLabel();

// Set the state of the buttons
    verifyButtonsState();

// Set the fraction of the life bar who's full
    m_lifeBar->SetFraction( m_ptrCharacter->getLife().fractionOfLifeFull() );

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

int UpgradeBuilding::to_int(std::string stringToConvert)
{
    int temp;
        m_converter.str(stringToConvert);
        m_converter >> temp;
        m_converter.str(string());
        m_converter.clear();

    return temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpgradeBuilding::setMoneyLabel()
{
// Clear stuff
    m_moneyString.clear();
    m_converter.str(std::string());
    m_converter.clear();

// Add the word money
    m_moneyString += "Money : ";

// Convert the int to a string and add it to the money string
    m_converter << m_ptrCharacter->getMoney().m_money;
    m_moneyString += m_converter.str();
    m_moneyLabel->SetText(m_moneyString); // Set the money label
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpgradeBuilding::moneyButtonClick( int life )
{
// Check if we can put all the life in the bar
    if(life > m_ptrCharacter->getLife().lifeNeededToBeFull())
        life = m_ptrCharacter->getLife().lifeNeededToBeFull(); // If we can't, put the max

// Check if the player have enough money
    if(m_ptrCharacter->getMoney().enoughMoney( life * m_lifePrice ))
    {
        // If yes, remove the money and add the life
            m_ptrCharacter->getMoney().removeMoney( life * m_lifePrice );
            m_ptrCharacter->getLife().addLife( life );
    }

    else
    {
        // Reduce by one the number of liter and check if the player can afford it
            for(int i(life); i > 0; i--)
            {
                if(m_ptrCharacter->getMoney().enoughMoney( i * m_lifePrice ))
                {
                    life = i;
                    break;
                }
            }
        // If we found a number greater than 0, remove the money and add the life
            if(life > 0)
            {
                m_ptrCharacter->getMoney().removeMoney( life * m_lifePrice );
                m_ptrCharacter->getLife().addLife( life );
            }
    }

// Set the fraction of the life bar who's full
    m_lifeBar->SetFraction( m_ptrCharacter->getLife().fractionOfLifeFull() );

// Set the money Label
    setMoneyLabel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpgradeBuilding::fullButtonClick()
{
// Get the life we need to add to be full
    int life = m_ptrCharacter->getLife().lifeNeededToBeFull();

// Check if the player have enough money
    if(m_ptrCharacter->getMoney().enoughMoney( (unsigned)(life * m_lifePrice) ))
    {
        // If yes, remove the money and add the life
            m_ptrCharacter->getMoney().removeMoney( (unsigned)(life * m_lifePrice) );
            m_ptrCharacter->getLife().addLife( life );
    }

    else
    {
        // Reduce by one the number of liter and check if the player can afford it
            for(int i(life); i > 0; i--)
            {
                if(m_ptrCharacter->getMoney().enoughMoney( (unsigned)(life * m_lifePrice) ))
                {
                    life = i;
                    break;
                }
            }
        // If we found a number greater than 0, remove the money and add the life
            if(life > 0)
            {
                m_ptrCharacter->getMoney().removeMoney( (unsigned)(life * m_lifePrice) );
                m_ptrCharacter->getLife().addLife( life );
            }
    }

// Set the fraction of the life bar who's full
    m_lifeBar->SetFraction( m_ptrCharacter->getLife().fractionOfLifeFull() );

// Set the money Label
    setMoneyLabel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpgradeBuilding::verifyButtonsState()
{
    for(std::map<sfg::Button::Ptr, Upgrade>::iterator iter(m_upgrades.begin()); iter != m_upgrades.end(); ++iter)
    {
        if(iter->second.upgradeType != Property::Engine && iter->second.level <= m_ptrCharacter->getProperty(iter->second.upgradeType))
            iter->first->SetState(sfg::Button::State::INSENSITIVE);

        if(iter->second.upgradeType == Property::Engine && iter->second.level >= m_ptrCharacter->getProperty(iter->second.upgradeType))
            iter->first->SetState(sfg::Button::State::INSENSITIVE);

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpgradeBuilding::upgradeButtonClick()
{
    for(std::map<sfg::Button::Ptr, Upgrade>::iterator iter(m_upgrades.begin()); iter != m_upgrades.end(); ++iter)
    {
        if(iter->first->GetState() == sfg::Button::State::ACTIVE)
        {
            if(m_ptrCharacter->getMoney().enoughMoney(iter->second.price))
            {
                m_ptrCharacter->getMoney().removeMoney(iter->second.price);
                m_ptrCharacter->setProperty(iter->second.upgradeType, iter->second.level);
            }
        }
    }
}
