#include "stdafx.h"
#include "SessionInfo.h"
#include "TunedInfo.h"
#include "Tank.h"
#include "Base.h"
#include "Tower.h"
#include "BurstWeapon.h"
#include "RangedMob.h"
#include "MeleeMob.h"
#include "LaserWeapon.h"

template<>
void TunedInfo::SetProps(std::shared_ptr<CBasicWeapon>& weapon)
{
    auto sideStr = std::to_string((int)weapon->GetSideOfConflict() + 1);
    weapon->SetColor(
        theTuning.GetFloat("Team" + sideStr + "ColorR"),
        theTuning.GetFloat("Team" + sideStr + "ColorG"),
        theTuning.GetFloat("Team" + sideStr + "ColorB"));
    weapon->SetDamage(theSession[weapon->GetSideOfConflict()]->GetBasicTankDamage() * theTuning.GetInt(theSession[weapon->GetSideOfConflict()]->GetTankWeaponType()));
    weapon->SetPoolSize(theTuning.GetInt("TankWeaponPoolSize"));
    weapon->SetSize(theTuning.GetVector("TankSize").X * 0.75, theTuning.GetVector("TankSize").Y * 0.75);
    weapon->SetDrawShape(ADS_Square);
    weapon->SetSprite(theTuning.GetString("TankTurretSprite"));
}

template<>
void TunedInfo::SetProps(std::shared_ptr<CTank>& tank)
{
    tank->SetBounty(theTuning.GetInt("TankBounty"));
    tank->SetRotationSpeed(theTuning.GetFloat("TankRotationSpeed"));
    tank->SetMaxHP(theSession[tank->GetSideOfConflict()]->GetTankHP());
    tank->SetSize(theTuning.GetVector("TankSize").X, theTuning.GetVector("TankSize").Y);
    tank->SetShapeType(PhysicsActor::eShapeType::SHAPETYPE_BOX);
    tank->SetSprite(theTuning.GetString("TankSprite"));
    tank->SetMoveSpeed(theSession[tank->GetSideOfConflict()]->GetTankSpeed());
    tank->SetDensity(theTuning.GetFloat("TankDensity"));
    tank->SetAttackDelay(theTuning.GetFloat("TankAttackDelay"));
    auto weapon = CBasicWeapon::Create(theSession[tank->GetSideOfConflict()]->GetTankWeaponType(), tank->GetSideOfConflict());
    SetProps(weapon);
    tank->SetWeapon(weapon);
    tank->SetTowerRotation(theTuning.GetFloat("TankGunRotationSpeed"));
}


template<>
void TunedInfo::SetProps(std::shared_ptr<CTower>& tower)
{
    tower->SetBounty(theTuning.GetInt("TowerBounty"));
    tower->SetSprite(theTuning.GetString("TowerSprite"));
    tower->SetSize(theTuning.GetFloat("TowerSize"));
    tower->SetMaxHP(theTuning.GetInt("TowerHP"));
    tower->GetWeapon()->SetDamage(theTuning.GetInt("TowerDamage"));
    tower->SetAttackDist(theTuning.GetFloat("TowerAttackDist"));
    tower->SetDetectDist(theTuning.GetFloat("TowerDetectDist"));
    tower->GetWeapon()->SetDrawShape(ADS_Square);
    tower->GetWeapon()->SetSize(theTuning.GetFloat("TowerSize") * 0.4, theTuning.GetFloat("TowerSize") * 1);
    tower->GetWeapon()->LoadSpriteFrames(theTuning.GetString("BaseGunSpriteAnimation"));
    tower->SetAttackDelay(theTuning.GetFloat("TowerAttackDelay"));
    tower->SetTowerRotation(theTuning.GetFloat("TowerRotationSpeed"));
}

