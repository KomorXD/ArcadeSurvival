#pragma once

#include <SFML/Graphics/Sprite.hpp>

enum class EffectType
{
	NONE,
	QUAD,
	HASTE,
	CRIPPLE
};

class PlayerEntity;

class Effect
{
	public:
		Effect(float time, sf::Texture* icon);
		virtual ~Effect() = default;

		virtual void BindEffect(PlayerEntity* player) = 0;
		
		virtual void RefreshEffect(float time);
		virtual void ClearEffect();
		virtual void Update(float dt);
		virtual void RenderIcon(sf::RenderTarget& renderer);
		virtual void SetIconPosition(const sf::Vector2f& pos);

		virtual inline float TimeLeft() const { return m_TimeLeft; }
		virtual inline EffectType GetEffectType() const { return m_Type; }
		virtual inline EffectType GetOppositeType() const { return m_OppositeType; }

	protected:
		sf::Sprite	  m_Icon;
		PlayerEntity* m_AffectedPlayer = nullptr;
		EffectType	  m_Type		   = EffectType::NONE;
		EffectType	  m_OppositeType   = EffectType::NONE;
		float		  m_TimeLeft;
};