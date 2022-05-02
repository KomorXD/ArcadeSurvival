#pragma once

#include "Enitity.hpp"
#include "../Effects/Effect.hpp"

class EffectEntity : public Entity
{
	public:
		EffectEntity(EffectType effectType, float effectDuration, float entityLifespan, const sf::Vector2f& pos = { 0.0f, 0.0f });
		EffectEntity(EffectEntity&& other) noexcept;
		virtual ~EffectEntity() = default;
		
		EffectEntity& operator= (EffectEntity&& other) noexcept;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget & renderer) override;

		void OnPlayerIntersect(PlayerEntity* player);

		inline bool Expired() const { return m_Lifespan == 0.0f; }

	private:
		std::unique_ptr<Effect> m_StoredEffect;

		float m_Lifespan;
};