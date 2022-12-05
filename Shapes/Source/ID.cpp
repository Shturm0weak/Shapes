#include "ID.h"

#include <random>
#include <sstream>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<size_t> s_UniformDistributionID1(0, 15);
static std::uniform_int_distribution<size_t> s_UniformDistributionID2(8, 11);

void ID::Generate()
{
	std::stringstream id;
	id << std::hex;
		
	for (size_t i = 0; i < 8; i++)
	{
		id << s_UniformDistributionID1(s_Engine);
	}

	id << "-";

	for (size_t i = 0; i < 4; i++)
	{
		id << s_UniformDistributionID1(s_Engine);
	}

	id << "-4";

	for (size_t i = 0; i < 3; i++)
	{
		id << s_UniformDistributionID1(s_Engine);
	}

	id << "-";
	id << s_UniformDistributionID2(s_Engine);

	for (size_t i = 0; i < 3; i++)
	{
		id << s_UniformDistributionID1(s_Engine);
	}

	id << "-";
		
	for (size_t i = 0; i < 12; i++)
	{
		id << s_UniformDistributionID1(s_Engine);
	}

	m_ID = id.str();
}