// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SFMLAudioCache.cpp
// SFMLAudioCache manages soundBuffer and music objects. It loads them when
// necessary and free them.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 07/04/2013
// ---------------------------------------------------------------------------

#include "SFMLAudioCache.h"

SFMLAudioCache::~SFMLAudioCache()
{
    std::for_each(m_soundBuffers.begin(),m_soundBuffers.end(),Deallocator<sf::SoundBuffer*>());
    std::for_each(m_musics.begin(),m_musics.end(),Deallocator<sf::Music*>());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::SoundBuffer const& SFMLAudioCache::getSoundBuffer(std::string soundName)
{
    std::map<std::string, sf::SoundBuffer*>::iterator iter = m_soundBuffers.find(soundName);

    if(iter == m_soundBuffers.end())
    {
        sf::SoundBuffer *soundBuffer = new sf::SoundBuffer;
        if(!soundBuffer->loadFromFile("data/" + soundName))
        {
            delete soundBuffer;
            throw SoundNotFoundException(soundName);
        }
        else
        {
            m_soundBuffers.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer));
            return *soundBuffer;
        }
    }

    else
        return *iter->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Music* SFMLAudioCache::getMusic(std::string songName)
{
    std::map<std::string, sf::Music*>::iterator iter = m_musics.find(songName);

    if(iter == m_musics.end())
    {
        sf::Music *song = new sf::Music;
        if(!song->openFromFile("data/" + songName))
        {
            delete song;
            throw SoundNotFoundException(songName);
        }
        else
        {
            iter = m_musics.insert(std::pair<std::string, sf::Music*>(songName, song)).first;
            return iter->second;
        }
    }

    else
        return iter->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::map<std::string, sf::SoundBuffer*> SFMLAudioCache::m_soundBuffers;
std::map<std::string, sf::Music*> SFMLAudioCache::m_musics;
