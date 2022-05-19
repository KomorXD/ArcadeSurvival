#pragma once

#include "Enitity.hpp"
#include "BulletEntity.hpp"
#include "../Effects/Effect.hpp"
#include "../UI/ResourceBar.hpp"
#include "../WeaponTypes/Weapon.hpp"

#include <vector>
#include <SFML/Audio/Sound.hpp>

class GameScene;

class PlayerEntity : public Entity
{
	public:
		PlayerEntity(GameScene* scene, const sf::Vector2f& pos = { 0.0f, 0.0f });
		virtual ~PlayerEntity() = default;

		virtual void Update(float dt)					  override;
		virtual void Render(sf::RenderTarget& renderer)	  override;
		virtual void SetPosition(const sf::Vector2f& pos) override;

		void Input(float dt);
		void OnDamage(int32_t damage, float dt);
		void OnEnemyKilled();

		void SetSpeedMultiplier(float mul);
		void SetDamageMultiplier(float mul);
		void SetFireRateMultiplier(float mul);
		void SetMovementSpeed(float ms);
		void SetWeaponType(std::unique_ptr<Weapon>&& type);

		void ApplyEffect(std::unique_ptr<Effect>&& effect);
		
		inline bool IsVulnerable() const { return m_InvulnFrames == 0; }
		inline const sf::View& GetPlayerCameraView() const { return m_PlayerCameraView; }
		inline const sf::View& GetInterfaceView() const { return m_InterfaceView; }

	private:
		void MovementInput();
		void FacingDirInput();
		void UpdateAnimation(float dt);
		void UpdateEffects(float dt);
		void UpdateIcons();

		GameScene* m_Scene;

		std::unique_ptr<Weapon> m_UsedWeaponType;

		std::vector<std::unique_ptr<Effect>> m_Effects;

		sf::View m_PlayerCameraView;
		sf::View m_InterfaceView;

		sf::Vector2f m_MoveDir   = { 0.0f, 0.0f };
		sf::Vector2f m_FacingDir = { 0.0f, 1.0f };

		int32_t m_HP			  = 100;
		int32_t m_KillCount		  = 0;
		int32_t m_InvulnFrames	  = 0;
		int32_t m_FireRate		  = 5;
		int32_t m_FireFrames	  = 0;
		int32_t m_AnimationFrames = 0;

		float m_SpeedMultiplier    = 1.0f;
		float m_DamageMultiplier   = 1.0f;
		float m_FireRateMultiplier = 1.0f;

		float m_MovementSpeed = 100.0f;

		sf::Sound m_ShootingSound;
		sf::Sound m_HurtSound;

		ResourceBar m_hpBar;
		ResourceBar m_UltBar;
};