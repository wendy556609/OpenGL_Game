#include "GameManager.h"

void GameManager::SetLevel() {
	if (_enemyCount_1 < 4) {
		Level = 1;
	}
	else if (_enemyCount_2 < 2 && _enemyCount_1 >= 4) {
		Level = 2;
	}
	else if (_enemyCount_2 >= 2) {
		Level = 3;
	}
}