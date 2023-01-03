#pragma once
#include"State.h"

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();
	static GameStateMachine* GetInstance();
	void Init();
	void Update(float deltaTime);
	void Render(Graphics* graphics, Device* device);
	void SwitchState(State* state);
	void DestroyInstance();
private:
	State* m_currentState;
	State* m_nextState;
	bool m_isExitCurrentState;
	bool m_isEnterNextState;
	static GameStateMachine* instance;
};

