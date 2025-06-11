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

private:
    sf::Music menuMusic;
    sf::SoundBuffer buttonClickBuffer;
    sf::Sound buttonClick;
    sf::SoundBuffer navigateBuffer;
    sf::Sound navigateSound;
    sf::SoundBuffer selectBuffer;
    sf::Sound selectSound;
};
