#pragma once

#include "Enitity.hpp"

class PlayerEntity;

class EnemyEntity : public Entity
{
	public:
		EnemyEntity(PlayerEntity* playerPtr);
		virtual ~EnemyEntity() = default;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		PlayerEntity* m_PlayerPtr;
};