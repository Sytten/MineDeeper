// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// IAudioProvider.h
// IAudioProvider is the interface for my sounds' providers. The parent class.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 07/04/2013
// ---------------------------------------------------------------------------

#ifndef IAUDIOPROVIDER_H
#define IAUDIOPROVIDER_H

#include <string>

class IAudioProvider
{
    public:
        IAudioProvider() : m_mute(false) {}
        virtual ~IAudioProvider() {}

        virtual void playSound(std::string filename, bool looping) = 0;
            virtual void playSound(std::string filename, int volume, bool looping) = 0;
        virtual void playSong(std::string filename, bool looping) = 0;
            virtual void playSong(std::string filename, int volume, bool looping) = 0;

        virtual void stopAllSounds() = 0;
        virtual void stopSounds() = 0;
        virtual void stopSound(std::string filename) = 0;
        virtual void stopSong() = 0;

        virtual bool isSoundPlaying() = 0;
        virtual bool isSoundPlaying(std::string filename) = 0;
        virtual bool isSongPlaying() = 0;
        virtual bool isSongPlaying(std::string filename) = 0;

        virtual void increaseVolume(float increase) = 0;
            virtual void increaseVolumeSounds(float increase) = 0;
            virtual void increaseVolumeSong(float increase) = 0;
        virtual void decreaseVolume(float decrease) = 0;
            virtual void decreaseVolumeSounds(float decrease) = 0;
            virtual void decreaseVolumeSong(float decrease) = 0;

        virtual void mute(bool state) = 0;
        bool isMuted() { return m_mute; }

    protected:
        bool m_mute;
};

#endif // IAUDIOPROVIDER_H
