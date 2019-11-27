#pragma once
#include "../Header/Angel.h"
class GameManager
{
private:
	bool _End = false;
public:
	int Level = 3;
	int _enemyCount_1 = 0;
	int _enemyCount_2 = 0;

	void SetLevel();
};