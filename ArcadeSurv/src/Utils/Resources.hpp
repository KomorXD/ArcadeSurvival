#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

#include <mutex>

struct Resources
{
	public:
		bool LoadTexture(const std::string& name);
		bool LoadSoundBuffer(const std::string& name);
		bool LoadFont(const std::string& name);

		sf::Texture*	 GetTexture(const std::string& name);
		sf::SoundBuffer* GetSoundBuffer(const std::string& name);
		sf::Font*		 GetFont(const std::string& name);

		bool DeleteTexture(const std::string& name);
		bool DeleteSoundBuffer(const std::string& name);
		bool DeleteFont(const std::string& name);

		static Resources& Get();

	private:
		Resources();

		ResourceManager<sf::Texture>	 m_Textures;
		ResourceManager<sf::SoundBuffer> m_SoundBuffers;
		ResourceManager<sf::Font>		 m_Fonts;

		std::mutex m_TextMutex;
		std::mutex m_SfxMutex;
		std::mutex m_FontMutex;
};