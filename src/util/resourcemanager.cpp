#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{
	loadTextures(false);
	loadFonts(false);
	loadSounds(false);
}

ResourceManager::~ResourceManager()
{
	/* free memory */
	loadTextures(true);
	loadFonts(true);
	loadSounds(true);
}

void ResourceManager::loadTextures(bool delete_)
{
	std::string texturesToLoad[] = { "background_sky", "background_menu", "tiles", "player_collider_floor", "button_start" };

	for (std::string textureToLoad : texturesToLoad)
	{
		if (delete_)
		{
			sf::Texture *textureToDelete = textures[textureToLoad];
			delete textureToDelete;
		}
		else
		{
			sf::Texture *targetTexture = new sf::Texture();
			if (!targetTexture->loadFromFile("gfx/" + textureToLoad + ".png"))
			{
				std::cerr << "Failed to load texture: " << textureToLoad << std::endl;
				exit(-1);
			}
			targetTexture->setSmooth(true);
			textures[textureToLoad] = targetTexture;
		}
	}

	if (delete_)
	{
		textures.clear();
	}
}

void ResourceManager::loadFonts(bool delete_)
{
	std::string fontsToLoad[] = { "Hanken-Book" };

	for (std::string fontToLoad : fontsToLoad)
	{
		if (delete_)
		{
			sf::Font *fontToDelete = fonts[fontToLoad];
			delete fontToDelete;
		}
		else {
			sf::Font *targetFont = new sf::Font();
			if (!targetFont->loadFromFile("fnt/" + fontToLoad + ".ttf"))
			{
				std::cerr << "Failed to load font: " << fontToLoad << std::endl;
			}
			fonts[fontToLoad] = targetFont;
		}
	}

	if (delete_)
	{
		fonts.clear();
	}
}

void ResourceManager::loadSounds(bool delete_)
{
	std::string soundsToLoad[] = { "on_collision_star", "game_finish", "game_reset", "button_click", "block_bouncy_jump", "speed_up" };

	for (std::string soundToLoad : soundsToLoad)
	{
		if (delete_)
		{
			/*sf::Sound *soundToDelete = sounds[soundToLoad];
			delete soundToDelete->getBuffer();
			delete soundToDelete;*/
		}
		else
		{
			/*sf::SoundBuffer *targetSoundBuffer = new sf::SoundBuffer();
			if (!targetSoundBuffer->loadFromFile("sfx/" + soundToLoad + ".wav"))
			{
				std::cerr << "Failed to load sound buffer: " << soundToLoad << std::endl;
			}
			sf::Sound *targetSound = new sf::Sound();
			targetSound->setBuffer(*targetSoundBuffer);
			sounds[soundToLoad] = targetSound;*/

		}
	}

	if (delete_)
	{
		sounds.clear();
	}
}

/* getters for resources */
sf::Font *ResourceManager::getFont(std::string fontName) { return fonts[fontName]; }
sf::Texture*ResourceManager::getTexture(std::string textureName) { return textures[textureName]; }
sf::Sound *ResourceManager::getSound(std::string soundName) { return sounds[soundName]; }
