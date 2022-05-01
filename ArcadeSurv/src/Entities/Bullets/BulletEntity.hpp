#pragma once

#include "../Enitity.hpp"

class BulletEntity : public Entity
{
	public:
		BulletEntity(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& pos, float travelSpeed, float strength);
		virtual ~BulletEntity() = default;

		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

		inline float GetStrength() const { return m_Strength; }
		
	private:
		sf::Vector2f m_TravelDir;
		float		 m_Strength;
};