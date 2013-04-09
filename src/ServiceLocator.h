// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// ServiceLocator.h
// The header file of the ServiceLocator object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 7/04/2013
// ---------------------------------------------------------------------------

#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include "sound/IAudioProvider.h"

class ServiceLocator
{
    public:
      static IAudioProvider* GetAudio() { return m_audioProvider; } const

      static void RegisterServiceLocator(IAudioProvider *provider)
      {
        m_audioProvider = provider;
      }

    private:
      static IAudioProvider * m_audioProvider;
};

#endif // SERVICELOCATOR_H
