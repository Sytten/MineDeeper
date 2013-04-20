// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SFMLAudioProvider.h
// The header file of the SFMLAudioProvider object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 08/04/2013
// ---------------------------------------------------------------------------

#ifndef SFMLAUDIOPROVIDER_H
#define SFMLAUDIOPROVIDER_H

#include <string>
#include <iostream>

#include <SFML\Audio.hpp>

#include "SFMLAudioCache.h"
#include "IAudioProvider.h"

class SFMLAudioProvider : public IAudioProvider
{
    public:
        SFMLAudioProvider();

        void playSong(std::string songName, bool looping = false);
            void playSong(std::string filename, int volume, bool looping = false);
        void playSound(std::string soundName, bool looping = false);
            void playSound(std::string filename, int volume, bool looping = false);

        void stopAllSounds();
        void stopSounds();
        void stopSound(std::string soundName);
        void stopSong();

        bool isSoundPlaying();
        bool isSoundPlaying(std::string soundName);
        bool isSongPlaying();
        bool isSongPlaying(std::string songName);

        void increaseVolume(float increase);
            void increaseVolumeSounds(float increase);
            void increaseVolumeSong(float increase);
        void decreaseVolume(float decrease);
            void decreaseVolumeSounds(float decrease);
            void decreaseVolumeSong(float decrease);

        void mute(bool state);

    private:
        struct Sound
        {
            sf::Sound sound;
            std::string name;
        };

        static const int MAX_SOUND_CHANNELS = 5;

        std::map<unsigned, SFMLAudioProvider::Sound> m_sounds;
        std::map<unsigned, SFMLAudioProvider::Sound>::iterator m_iterSounds;
        std::string m_currentSongName;
        SFMLAudioCache m_cache;
        float m_volumeSounds;
        float m_volumeSong;
};

#endif // SFMAUDIOPROVIDER_H
