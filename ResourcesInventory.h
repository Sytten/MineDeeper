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
// Last modification date: 01/02/2013
// ---------------------------------------------------------------------------

#include <map>

#ifndef RESSOURCESINVENTORY_H
#define RESSOURCESINVENTORY_H

class ResourcesInventory
{
    public:
        ResourcesInventory();
        void setMaxResources(int maxResources) { m_maxResources = maxResources; }
        void removeResources();
        void addResource(int blockID);

    private:
        bool checkFull();
        unsigned m_maxResources;
        std::map<int, int> m_resourcesList;
        std::map<int,int>::iterator m_it;
};

#endif // RESSOURCESINVENTORY_H
