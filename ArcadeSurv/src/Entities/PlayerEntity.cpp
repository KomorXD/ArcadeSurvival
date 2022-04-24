#include "PlayerEntity.hpp"
#include "../Scenes/GameScene.hpp"
#include "../Utils/Resources.hpp"

#include <ranges>
#include <algorithm>

PlayerEntity::PlayerEntity(GameScene* scene)
	: Entity(scene, 64.0f), m_MoveDir({ 0.0f, 0.0f }), m_FacingDir({ 0.0f, 1.0f }), m_hpBar(&m_HP, { 500.0f, 16.0f }, { 10.0f, 15.0f })
{
	m_PlayerCameraView.setCenter(640.0f, 360.0f);
	m_PlayerCameraView.setSize(1280.0f, 720.0f);

	m_InterfaceView.setCenter(640.0f, 360.0f);
	m_InterfaceView.setSize(1280.0f, 720.0f);
	
	m_Body.setTextureRect({ 0, 0, 32, 32 });

	m_ShootingSound.setBuffer(*Resources::Get().GetSoundBuffer("shoot"));
	m_ShootingSound.setVolume(50.0f);

	m_hpBar.SetColor(sf::Color::Red);
}

void PlayerEntity::Input(float dt)
{
	MovementInput();
	FacingDirInput();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_FireFrames == 0)
	{
		m_Scene->SpawnBullet(m_FacingDir, GetPosition(), 500.0f, 10.0f * m_DamageMultiplier);
		m_FireFrames = static_cast<int32_t>((1 / dt) / (m_FireRate * m_FireRateMultiplier));

		m_ShootingSound.play();
	}
}

void PlayerEntity::OnDamage(int32_t damage, float dt)
{
	m_HP = std::max(m_HP - damage, 0);
	m_InvulnFrames = static_cast<int32_t>(1 / dt);
}

void PlayerEntity::SetSpeedMultiplier(float mul)
{
	m_SpeedMultiplier = mul;
}

void PlayerEntity::SetDamageMultiplier(float mul)
{
	m_DamageMultiplier = mul;
}

void PlayerEntity::SetFireRateMultiplier(float mul)
{
	m_FireRateMultiplier = mul;
}

void PlayerEntity::ApplyEffect(std::unique_ptr<Effect>&& effect)
{
	EffectType newEffectType	= effect->GetEffectType();
	EffectType newEffectOppType = effect->GetOppositeType();

	for(auto itr = m_Effects.begin(); itr != m_Effects.end();)
	{
		std::unique_ptr<Effect>& eff = *itr;
		
		if(eff->GetEffectType() == newEffectType)
			eff->RefreshEffect(effect->TimeLeft());

		if(eff->GetEffectType() == newEffectOppType)
		{
			itr = m_Effects.erase(itr);

			continue;
		}

		++itr;
	}

	effect->BindEffect(this);
	m_Effects.push_back(std::move(effect));
}

void PlayerEntity::MovementInput()
{
	sf::Vector2f wishDir(0.0f, 0.0f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		wishDir += { 0.0f, -1.0f };

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		wishDir += { 0.0f, 1.0f };

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		wishDir += { -1.0f, 0.0f };

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		wishDir += { 1.0f, 0.0f };

	float len = std::sqrtf(wishDir.x * wishDir.x + wishDir.y * wishDir.y);

	if(len != 0.0f)
		wishDir /= len;

	m_MoveDir = wishDir;
}

void PlayerEntity::FacingDirInput()
{
	int32_t vulnOffset = IsVulnerable() ? 0 : 128;
	int32_t texRectY = m_Body.getTextureRect().top;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_FacingDir = {  0.0f, -1.0f  };
		m_Body.setTextureRect({ vulnOffset + 96, texRectY, 32, 32 });

		return;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_FacingDir = {  0.0f,  1.0f  };
		m_Body.setTextureRect({ vulnOffset + 0, texRectY, 32, 32 });

		return;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_FacingDir = { -1.0f,  0.0f  };
		m_Body.setTextureRect({ vulnOffset + 32, texRectY, 32, 32 });

		return;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_FacingDir = {  1.0f,  0.0f  };
		m_Body.setTextureRect({ vulnOffset + 64, texRectY, 32, 32 });

		return;
	}
}

void PlayerEntity::UpdateAnimation(float dt)
{
	int32_t texRectX = m_Body.getTextureRect().left;
	int32_t texRectY = m_Body.getTextureRect().top;

	if(IsVulnerable() && texRectX >= 128)
		texRectX -= 128;

	if(!IsVulnerable() && texRectX < 128)
		texRectX += 128;

	m_AnimationFrames = std::max(m_AnimationFrames - 1, 0);

	if(m_AnimationFrames == 0)
	{
		m_AnimationFrames = static_cast<int32_t>(0.5f / (dt * m_SpeedMultiplier));
		texRectY = 32 - texRectY;
	}

	m_Body.setTextureRect({ texRectX, texRectY, 32, 32 });
}

void PlayerEntity::UpdateEffects(float dt)
{
	auto itr = std::ranges::find_if(m_Effects, [&](const std::unique_ptr<Effect>& effect)
	{
		return effect->TimeLeft() == 0.0f;
	});

	if(itr != m_Effects.end())
		m_Effects.erase(itr);

	for(auto& eff : m_Effects)
		eff->Update(dt);

	UpdateIcons();
}

void PlayerEntity::UpdateIcons()
{
	for(size_t i = 0; i < m_Effects.size(); ++i)
		m_Effects[i]->SetIconPosition({ 35.0f * i + 750.0f, 8.0f });
}

void PlayerEntity::Update(float dt)
{
	m_InvulnFrames = std::max(m_InvulnFrames - 1, 0);
	m_FireFrames   = std::max(m_FireFrames - 1, 0);

	UpdateAnimation(dt);
	UpdateEffects(dt);
	m_hpBar.Update();

	m_Body.move(m_MoveDir * m_MovementSpeed * m_SpeedMultiplier * dt);
	m_PlayerCameraView.move(m_MoveDir * m_MovementSpeed * m_SpeedMultiplier * dt);

}

void PlayerEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
	renderer.setView(m_InterfaceView);
	
	for(auto& effect : m_Effects)
		effect->RenderIcon(renderer);

	m_hpBar.draw(renderer, sf::RenderStates::Default);

	renderer.setView(m_PlayerCameraView);
}

void PlayerEntity::SetPosition(const sf::Vector2f& pos)
{
	m_Body.setPosition(pos);
	m_PlayerCameraView.setCenter({ GetPosition().x + 16.0f, GetPosition().y + 16.0f });
}
