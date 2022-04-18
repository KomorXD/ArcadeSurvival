#pragma once

#include "Enitity.hpp"
#include "BulletEntity.hpp"
#include "../Effects/Effect.hpp"

#include <vector>

class PlayerEntity : public Entity
{
	public:
		PlayerEntity(GameScene* scene);
		virtual ~PlayerEntity() = default;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void Input(float dt);
		void OnDamage(int32_t damage, float dt);
		void SetSpeedMultiplier(float mul);
		void SetDamageMultiplier(float mul);
		void SetFireRateMultiplier(float mul);
		void ApplyEffect(std::unique_ptr<Effect>&& effect);
		
		inline bool IsVulnerable() const { return m_InvulnFrames == 0; }
		inline const sf::View& GetPlayerCameraView() const { return m_PlayerCameraView; }

	private:
		void MovementInput();
		void FacingDirInput();
		void UpdateAnimation(float dt);
		void UpdateEffects(float dt);
		void UpdateIcons();

		std::vector<std::unique_ptr<Effect>> m_Effects;

		sf::Vector2f m_MoveDir;
		sf::Vector2f m_FacingDir;
		sf::View	 m_PlayerCameraView;
		sf::View	 m_InterfaceView;

		int32_t m_HP			  = 100;
		int32_t m_InvulnFrames	  = 0;
		int32_t m_FireRate		  = 10;
		int32_t m_FireFrames	  = 0;
		int32_t m_AnimationFrames = 0;

		float m_SpeedMultiplier    = 1.0f;
		float m_DamageMultiplier   = 1.0f;
		float m_FireRateMultiplier = 1.0f;
};