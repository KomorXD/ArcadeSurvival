#pragma once

#include <SFML/Graphics/Sprite.hpp>

enum class EffectType
{
	NONE,
	QUAD,
	HASTE,
	CRIPPLE,
	HEAL,
	NO_WEAPON,
	SPREAD_WEAPON,
	EXPLOSIVE_WEAPON
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
		EffectType	  m_Type = EffectType::NONE;
		EffectType	  m_OppositeType = EffectType::NONE;
		float		  m_TimeLeft;
};

class HasteEffect : public Effect
{
	public:
		HasteEffect(float time, sf::Texture* icon);
		virtual ~HasteEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};

class QuadDmgEffect : public Effect
{
	public:
		QuadDmgEffect(float time, sf::Texture* icon);
		virtual ~QuadDmgEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};

class CrippleEffect : public Effect
{
	public:
		CrippleEffect(float time, sf::Texture* icon);
		virtual ~CrippleEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};

class HealEffect : public Effect
{
	public:
		HealEffect(float time, sf::Texture* icon);
		virtual ~HealEffect() = default;

		virtual void BindEffect(PlayerEntity* player) override;
};

class NoWeaponEffect : public Effect
{
	public:
		NoWeaponEffect(float time, sf::Texture* icon);
		virtual ~NoWeaponEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};

class SpreadWeaponEffect : public Effect
{
	public:
		SpreadWeaponEffect(float time, sf::Texture* icon);
		virtual ~SpreadWeaponEffect();

		virtual void BindEffect(PlayerEntity* player) override;
		virtual void Update(float dt) override;
};

class ExplosiveWeaponEffect : public Effect
{
	public:
		ExplosiveWeaponEffect(float time, sf::Texture* icon);
		virtual ~ExplosiveWeaponEffect();

		virtual void BindEffect(PlayerEntity* player) override;
		virtual void Update(float dt) override;
};
