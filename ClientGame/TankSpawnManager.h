#pragma once
#include "BasicSpawnManager.h"
class CTankSpawnPoint :
    public CBasicSpawnPoint
{
public:
    CTankSpawnPoint(Vector2 pos, ESideIdentificator side);
    ~CTankSpawnPoint() = default;
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;
    virtual void UpdateSpawnTime(float dt) override;
    virtual void Render() override;

private:
    void StartLoading();
    void StopLoading();
    void UpdateLoader(float dt);
    void RenderLoader();

private:
    Actor m_loadingActor;
    bool m_tankIsDead;
    bool m_loading = false;
};

