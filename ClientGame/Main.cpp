#include "stdafx.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
    //1366-768
	theWorld.Initialize(1366, 768, "DOTanks", false, false);
	theWorld.SetGameManager(new CGameManager());
	theWorld.StartGame();
	theWorld.Destroy();
	
	return 0;
}
