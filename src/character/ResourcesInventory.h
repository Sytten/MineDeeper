// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// ResourcesInventory.h
// The header file of the ResourcesInventory object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#ifndef RESOURCESINVENTORY_H
#define RESOURCESINVENTORY_H

#include <map>
#include <string>

#include "../buildings/SellBuilding.h"
#include "../ServiceLocator.h"

class Character;

class ResourcesInventory
{
    public:
        ResourcesInventory();
        void removeResources();
        bool addResource(int blockID, std::string name, int price);

        struct Resource
        {
            public:
                int number;
                std::string name;
                int price;
        };

    private:
        bool full();
        unsigned m_maxResources;
        std::map<int, ResourcesInventory::Resource> m_resourcesList;
        std::map<int, ResourcesInventory::Resource>::iterator m_it;

    friend bool SellBuilding::enter(sfg::SFGUI &sfgui, sf::RenderWindow &window, Character *ptrCharacter);
    friend class Character;
};

#endif // RESOURCESINVENTORY_H
