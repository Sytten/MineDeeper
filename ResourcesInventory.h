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
// Last modification date: 01/03/2013
// ---------------------------------------------------------------------------

#ifndef RESOURCESINVENTORY_H
#define RESOURCESINVENTORY_H

#include <map>
#include <string>

#include "SellBuilding.h"

class ResourcesInventory
{
    public:
        ResourcesInventory();
        void setMaxResources(int maxResources) { m_maxResources = maxResources; }
        void removeResources();
        void addResource(int blockID, std::string name, int price);
        void display();

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
};

#endif // RESOURCESINVENTORY_H
