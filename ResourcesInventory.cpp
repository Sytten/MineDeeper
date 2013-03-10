// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// ResourcesInventory.cpp
// ResourcesInventory manages the resources
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 01/02/2013
// ---------------------------------------------------------------------------

#include <iostream>

#include "ResourcesInventory.h"

ResourcesInventory::ResourcesInventory() : m_maxResources(20)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ResourcesInventory::removeResources()
{
    m_resourcesList.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ResourcesInventory::addResource(int blockID, std::string name, int price)
{
    if(!full())
    {
        m_it = m_resourcesList.find(blockID);

        if(m_it != m_resourcesList.end())
        {
            int tempNum = m_it->second.number + 1;
            m_resourcesList.at(blockID).number = tempNum;
        }

        else
        {
            ResourcesInventory::Resource ressource;
                ressource.number = 1;
                ressource.name = name;
                ressource.price = price;

            m_resourcesList[blockID] = ressource;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ResourcesInventory::full()
{
    int total(0);

    for(m_it = m_resourcesList.begin(); m_it != m_resourcesList.end(); ++m_it)
        total += m_it->second.number;

    if(total >= m_maxResources)
        return true;

    else
        return false;
}
