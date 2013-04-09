// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// ServiceLocator.cpp
// ServiceLocator gives us the possibility to access our audio provider
// everywhere.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 08/04/2013
// ---------------------------------------------------------------------------

#include "ServiceLocator.h"

IAudioProvider* ServiceLocator::m_audioProvider = NULL;
