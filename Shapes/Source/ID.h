#pragma once

#include <string>
#include <vector>

class ID
{
private:

	std::string m_ID;
public:

	void Generate();

	ID() = default;
	~ID() = default;
	ID(const std::string& ID) { m_ID = ID; }
	ID(const ID& ID) { m_ID = ID.m_ID; }
		
	void operator=(std::string ID) { m_ID = ID; }
	void operator=(const ID& ID) { m_ID = ID.m_ID; }

	operator std::string() const { return m_ID; }
	std::string Get() const { return m_ID; }
};