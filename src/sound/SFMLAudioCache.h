// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SFMLAudioCache.h
// The header file of the SFMLAudioCache object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 08/04/2013
// ---------------------------------------------------------------------------

#ifndef SFMLAUDIOCACHE_H
#define SFMLAUDIOCACHE_H

#include <map>
#include <string>

#include <SFML\Audio.hpp>

#include "../exceptions/SoundNotFoundException.h"

class SFMLAudioCache
{
    public:
        ~SFMLAudioCache();

        sf::SoundBuffer const& getSoundBuffer(std::string soundName);
        sf::Music* getMusic(std::string songName);

    private:
        static std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
        static std::map<std::string, sf::Music*> m_musics;

        template <typename T>
        struct Deallocator
        {
            void operator()(const std::pair<std::string,T> &p)
            {
                delete p.second;
            }
        };
};

#endif // SFMLAUDIOCACHE_H