template<>
void TunedInfo::SetProps(std::shared_ptr<CBase>& base)
{
    base->SetSprite(theTuning.GetString("BaseSprite"));
    base->SetSize(theTuning.GetFloat("BaseSize"));
    base->SetMaxHP(theSession[base->GetSideOfConflict()]->GetBaseHP());
    base->GetWeapon()->SetDamage(theTuning.GetInt("BaseDamage"));
    base->SetAttackDist(theTuning.GetFloat("BaseAttackDist"));
    base->SetDetectDist(theTuning.GetFloat(("BaseDetectDist")));
    base->GetWeapon()->SetDrawShape(ADS_Square);
    base->GetWeapon()->SetSize(theTuning.GetFloat("BaseSize") * 0.2, theTuning.GetFloat("TowerSize") * 2.5);
    base->GetWeapon()->LoadSpriteFrames(theTuning.GetString("BaseGunSpriteAnimation"));
    base->SetAttackDelay(theTuning.GetFloat("BaseAttackDelay"));
    base->SetTowerRotation(theTuning.GetFloat("TowerRotationSpeed"));
}

template<>
void TunedInfo::SetProps(std::shared_ptr<CRangedMob>& mob)
{
    mob->SetBounty(theTuning.GetInt("RangeMobBounty"));
    mob->SetSprite(theTuning.GetString("RangeMobSprite"));
    mob->SetSize(theTuning.GetFloat("RangeMobSize"));
    mob->SetMaxHP(theTuning.GetInt("RangeMobHP") + theSession[mob->GetSideOfConflict()]->GetBasicMobHP());
    mob->SetMoveSpeed(theTuning.GetFloat("RangeMobSpeed"));
    mob->SetAttackDist(theTuning.GetFloat("RangeMobAttackDist"));
    mob->SetDetectDist(theTuning.GetFloat("RangeMobDetectDist"));
    mob->GetWeapon()->SetDrawShape(ADS_Square);
    mob->GetWeapon()->SetSize(theTuning.GetFloat("RangeMobSize") * 0.4, theTuning.GetFloat("RangeMobSize") * 1);
    mob->GetWeapon()->SetSprite(theTuning.GetString("RangeMobTurretSprite"));
    mob->GetWeapon()->SetDamage(theTuning.GetInt("RangeMobDamage"));
    mob->SetAttackDelay(theTuning.GetFloat("RangeMobAttackDelay"));
    mob->SetTowerRotation(theTuning.GetFloat("TowerRotationSpeed"));
}

template<>
void TunedInfo::SetProps(std::shared_ptr<CMob>& mob)
{
    mob->SetBounty(theTuning.GetInt("MobBounty"));

    mob->LoadSpriteFrames(theTuning.GetString("MobSprite"));
    mob->PlaySpriteAnimation(0.4f, SAT_Loop, 0, 2);

    mob->SetSize(theTuning.GetFloat("MobSize"));
    mob->SetMaxHP(theSession[mob->GetSideOfConflict()]->GetBasicMobHP());
    mob->SetAttackForce(theTuning.GetInt("MobDamage"));
    mob->SetMoveSpeed(theTuning.GetFloat("MobSpeed"));
    mob->SetAttackDist(theTuning.GetFloat("MobAttackDist"));
    mob->SetDetectDist(theTuning.GetFloat("MobDetectDist"));
}

template<>
void TunedInfo::SetProps(std::shared_ptr<CMeleeMob>& mob)
{
    mob->SetBounty(theTuning.GetInt("MeeleeMobBounty"));
    mob->SetSprite(theTuning.GetString("MeeleeMobSprite"));
    mob->SetSize(theTuning.GetFloat("MeeleeMobSize"));
    mob->SetMaxHP(theTuning.GetInt("MeeleeMobHP") + theSession[mob->GetSideOfConflict()]->GetBasicMobHP());
    mob->SetAttackForce(theTuning.GetInt("MeeleeMobDamage"));
    mob->SetMoveSpeed(theTuning.GetFloat("MeeleeMobSpeed"));
    mob->SetAttackDist(theTuning.GetFloat("MeeleeMobAttackDist"));
    mob->SetDetectDist(theTuning.GetFloat("MeeleeMobDetectDist"));
    mob->SetAttackDelay(theTuning.GetFloat("MeeleeMobAttackDelay"));
}