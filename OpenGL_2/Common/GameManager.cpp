#include "GameManager.h"

void GameManager::SetLevel() {
	if (_enemyCount_1 >= 4) {
		Level = 2;
	}
	if (_enemyCount_2 >= 2) {
		Level = 3;
	}
}