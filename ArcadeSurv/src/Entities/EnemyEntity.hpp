#pragma once

#include "Enitity.hpp"

class PlayerEntity;

class EnemyEntity : public Entity
{
	public:
		EnemyEntity(PlayerEntity* playerPtr);

		virtual void Update(float dt);
		virtual void Render(sf::RenderTarget& renderer);

	private:
		PlayerEntity* m_PlayerPtr;
};