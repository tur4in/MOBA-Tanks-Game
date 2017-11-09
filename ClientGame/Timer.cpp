#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer()
{
	int xWidth = theCamera.GetWindowWidth();
	int yHeight = theCamera.GetWindowHeight();
	m_time.SetPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight * 0.1f));

	RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 60, "TimeFont");
	m_time.SetAlignment(TXT_Center);
	m_time.SetFont("TimeFont");

	m_timePlaying = 0;
}

CTimer::~CTimer()
{
}

void CTimer::Update(float dt)
{
	m_timePlaying += dt;
	size_t seconds = m_timePlaying;
	size_t minutes = seconds / 60;
	seconds %= 60;
	std::string time;
	if (minutes < 10)
	{
		time = "0" + std::to_string(minutes);
	}
	else
	{
		time = std::to_string(minutes);
	}

	if (seconds < 10)
	{
		time += " : 0" + std::to_string(seconds);
	}
	else
	{
		time += " : " + std::to_string(seconds);
	}
	m_time.SetDisplayString(time);
}

void CTimer::Render()
{
	m_time.Render();
}
