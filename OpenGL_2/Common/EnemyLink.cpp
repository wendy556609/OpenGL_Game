#include "EnemyLink.h"
EnemyLink::EnemyLink(mat4& matModelView, mat4& matProjection, GLuint shaderHandle, int totalCount_1, int totalCount_2, int totalCount_3) {
	_UseHead = _UseTail = NULL;

	//Enemy1
	_totalCount_1 = totalCount_1;
	_Head_1 = _Get = _Tail_1 = NULL;
	_Head_1 = new Enemy1(matModelView, matProjection);
	_Tail_1 = _Head_1;
	for (int i = 1; i < _totalCount_1; i++)
	{
		_Get = new Enemy1(matModelView, matProjection);
		_Get->next = NULL;
		_Tail_1->next = _Get;
		_Tail_1 = _Get;
	}
	//Enemy2
	_totalCount_2 = totalCount_2;
	_Head_2 = _Get = _Tail_2 = NULL;
	_Head_2 = new Enemy2(matModelView, matProjection);
	_Tail_2 = _Head_2;
	for (int i = 1; i < _totalCount_2; i++)
	{
		_Get = new Enemy2(matModelView, matProjection);
		_Get->next = NULL;
		_Tail_2->next = _Get;
		_Tail_2 = _Get;
	}

	//Enemy3
	_totalCount_3 = totalCount_3;
	_Head_3 = new Enemy3(matModelView, matProjection);
	_Head_3->next = NULL;
}

EnemyLink::~EnemyLink() {
	//Enemy1
	_Get = _Head_1;
	while (_Get != NULL) {
		_Head_1 = _Get->next;
		delete _Get;
		_Get = _Head_1;
	}
	delete _Head_1;
	//Enemy2
	_Get = _Head_2;
	while (_Get != NULL) {
		_Head_2 = _Get->next;
		delete _Get;
		_Get = _Head_2;
	}
	delete _Head_2;

	//UseEnemy
	_UseGet = _UseHead;
	while (_UseGet != NULL) {
		_UseHead = _UseGet->next;
		delete _UseGet;
		_UseGet = _UseHead;
	}
	delete _UseHead;

	if (_Head_3 != NULL)delete _Head_3;
}

