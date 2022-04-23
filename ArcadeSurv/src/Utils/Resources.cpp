#include "Resources.hpp"

Resources& Resources::Get()
{
	static Resources rscs;

	return rscs;
}

Resources::Resources()
	: m_Textures("Resources/Textures/", ".png")
	, m_SoundBuffers("Resources/SFX/", ".ogg")
	, m_Fonts("Resources/Fonts/", ".ttf")
{ }

bool Resources::LoadTexture(const std::string& name)
{
	std::lock_guard<std::mutex> lock(m_TextMutex);

	return m_Textures.LoadResource(name);
}

bool Resources::LoadSoundBuffer(const std::string& name)
{
	std::lock_guard<std::mutex> lock(m_SfxMutex);

	return m_SoundBuffers.LoadResource(name);
}

bool Resources::LoadFont(const std::string& name)
{
	std::lock_guard<std::mutex> lock(m_FontMutex);
	
	return m_Fonts.LoadResource(name);
}

sf::Texture* Resources::GetTexture(const std::string& name)
{
	return m_Textures.GetResource(name);
}

sf::SoundBuffer* Resources::GetSoundBuffer(const std::string& name)
{
	return m_SoundBuffers.GetResource(name);
}

sf::Font* Resources::GetFont(const std::string& name)
{
	return m_Fonts.GetResource(name);
}

bool Resources::DeleteTexture(const std::string& name)
{
	return m_Textures.EraseResource(name);
}

bool Resources::DeleteSoundBuffer(const std::string& name)
{
	return m_SoundBuffers.LoadResource(name);
}

bool Resources::DeleteFont(const std::string& name)
{
	return m_Fonts.LoadResource(name);
}
