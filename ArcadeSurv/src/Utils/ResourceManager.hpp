#pragma once

#include <unordered_map>
#include <iostream>

template<typename ResourceType>
class ResourceManager
{
	public:
		ResourceManager(const std::string& folder, const std::string& extension)
			: m_Folder(folder), m_Extension(extension)
		{ }

		bool LoadResource(const std::string& name)
		{
			if(m_Resources.find(name) != m_Resources.end())
				return false;

			ResourceType res;

			if(!res.loadFromFile(GetFullPath(name)))
			{
				std::cerr << "Failed to load resource: " << GetFullPath(name) << '\n';

				return false;
			}

			m_Resources.insert(std::make_pair(name, res));

			return true;
		}

		bool EraseResource(const std::string& name)
		{
			auto itr = m_Resources.find(name);

			if(itr == m_Resources.end())
			{
				std::cerr << "Failed to release resource: " << GetFullPath(name) << " - no such resource to erase\n";

				return false;
			}

			m_Resources.erase(itr);

			return true;
		}

		ResourceType* GetResource(const std::string& name)
		{
			auto itr = m_Resources.find(name);

			if(itr == m_Resources.end())
			{
				std::cerr << "Failed to get resource " << GetFullPath(name) << " - it doesn't exist\n";

				return nullptr;
			}
			
			return &((*itr).second);
		}

	private:
		inline std::string GetFullPath(const std::string& name) { return m_Folder + name + m_Extension; }

		std::unordered_map<std::string, ResourceType> m_Resources;
		
		std::string m_Folder;
		std::string m_Extension;
};