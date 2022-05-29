#include "Effects.hpp"
#include "Entities/PlayerEntity.hpp"

#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>

Effect::Effect(float time, sf::Texture* icon)
	: m_TimeLeft(time)
{
	if(icon)
		m_Icon.setTexture(*icon);
}

void Effect::RefreshEffect(float time)
{
	m_TimeLeft = time;
}

void Effect::ClearEffect()
{
	m_TimeLeft = 0.0f;
}

void Effect::Update(float dt)
{
	if(m_AffectedPlayer)
		m_TimeLeft = std::max(m_TimeLeft - dt, 0.0f);
}

void Effect::RenderIcon(sf::RenderTarget& renderer)
{
	renderer.draw(m_Icon);
}

void Effect::SetIconPosition(const sf::Vector2f& pos)
{
	m_Icon.setPosition(pos);
}

HasteEffect::HasteEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::HASTE;
	m_OppositeType = EffectType::CRIPPLE;
}

HasteEffect::~HasteEffect()
{
	if(m_AffectedPlayer)
	{
		m_AffectedPlayer->SetSpeedMultiplier(1.0f);
		m_AffectedPlayer->SetFireRateMultiplier(1.0f);
	}
}

void HasteEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetSpeedMultiplier(2.0f);
	m_AffectedPlayer->SetFireRateMultiplier(2.0f);
}

QuadDmgEffect::QuadDmgEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::QUAD;
}

QuadDmgEffect::~QuadDmgEffect()
{
	if(m_AffectedPlayer)
		m_AffectedPlayer->SetDamageMultiplier(1.0f);
}

void QuadDmgEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetDamageMultiplier(4.0f);
}

CrippleEffect::CrippleEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::CRIPPLE;
	m_OppositeType = EffectType::HASTE;
}

CrippleEffect::~CrippleEffect()
{
	if(m_AffectedPlayer)
	{
		m_AffectedPlayer->SetSpeedMultiplier(1.0f);
		m_AffectedPlayer->SetFireRateMultiplier(1.0f);
	}
}

void CrippleEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetSpeedMultiplier(0.5f);
	m_AffectedPlayer->SetFireRateMultiplier(0.5f);
}

HealEffect::HealEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::HEAL;
}

void HealEffect::BindEffect(PlayerEntity* player)
{
	player->Heal(20);
}

NoWeaponEffect::NoWeaponEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::NO_WEAPON;
}

NoWeaponEffect::~NoWeaponEffect()
{
	if(m_AffectedPlayer)
		m_AffectedPlayer->SetWeaponType(std::make_unique<BasicWeapon>());
}

void NoWeaponEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;

	if(m_AffectedPlayer->HasEffect(EffectType::EXPLOSIVE_WEAPON))
		m_AffectedPlayer->ClearEffect(EffectType::EXPLOSIVE_WEAPON);
	else if(m_AffectedPlayer->HasEffect(EffectType::SPREAD_WEAPON))
		m_AffectedPlayer->ClearEffect(EffectType::SPREAD_WEAPON);

	m_AffectedPlayer->SetWeaponType(std::make_unique<NoWeapon>());
}

SpreadWeaponEffect::SpreadWeaponEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::SPREAD_WEAPON;
	m_OppositeType = EffectType::EXPLOSIVE_WEAPON;
}

SpreadWeaponEffect::~SpreadWeaponEffect()
{
	if(m_AffectedPlayer)
		m_AffectedPlayer->SetWeaponType(std::make_unique<BasicWeapon>());
}

void SpreadWeaponEffect::BindEffect(PlayerEntity* player)
{
	if(player->HasEffect(EffectType::NO_WEAPON))
	{
		m_TimeLeft = 0.0f;

		return;
	}
	
	m_AffectedPlayer = player;
	player->SetWeaponType(std::make_unique<SpreadWeapon>());
}

void SpreadWeaponEffect::Update(float dt)
{
	if(m_AffectedPlayer)
		m_TimeLeft -= dt;
}

ExplosiveWeaponEffect::ExplosiveWeaponEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::EXPLOSIVE_WEAPON;
	m_OppositeType = EffectType::SPREAD_WEAPON;
}

ExplosiveWeaponEffect::~ExplosiveWeaponEffect()
{
	if(m_AffectedPlayer)
		m_AffectedPlayer->SetWeaponType(std::make_unique<BasicWeapon>());
}

void ExplosiveWeaponEffect::BindEffect(PlayerEntity* player)
{
	if(player->HasEffect(EffectType::NO_WEAPON))
	{
		m_TimeLeft = 0.0f;

		return;
	}

	m_AffectedPlayer = player;
	player->SetWeaponType(std::make_unique<ExplosiveWeapon>());
}

void ExplosiveWeaponEffect::Update(float dt)
{
	if(m_AffectedPlayer)
		m_TimeLeft -= dt;
}
