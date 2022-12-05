#pragma once

#include <chrono>

class Time
{
private:

	float m_Time = 0.0f;
	float m_LastTime = 0.0f;
	float m_DeltaTime = 0.0f;

	Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) { return *this; }
	~Time() = default;

	static Time& GetInstance()
	{
		static Time deltaTime;
		return deltaTime;
	}

	void CalculateDeltaTimeImpl()
	{
		float currentTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		m_DeltaTime = abs(m_LastTime - currentTime);
		m_LastTime = currentTime;
		m_Time += m_DeltaTime;
	}

public:

	static inline float GetTime() { return Time::GetInstance().m_Time; };
		
	static inline float GetDeltaTime() { return Time::GetInstance().m_DeltaTime; };

	static inline float GetFps() { return 1.0f / Time::GetDeltaTime(); }

	static inline void CalculateDeltaTime() { Time::GetInstance().CalculateDeltaTimeImpl(); }
};