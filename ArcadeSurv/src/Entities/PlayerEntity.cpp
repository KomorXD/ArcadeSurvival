#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity()
	: Entity(50.0f), m_MoveDir({ 0.0f, 0.0f }), m_FacingDir({ 1.0f, 0.0f }), m_HP(100), m_InvulnFrames(0)
{
	m_Body.setFillColor(sf::Color::Cyan);
	m_PlayerCameraView.setCenter(640.0f, 360.0f);
	m_PlayerCameraView.setSize(1280.0f, 720.0f);
}

void PlayerEntity::Input()
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

	if(len == 1.0f)
		m_FacingDir = wishDir;

	m_MoveDir = wishDir;
}

void PlayerEntity::OnDamage(int32_t damage, float dt)
{
	m_HP = std::max(m_HP - damage, 0);
	m_InvulnFrames = 2 / dt;

	printf("Took %d damage\tCurr HP: %d\n", damage, m_HP);
}

void PlayerEntity::Update(float dt)
{
	if(m_HP == 0)
	{
		printf("ded xd\n");

		return;
	}

	--m_InvulnFrames;
	m_InvulnFrames = std::max(m_InvulnFrames - 1, 0);

	m_Body.move(m_MoveDir * m_MovementSpeed * dt);
	m_PlayerCameraView.move(m_MoveDir * m_MovementSpeed * dt);
}

void PlayerEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}
