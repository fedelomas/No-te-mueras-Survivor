#pragma once
#include <SFML/Audio.hpp>
#include <string>

class SoundManager
{
public:
    SoundManager();
    void playMenuMusic();
    void stopMenuMusic();
    void playSoundEffect(const std::string& soundName);
    void setSoundEffectsEnabled(bool enabled);
    void setMenuMusicEnabled(bool enabled);
    void playGameplayMusic();
    void stopGameplayMusic();
    void setGameplayMusicEnabled(bool enabled);


private:
    sf::Music menuMusic;
    sf::Music gameplayMusic;
    sf::SoundBuffer buttonClickBuffer;
    sf::Sound buttonClick;
    sf::SoundBuffer navigateBuffer;
    sf::Sound navigateSound;
    sf::SoundBuffer selectBuffer;
    sf::Sound selectSound;

    bool soundEffectsEnabled = true;

};
