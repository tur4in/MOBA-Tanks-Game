#pragma once

#include "stdafx.h"

class ExplosionSystem :
	MessageListener
{
public:
	ExplosionSystem();
	~ExplosionSystem();
	void Update(float dt);
	virtual void ReceiveMessage(Message* m) override;
	void Render();
	void Reset();

private:
	std::vector<std::shared_ptr<Actor>> m_explosions;
};

