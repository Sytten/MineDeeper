// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Artifacts.h
// The header file of the Artifacts object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 31/01/2013
// ---------------------------------------------------------------------------

#ifndef ARTIFACTS_H
#define ARTIFACTS_H

class Artifacts
{
    public:
        Artifacts();
        bool allFound();
        void foundArtifact();

    private:
        bool m_artifact1;
        bool m_artifact2;
        bool m_artifact3;
};

#endif // ARTIFACTS_H
