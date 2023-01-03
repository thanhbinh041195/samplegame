#pragma once
#include <GameEngine.h>
#include"Object.h"

using namespace std;

class State
{
public:
	State();
	virtual ~State();
	virtual void OnInit() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender(Graphics* graphics, Device* device) = 0;
	virtual void OnExit() = 0;
protected:
	Image* m_backGround, *m_playerHud, *m_enemyHud;
};