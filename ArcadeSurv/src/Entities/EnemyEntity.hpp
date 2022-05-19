#pragma once

#include "Enitity.hpp"

class PlayerEntity;

class EnemyEntity : public Entity
{
	public:
		EnemyEntity(PlayerEntity* playerPtr, const sf::Vector2f& pos = { 0.0f, 0.0f });
		virtual ~EnemyEntity() = default;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void OnDamage(int32_t damage);
		void SetMovementSpeed(float ms);
		void SetStrength(float strength);
		
		inline float GetStrength() const { return m_Strength; }
		inline bool IsDead() const { return m_HP == 0 && m_AnimationFrames == 0; }
		inline bool IsDying() const { return m_HP == 0 && m_DyingAnimationFrames != 0; }
		
	private:
		PlayerEntity* m_PlayerPtr;

		int32_t m_HP				   = 100;
		int32_t m_AnimationFrames	   = 0;
		int32_t m_DyingAnimationFrames = 0;

		float m_MovementSpeed;
		float m_Strength;

		void DyingUpdate(float dt);
};