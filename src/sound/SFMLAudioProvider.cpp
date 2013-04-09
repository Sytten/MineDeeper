// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SFMLAudioProvider.cpp
// SFMLAudioProvider manages all the sounds in the game. It implements all the
// functions to play a song and multiple sounds at the same time.
//
// Author: Sytten
// Creation date: 05/04/2012
// Last modification date: 08/04/2013
// ---------------------------------------------------------------------------

#include "SFMLAudioProvider.h"

SFMLAudioProvider::SFMLAudioProvider() : m_currentSongName(""), m_volumeSounds(80), m_volumeSong(100)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::playSong(std::string songName, bool looping)
{
// Create a pointer to handle the music
    sf::Music* song;

// Try to load the music
    try
    {
        song = m_cache.getMusic(songName);
    }
    catch(SoundNotFoundException &e)
    {
        // We failed to load the song so display it in the console and exit
            std::cerr << "An exception occurred : " << e.what() << std::endl;
            return;
    }

// If it's not the same song, stop the previous one
    if(m_currentSongName != songName)
    {
        stopSong();
        m_currentSongName = songName;
    }

// Set the properties of the song
    song->setVolume(m_volumeSong);
    song->setLoop(looping);
    song->play();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::playSong(std::string filename, int volume, bool looping)
{
// When the player specify a volume
    m_volumeSong = volume;
    playSong(filename, looping);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::playSound(std::string soundName, bool looping)
{
// Check if there's a channel free to play the sound
    int availChannel = -1;
    int i(0);

    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        if(m_iterSounds->second.sound.getStatus() != sf::Sound::Playing)
        {
            availChannel = i;
            break;
        }
    }

// If we found channel
    if(availChannel != -1)
    {
        try
        {
            // Create the object sound that we'll store and set its properties
                SFMLAudioProvider::Sound sound;
                    sound.sound.setBuffer(m_cache.getSoundBuffer(soundName));
                    sound.sound.setLoop(looping);
                    sound.sound.setVolume(m_volumeSounds);
                    sound.name = soundName;

            // Store the sound
                m_sounds.erase(availChannel);
                m_iterSounds = m_sounds.insert(std::pair<int, SFMLAudioProvider::Sound>(availChannel, sound)).first;

            // Start the sound
                m_iterSounds->second.sound.play();
        }
        catch(SoundNotFoundException &e)
        {
            // We failed to load the sound so display it in the console and exit
                std::cerr << "An exception occurred : " << e.what() << std::endl;
                return;
        }
    }

// If we didn't find a channel, but the map isn't full
    else if(m_sounds.size() < MAX_SOUND_CHANNELS)
    {
        try
        {
            // Create the object sound that we'll store and set its properties
                SFMLAudioProvider::Sound sound;
                    sound.sound.setBuffer(m_cache.getSoundBuffer(soundName));
                    sound.sound.setLoop(looping);
                    sound.sound.setVolume(m_volumeSounds);
                    sound.name = soundName;
            // Store the sound
                m_iterSounds = m_sounds.insert(std::pair<int, SFMLAudioProvider::Sound>(m_sounds.size(), sound)).first;

            // Start the sound
                m_iterSounds->second.sound.play();
        }
        catch(SoundNotFoundException &e)
        {
            // We failed to load the sound so display it in the console and exit
                std::cerr << "An exception occurred : " << e.what() << std::endl;
                return;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::playSound(std::string filename, int volume, bool looping)
{
// When the player specify a volume
    m_volumeSounds = volume;
    playSound(filename, looping);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::stopSong()
{
// Check if we loaded a song
    if(m_currentSongName != "")
    {
        // Create the pointer ton handle the song
            sf::Music* song;

        // Try to find the song
            try
            {
                song = m_cache.getMusic(m_currentSongName);
                // If the song is playing, stop it
                    if(song->getStatus() != sf::Music::Stopped)
                        song->stop();
            }
            catch(SoundNotFoundException &e)
            {
                // We failed to stop the song, so just display it and do nothing
                    std::cerr << "An exception occurred : " << e.what() << std::endl;
            }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::stopSounds()
{
// Check each sound in the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // If the sound is playing, stop it
            if(m_iterSounds->second.sound.getStatus() != sf::Sound::Stopped)
                m_iterSounds->second.sound.stop();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::stopAllSounds()
{
// If the player wants to stop everything
    stopSounds();
    stopSong();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::stopSound(std::string soundName)
{
// Check each sound in the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // If it's the good sound and it's playing, stop it
            if(m_iterSounds->second.name == soundName)
            {
                if(m_iterSounds->second.sound.getStatus() != sf::Sound::Stopped)
                    m_iterSounds->second.sound.stop();
                break;
            }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SFMLAudioProvider::isSoundPlaying()
{
// Check each sound in the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // If a sound is playing, return true
            if(m_iterSounds->second.sound.getStatus() == sf::Sound::Playing)
                return true;
    }

// Return false because no sound is playing
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SFMLAudioProvider::isSoundPlaying(std::string soundName)
{
// Check each sound in the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // If the specified sound is playing, return true
            if(m_iterSounds->second.name == soundName && m_iterSounds->second.sound.getStatus() == sf::Sound::Playing)
                return true;
    }

// Return false because the specified sound isn't playing
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SFMLAudioProvider::isSongPlaying()
{
// If we loaded a song
    if(m_currentSongName != "")
    {
        // Return true if the status is set to playing, otherwise return false
            return m_cache.getMusic(m_currentSongName)->getStatus() == sf::Music::Playing;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SFMLAudioProvider::isSongPlaying(std::string songName)
{
// If the current song is the one specified
    if(m_currentSongName == songName)
    {
        // Return true if the status is set to playing, otherwise return false
            return m_cache.getMusic(m_currentSongName)->getStatus() == sf::Music::Playing;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::increaseVolume(float increase)
{
// If the player want to increase the volume of the song and the sounds
    increaseVolumeSounds(increase);
    increaseVolumeSong(increase);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::increaseVolumeSounds(float increase)
{
// Add the increase
    m_volumeSounds += increase;

// Check if more than 100
    if(m_volumeSounds > 100)
        m_volumeSounds = 100;

// Check each sound in the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // Set the new volume to each of them
            m_iterSounds->second.sound.setVolume(m_volumeSounds);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::increaseVolumeSong(float increase)
{
// Add the increase
    m_volumeSong += increase;

// Check if more than 100
    if(m_volumeSong > 100)
        m_volumeSong = 100;

// If we loaded a song
    if(m_currentSongName != "")
    {
        // Create a pointer to handle the song
            sf::Music* song;

        // Try to load the music and set the new volume
            try
            {
                song = m_cache.getMusic(m_currentSongName);
                song->setVolume(m_volumeSong);
            }
            catch(SoundNotFoundException &e)
            {
                // We failed to change the song's volume, so just display it and do nothing
                    std::cerr << "An exception occurred : " << e.what() << std::endl;
            }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::decreaseVolume(float decrease)
{
// If the player want to decrease the volume of the song and the sounds
    decreaseVolumeSounds(decrease);
    decreaseVolumeSong(decrease);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::decreaseVolumeSounds(float decrease)
{
// Remove the decrease
    m_volumeSounds -= decrease;

// Check if less than 0
    if(m_volumeSounds < 0)
        m_volumeSounds = 0;

// Check each sound the map
    int i(0);
    for(m_iterSounds = m_sounds.begin(), i = 0; m_iterSounds != m_sounds.end() && i < MAX_SOUND_CHANNELS; ++m_iterSounds, ++i)
    {
        // Set the new volume to each of them
            m_iterSounds->second.sound.setVolume(m_volumeSounds);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SFMLAudioProvider::decreaseVolumeSong(float decrease)
{
// Remove the decrease
    m_volumeSong -= decrease;

// Check if less than 0
    if(m_volumeSong < 0)
        m_volumeSong = 0;

// If we loaded a song
    if(m_currentSongName != "")
    {
        // Create a pointer to handle the song
            sf::Music* song;

        // Try to load the music and set the new volume
            try
            {
                song = m_cache.getMusic(m_currentSongName);
                song->setVolume(m_volumeSong);
            }
            catch(SoundNotFoundException &e)
            {
                // We failed to change the song's volume, so just display it and do nothing
                    std::cerr << "An exception occurred : " << e.what() << std::endl;
            }
    }
}
