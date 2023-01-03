#include "GameOverState.h"
#include"ResourceManager.h"
#include"GamePlayState.h"


GameOverState::GameOverState(Result state)
{
	m_State = state;
	OnInit();
}


GameOverState::~GameOverState()
{

}

void GameOverState::OnInit()
{
	ResourceManager* resource = ResourceManager::GetInstance();
	m_backGround = resource->getImageById('0');
	m_playerHud = resource->getImageById('1');
	m_enemyHud = resource->getImageById('2');
	m_Result = resource->getFontById('1');
	buttonReset = resource->getUIButtonById('1');
	buttonReset->SetPositionButton(Vector2(200, 350));
	buttonReset->SetOnClickCallBack([] {
		GamePlayState *nextState = new GamePlayState();
		GameStateMachine::GetInstance()->SwitchState(nextState);
	});
}

void GameOverState::OnUpdate(float deltaTime)
{
	buttonReset->Update();
}

void GameOverState::OnRender(Graphics * graphics, Device * device)
{
	//Draw backgroup and hud
	graphics->DrawImage(m_backGround, 0, 0, 0);
	graphics->DrawImage(m_playerHud, 0, 710, 0);
	graphics->DrawImage(m_enemyHud, 0, 0, 0);
	graphics->DrawUIButton(buttonReset);
	if (m_State == k_Over)
	{
		graphics->DrawTextWithFont(m_Result, 200, 300, "Replay");
	}
	else if (m_State == k_Play)
	{
		graphics->DrawTextWithFont(m_Result, 200, 300, "Play");
	}
}

void GameOverState::OnExit()
{
	delete this;
}
