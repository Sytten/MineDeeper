// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Artifacts.cpp
// Artifacts manages the artifacts that the player have found.
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 31/01/2013
// ---------------------------------------------------------------------------

#include "Artifacts.h"

Artifacts::Artifacts() : m_artifact1(false), m_artifact2(false), m_artifact3(false)
{
}

bool Artifacts::allFound()
{
// If all the artifacts are set to true, return true.
    if(m_artifact1 && m_artifact2 && m_artifact3)
        return true;

    return false;
}

void Artifacts::foundArtifact()
{
// Set a new artifact to true, we don't need to know which it is.
    if(!m_artifact1)
    {
        m_artifact1 = true;
        return;
    }

    if(!m_artifact2)
    {
        m_artifact2 = true;
        return;
    }

    if(!m_artifact3)
    {
        m_artifact3 = true;
        return;
    }
}
