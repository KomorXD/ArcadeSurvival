#pragma once

#include "../Enitity.hpp"

class BulletEntity : public Entity
{
	public:
		BulletEntity(const sf::Vector2f& pos = { 0.0f, 0.0f });
		virtual ~BulletEntity() = default;

		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void SetTravelSpeed(float ts);
		void SetStrength(float strength);
		void SetVelocityVector(const sf::Vector2f& velVec);

		inline float GetStrength() const { return m_Strength; }
		
	private:
		sf::Vector2f m_TravelDir;
		float		 m_TravelSpeed;
		float		 m_Strength;
};