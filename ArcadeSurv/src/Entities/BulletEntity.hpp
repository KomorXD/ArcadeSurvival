#pragma once

#include "Enitity.hpp"

class BulletEntity : public Entity
{
	public:
		BulletEntity(const sf::Vector2f& dir, float travelSpeed);
		virtual ~BulletEntity() = default;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		sf::Vector2f m_TravelDir;
};