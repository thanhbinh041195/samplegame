#pragma once
#include"State.h"

enum Result
{
	k_Play,
	k_Over
};

class GameOverState : public State
{
public:
	GameOverState(Result);
	~GameOverState();
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnRender(Graphics* graphics, Device* device) override;
	void OnExit() override;
private:
	UIButton *buttonReset;
	Font *m_Result;
	Result m_State;
};

