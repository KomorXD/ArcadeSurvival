#include "Resources.hpp"

Resources& Resources::Get()
{
	static Resources rscs;

	return rscs;
}

Resources::Resources()
	: textures("Resources/Textures/", ".png")
{
	textures.LoadResource("player_atlas");
	textures.LoadResource("enemy_atlas");
	textures.LoadResource("basic_bullet");
	textures.LoadResource("effect_haste");
	textures.LoadResource("effect_quad");
}
