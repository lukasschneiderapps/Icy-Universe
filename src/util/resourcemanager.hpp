#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	sf::Font *getFont(std::string fontName);
	sf::Texture *getTexture(std::string textureName);
	sf::Sound *getSound(std::string soundName);

private:
	void loadTextures(bool delete_);
	void loadFonts(bool delete_);
	void loadSounds(bool delete_);

private:
	std::map<std::string, sf::Texture *> textures;

private:
	std::map<std::string, sf::Font *> fonts;

private:
	std::map<std::string, sf::Sound *> sounds;
};