//©I¥sEnemy
void EnemyLink::UseEnemy(float delta) {
	Enemy *shootGet;
	if (gameManager->Level >= 1)ShootTime_1 += delta;
	if (gameManager->Level >= 2)ShootTime_2 += delta;
	
			if (gameManager->Level >= 1 && ShootTime_1 >= 2.0f && (useCount_1 < _totalCount_1)) {
				if (_UseHead == NULL) {
					shootGet = _Head_1;
					_Head_1 = _Head_1->next;
					shootGet->next = NULL;
					_UseTail = _UseHead = shootGet;
					useCount_1++;
					shootGet->SetEnemy();
					ShootTime_1 = 0;
				}
				else {
					shootGet = _Head_1;
					if (_Head_1 != NULL)_Head_1 = _Head_1->next;
					else _Tail_1 = _Head_1;
					if (shootGet != NULL) {
						shootGet->next = NULL;
						_UseTail->next = shootGet;
						_UseTail = shootGet;
						useCount_1++;
						shootGet->SetEnemy();
						ShootTime_1 = 0;
					}
				}				
			}
			if (gameManager->Level >= 2 && ShootTime_2 >= 3.0f && (useCount_2 < _totalCount_2)) {
				if (_UseHead == NULL) {
					shootGet = _Head_2;
					_Head_2 = _Head_2->next;
					shootGet->next = NULL;
					_UseTail = _UseHead = shootGet;
					useCount_2++;
					shootGet->SetEnemy();
					ShootTime_2 = 0;
				}
				else {
					shootGet = _Head_2;
					if (_Head_2 != NULL)_Head_2 = _Head_2->next;
					else _Tail_2 = _Head_2;
					if (shootGet != NULL) {
						shootGet->next = NULL;
						_UseTail->next = shootGet;
						_UseTail = shootGet;
						useCount_2++;
						shootGet->SetEnemy();
						ShootTime_2 = 0;
					}
				}
			}
			if (gameManager->Level >= 3 && (useCount_3 < _totalCount_3)) {
				if (_UseHead == NULL) {
					shootGet = _Head_3;
					_Head_3 = _Head_3->next;
					shootGet->next = NULL;
					_UseTail = _UseHead = shootGet;
					useCount_3++;
					shootGet->SetEnemy();
				}
				else {
					shootGet = _Head_3;
					if (_Head_3 != NULL)_Head_3 = _Head_3->next;
					if (shootGet != NULL) {
						shootGet->next = NULL;
						_UseTail->next = shootGet;
						_UseTail = shootGet;
						useCount_3++;
						shootGet->SetEnemy();
					}
				}
			}
}
//ÀË¬dEnemy
void EnemyLink::DetectEnemy(float delta) {
	int Count = 0;
	_Link = NULL;
	_UseGet = _UseHead;
	while (_UseGet != NULL) {
		_UseGet->Update(delta);
		_UseGet->gameManager = gameManager;
		_UseGet->_bulletLink->playerCollider = playerCollider;
		//_UseGet->_bulletLink->playerProtect = playerProtect;
		_UseGet->playerCollider = playerCollider;
		if (_UseGet->GetPos().y <= -15.0f) {
			RecycleEnemy(_UseGet->Num);
		}
		else {
			_Link = _UseGet;
			_UseGet = _UseGet->next;
		}
	}
}
//¦^¦¬Enemy
void EnemyLink::RecycleEnemy(int num) {
	Enemy* recycleGet;
	switch (num)
	{
	case 1:
		if (_Head_1 == NULL) {
			recycleGet = _UseGet;
			_UseGet = _UseGet->next;
			if (_UseGet == NULL)_UseTail = _Link;
			if (_Link != NULL)_Link->next = _UseGet;
			else _UseHead = _UseGet;
			recycleGet->next = NULL;
			_Tail_1 = _Head_1 = recycleGet;
			useCount_1--;

		}
		else {
			recycleGet = _UseGet;
			_UseGet = _UseGet->next;
			if (_UseGet == NULL)_UseTail = _Link;
			if (_Link != NULL)_Link->next = _UseGet;
			else _UseHead = _UseGet;
			recycleGet->next = NULL;
			_Tail_1->next = recycleGet;
			_Tail_1 = recycleGet;
			useCount_1--;
		}
		break;
	case 2:
		if (_Head_2 == NULL) {
			recycleGet = _UseGet;
			_UseGet = _UseGet->next;
			if (_UseGet == NULL)_UseTail = _Link;
			if (_Link != NULL)_Link->next = _UseGet;
			else _UseHead = _UseGet;
			recycleGet->next = NULL;
			_Tail_2 = _Head_2 = recycleGet;
			useCount_2--;

		}
		else {
			recycleGet = _UseGet;
			_UseGet = _UseGet->next;
			if (_UseGet == NULL)_UseTail = _Link;
			if (_Link != NULL)_Link->next = _UseGet;
			else _UseHead = _UseGet;
			recycleGet->next = NULL;
			_Tail_2->next = recycleGet;
			_Tail_2 = recycleGet;
			useCount_2--;
		}
		break;
	case 3:
		if (_Head_3 == NULL) {
			recycleGet = _UseGet;
			_UseGet = _UseGet->next;
			if (_UseGet == NULL)_UseTail = _Link;
			if (_Link != NULL)_Link->next = _UseGet;
			else _UseHead = _UseGet;
			recycleGet->next = NULL;
			_Head_3 = recycleGet;
			useCount_3--;
		}
		break;
	default:
		break;
	}
	
}

void EnemyLink::Draw() {
	Enemy* drawGet;
	drawGet = _UseHead;
	while (drawGet != NULL) {
		drawGet->Draw();
		drawGet = drawGet->next;
	}
}

void EnemyLink::Update(float delta) {
	if ((useCount_1+ useCount_2 + useCount_3)<(_totalCount_1 + _totalCount_2 + _totalCount_3)) {
		UseEnemy(delta);
	}
	DetectEnemy(delta);
}