#pragma once
class CTimer
{
public:
	CTimer();
	~CTimer();
	void Update(float dt);
	void Render();

private:
	float m_timePlaying;
	TextActor m_time;
};

