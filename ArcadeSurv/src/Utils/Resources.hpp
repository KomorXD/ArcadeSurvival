#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics/Texture.hpp>

struct Resources
{
	ResourceManager<sf::Texture> textures;

	static Resources& Get();

	private:
		Resources();
};