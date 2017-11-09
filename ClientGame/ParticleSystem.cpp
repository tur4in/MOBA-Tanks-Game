#include "stdafx.h"
#include "ParticleSystem.h"

void ParticleSystem::CreateExplosion(Vector2 pos, float timetoLive)
{
    ParticleActor* exp = new ParticleActor();
    exp->SetPosition(pos);
    exp->SetSize(0.08f, 0.08f);
    exp->SetDrawShape(ADS_Circle);
    exp->SetColor(0.8f, 0.9f, 0.0f);
    exp->SetEndColor(Color(1.0f, 0.0f, 0.0f));
    exp->SetMaxParticles(2000);
    exp->SetParticlesPerSecond(5000);
    exp->SetParticleLifetime(0.2f);
    exp->SetSystemLifetime(timetoLive);
    exp->SetSpread(MathUtil::Pi * 2);
    exp->SetGravity(Vector2(0, 0));
    theWorld.Add(exp);
}