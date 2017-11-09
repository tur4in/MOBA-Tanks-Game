#include "stdafx.h"
#include "ExplosionSystem.h"
#include "Tank.h"
#include "Base.h"

ExplosionSystem::ExplosionSystem()
{
	theSwitchboard.SubscribeTo(this, "Explosion");
	theSwitchboard.SubscribeTo(this, "BaseDead");
}


ExplosionSystem::~ExplosionSystem()
{
}

void ExplosionSystem::Update(float dt)
{
	auto it = m_explosions.begin();
	while (it < m_explosions.end())
	{
		if (!(*it)->IsSpriteAnimPlaying())
		{
			it = m_explosions.erase(it);
		}
		else
		{
			++it;
		}
	}
	for (auto explositon : m_explosions)
	{
		explositon->Update(dt);
	}
}

void ExplosionSystem::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "Explosion")
	{
		auto data = static_cast<TypedMessage<std::pair<Vector2, Vector2>>*>(m);
		auto ptr = std::make_shared<Actor>();
		ptr->LoadSpriteFrames(theTuning.GetString("ExplosionSprite"));
		ptr->SetPosition(data->GetValue().first);
		ptr->SetSize(data->GetValue().second.X * 4, data->GetValue().second.X * 6);
		ptr->PlaySpriteAnimation(0.02f, SAT_OneShot, 0, 45);
		m_explosions.push_back(ptr);
	}
	else if (m->GetMessageName() == "BaseDead")
	{
		Reset();
	}
}

void ExplosionSystem::Render()
{
	for (auto explosion : m_explosions)
	{
		explosion->Render();
	}
}

void ExplosionSystem::Reset()
{
	m_explosions.clear();
}