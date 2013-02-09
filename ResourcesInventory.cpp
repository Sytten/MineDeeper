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

#include "ResourcesInventory.h"

ResourcesInventory::ResourcesInventory() : m_maxResources(20)
{
}

void ResourcesInventory::removeResources()
{
    m_resourcesList.clear();
}

void ResourcesInventory::addResource(int blockID)
{
    m_it = m_resourcesList.find(blockID);

    if(m_it != m_resourcesList.end())
    {
        int tempNum = (*m_it).second + 1;
        m_resourcesList[blockID] = tempNum;
    }

    else
        m_resourcesList[blockID] = 1;
}
