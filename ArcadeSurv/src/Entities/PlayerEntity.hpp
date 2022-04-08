#pragma once

#include "Enitity.hpp"
#include "BulletEntity.hpp"

#include <vector>

class PlayerEntity : public Entity
{
	public:
		PlayerEntity();
		virtual ~PlayerEntity() = default;

		virtual void Update(float dt) override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void Input();
		void OnDamage(int32_t damage, float dt);
		
		inline bool IsVulnerable() const { return m_InvulnFrames == 0; }
		inline const sf::View& GetPlayerCameraView() const { return m_PlayerCameraView; }

	private:
		sf::Vector2f m_MoveDir;
		sf::Vector2f m_FacingDir;
		sf::View	 m_PlayerCameraView;

		int32_t m_HP;
		int32_t m_InvulnFrames;
		int32_t m_FireDelay;

		std::vector<BulletEntity> m_Bullets;
};