#pragma once

#include "Enitity.hpp"

class PlayerEntity : public Entity
{
	public:
		PlayerEntity();

		virtual void Update(float dt);
		virtual void Render(sf::RenderTarget& renderer);

		void Input();
		
		inline sf::View GetPlayerCameraView() const { return m_PlayerCameraView; }

	private:
		sf::Vector2f m_MoveDir;
		sf::View	 m_PlayerCameraView;
};