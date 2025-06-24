#include "SoundManager.h"
#include <stdexcept>

SoundManager::SoundManager() {
    // Música del menú
    if (!menuMusic.openFromFile("Assets/Sound-Music/Music/mix2.ogg")) {
        throw std::runtime_error("No se pudo cargar la música del menú.");
    }
    menuMusic.setLoop(true);

    // Sonido de selección (Enter)
    if (!buttonClickBuffer.loadFromFile("Assets/Sound-Music/Sounds/select.wav")) {
        throw std::runtime_error("No se pudo cargar select.wav.");
    }
    buttonClick.setBuffer(buttonClickBuffer);
    selectSound = buttonClick;  //  opcional si querés compartirlo

    // Sonido de navegación (W/S)
    if (!navigateBuffer.loadFromFile("Assets/Sound-Music/Sounds/selectMove.wav")) {
        throw std::runtime_error("No se pudo cargar selectMove.wav.");
    }
    navigateSound.setBuffer(navigateBuffer);
}

void SoundManager::playMenuMusic() {
    menuMusic.play();
}

void SoundManager::stopMenuMusic() {
    menuMusic.stop();
}

void SoundManager::playSoundEffect(const std::string& soundName) {
    if (!soundEffectsEnabled) return;  // Evita reproducir sonidos si están desactivados

    if (soundName == "navigate") {
        navigateSound.play();
    } else if (soundName == "select") {
        selectSound.play();
    }
}

void SoundManager::setSoundEffectsEnabled(bool enabled) {
    soundEffectsEnabled = enabled;  // Cambia el estado de los efectos de sonido
}

