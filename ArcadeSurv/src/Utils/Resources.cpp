#include "Resources.hpp"

Resources& Resources::Get()
{
	static Resources rscs;

	return rscs;
}

Resources::Resources()
	: textures("Resources/Textures/", ".png")
{
	textures.LoadResource("lol");
}
