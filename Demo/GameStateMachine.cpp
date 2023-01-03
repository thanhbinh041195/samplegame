#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "GamePlayState.h"
#include"GameOverState.h"


GameStateMachine::GameStateMachine()
{
	m_isExitCurrentState = false;
	m_isEnterNextState = false;
}


GameStateMachine::~GameStateMachine()
{
	m_currentState->OnExit();
}

GameStateMachine* GameStateMachine::instance = nullptr;

GameStateMachine* GameStateMachine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameStateMachine();
	}
	return instance;
}

void GameStateMachine::Init()
{
	ResourceManager::GetInstance()->Init("../Resources/Data.bin");	
	m_isExitCurrentState = false;
	m_isEnterNextState = false;
	m_currentState = new GameOverState(k_Play);
}

void GameStateMachine::Update(float deltaTime)
{
	m_currentState->OnUpdate(deltaTime);
	if (m_isExitCurrentState)
	{
		m_isExitCurrentState = false;
		m_currentState->OnExit();
		m_isEnterNextState = true;
	}
	if (m_isEnterNextState)
	{
		m_isEnterNextState = false;
		m_currentState = m_nextState;
		m_currentState->OnInit();
	}
}

void GameStateMachine::Render(Graphics* graphics, Device* device)
{
	graphics->ClearScreen();
	m_currentState->OnRender(graphics, device);
}

void GameStateMachine::SwitchState(State* state)
{
	m_nextState = state;
	m_isExitCurrentState = true;
}

void GameStateMachine::DestroyInstance()
{
	delete instance;
}
