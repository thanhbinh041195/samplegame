#include "GamePlayState.h"
#include "ResourceManager.h"
#include "Object.h"
#include "GameOverState.h"

ResourceManager* resource = ResourceManager::GetInstance();
GamePlayState::GamePlayState()
{
	OnInit();
	m_playerTimer = 0;
	m_enemyTimer = 0;
	m_playerHealth = 100;
	m_enemyHeatlh = 100;
	isFirstTimeList1 = true;
	isFirstTimeList2 = true;
	isFirstTimeList3 = true;
	isInited = false;
	totalpower1 = 0;
	totalpower2 = 0;
	totalpower3 = 0;
}


GamePlayState::~GamePlayState()
{
}

void GamePlayState::OnInit()
{
	//Init backgroup and hud
	m_backGround = resource->getImageById('0');
	m_playerHud = resource->getImageById('1');
	m_enemyHud = resource->getImageById('2');
	m_playerName = resource->getFontById('1');
	m_enemyName = resource->getFontById('0');
	buttonExit = resource->getUIButtonById('1');
	buttonExit->SetPositionButton(Vector2(350, 0));
	buttonExit->SetOnClickCallBack([] {
		Device::GetInstance()->Quit();
	});

	//Init charactor
	CreatePlayerCreep();
	CreateEnemyCreep();
}

void GamePlayState::OnUpdate(float deltaTime)
{
	buttonExit->Update();

	if (m_playerTimer <= 60)
	{
		m_playerTimer+=  20 * deltaTime;
	}
	if (m_playerTimer >= 60 && InputManager::GetInstance()->GetTouch() != NULL
		&& InputManager::GetInstance()->GetTouch()->position.x >= 35 
		&& InputManager::GetInstance()->GetTouch()->position.x <= 430
		&& InputManager::GetInstance()->GetTouch()->position.x >= 100
		&& InputManager::GetInstance()->GetTouch()->position.x <= 650)
	{
		m_playerTimer = 0;
		CreatePlayerCreep();
		InputManager::GetInstance()->GetTouch()->state = TOUCH_UP;
	}
	if (m_enemyTimer <= 60)
	{
		m_enemyTimer += 20 * deltaTime;
	}
	else if (m_enemyTimer >= 60)
	{
		{
			CreateEnemyCreep();
			m_enemyTimer = 0;
		}
	}

	//Update 3 lane creeps
	//player
	for (int i = 0; i< listPlayerLane1.size(); i++)
	{
		listPlayerLane1.at(i)->Update(deltaTime);
		if (listPlayerLane1.at(i)->getPosition().y <= 95)
		{
			m_playerHealth += 10;
			m_enemyHeatlh -= 10;
			listPlayerLane1.erase(listPlayerLane1.begin() + i);
			break;
		}
		if (listPlayerLane1.at(i)->getPosition().y >= 630)
		{
			listPlayerLane1.erase(listPlayerLane1.begin() + i);
			break;
		}
	}
	for (int i = 0; i< listPlayerLane2.size(); i++)
	{
		listPlayerLane2.at(i)->Update(deltaTime);
		if (listPlayerLane2.at(i)->getPosition().y <= 95)
		{
			m_playerHealth += 10;
			m_enemyHeatlh -= 10;
			listPlayerLane2.erase(listPlayerLane2.begin() + i);
			break;
		}
		if (listPlayerLane2.at(i)->getPosition().y >= 630)
		{
			listPlayerLane2.erase(listPlayerLane2.begin() + i);
			break;
		}
	}
	for (int i = 0; i< listPlayerLane3.size(); i++)
	{
		listPlayerLane3.at(i)->Update(deltaTime);
		if (listPlayerLane3.at(i)->getPosition().y <= 95)
		{
			m_playerHealth += 10;
			m_enemyHeatlh -= 10;
			listPlayerLane3.erase(listPlayerLane3.begin() + i);
			break;
		}
		if (listPlayerLane3.at(i)->getPosition().y >= 630)
		{
			listPlayerLane3.erase(listPlayerLane3.begin() + i);
			break;
		}
	}
	//enemy
	for (int i = 0; i< listEnemyLane1.size(); i++)
	{
		listEnemyLane1.at(i)->Update(deltaTime);
		if (listEnemyLane1.at(i)->getPosition().y <= 95)
		{
			listEnemyLane1.erase(listEnemyLane1.begin() + i);
			break;
		}
		if (listEnemyLane1.at(i)->getPosition().y >= 630)
		{
			m_enemyHeatlh += 10;
			m_playerHealth -= 10;
			listEnemyLane1.erase(listEnemyLane1.begin() + i);
			break;
		}
	}
	for (int i = 0; i< listEnemyLane2.size(); i++)
	{
		listEnemyLane2.at(i)->Update(deltaTime);
		if (listEnemyLane2.at(i)->getPosition().y <= 95)
		{
			listEnemyLane2.erase(listEnemyLane2.begin() + i);
			break;
		}
		if (listEnemyLane2.at(i)->getPosition().y >= 630)
		{
			m_enemyHeatlh += 10;
			m_playerHealth -= 10;
			listEnemyLane2.erase(listEnemyLane2.begin() + i);
			break;
		}
	}
	for (int i = 0; i< listEnemyLane3.size(); i++)
	{
		listEnemyLane3.at(i)->Update(deltaTime);
		if (listEnemyLane3.at(i)->getPosition().y <= 95)
		{
			listEnemyLane3.erase(listEnemyLane3.begin() + i);
			break;
		}
		if (listEnemyLane3.at(i)->getPosition().y >= 630)
		{
			m_enemyHeatlh += 10;
			m_playerHealth -= 10;
			listEnemyLane3.erase(listEnemyLane3.begin() + i);
			break;
		}
	}

	//Game play update
	UpdateGame(listPlayerLane1, listEnemyLane1, totalpower1, isFirstTimeList1);
	UpdateGame(listPlayerLane2, listEnemyLane2, totalpower2, isFirstTimeList2);
	UpdateGame(listPlayerLane3, listEnemyLane3, totalpower3, isFirstTimeList3);

	//Gameover
	if(m_enemyHeatlh <= 0 || m_playerHealth <= 0)
	{
		GameOverState *nextState = new GameOverState(k_Over);
		GameStateMachine::GetInstance()->SwitchState(nextState);
	}

	isInited = true;
}

void GamePlayState::OnRender(Graphics* graphics, Device* device)
{
	//Draw backgroup and hud
	graphics->DrawImage(m_backGround, 0, 0, 0);
	graphics->DrawImage(m_playerHud, 0, 710, 0);
	graphics->DrawImage(m_enemyHud, 0, 0, 0);
	graphics->DrawTextWithFont(m_playerName, 10, 750, "Player");
	graphics->DrawTextWithFont(m_enemyName, 10, 25, "Insanse AI");
	graphics->DrawUIButton(buttonExit);

	//player health
	graphics->SetColor(0.0f, 1.0f, 0.0f);
	graphics->FillRect(320, 700, m_playerHealth, 30);
	//enemy health
	graphics->SetColor(0.0f, 1.0f, 0.0f);
	graphics->FillRect(40, 70, m_enemyHeatlh, 30);

	//Timer
	graphics->SetColor(1.0f, 0.0f, 0.0f);
	//enemies
	graphics->DrawRect(210, 12, 60, 10);
	graphics->FillRect(210, 12, m_enemyTimer, 10);
	graphics->DrawImage(m_enemyImage, 245, 20, 2);
	//player
	graphics->DrawRect(210, 770, 60, 10);
	graphics->FillRect(210, 770, m_playerTimer, 10);
	graphics->DrawImage(m_playerImage, 245, 705, 2);

	//Render 3 lane creep
	for (int i = 0; i< listPlayerLane1.size(); i++)
	{
		listPlayerLane1.at(i)->Render(graphics);
	}
	for (int i = 0; i< listPlayerLane2.size(); i++)
	{
		listPlayerLane2.at(i)->Render(graphics);
	}
	for (int i = 0; i< listPlayerLane3.size(); i++)
	{
		listPlayerLane3.at(i)->Render(graphics);
	}

	for (int i = 0; i< listEnemyLane1.size(); i++)
	{
		listEnemyLane1.at(i)->Render(graphics);
	}
	for (int i = 0; i< listEnemyLane2.size(); i++)
	{
		listEnemyLane2.at(i)->Render(graphics);
	}
	for (int i = 0; i< listEnemyLane3.size(); i++)
	{
		listEnemyLane3.at(i)->Render(graphics);
	}
}

void GamePlayState::CreatePlayerCreep()
{
	TouchData *touchData = InputManager::GetInstance()->GetTouch();
	int size = rand() % 2 + 0;
	if(size == k_big)
	{
		m_playerImage = resource->getImageById('3');
	}
	else if (size == k_medium)
	{
		m_playerImage = resource->getImageById('4');
	}
	else if (size == k_small)
	{
		m_playerImage = resource->getImageById('5');	
	}
	m_creep = make_shared<Object>(k_Player, Size(size));
	if (touchData != NULL)
	{
		if (touchData->position.x >= 35 && touchData->position.x <= 170
			&& touchData->position.y >= 100 && touchData->position.y <= 650)
		{
			m_creep->setPosition(Vector2(90, 600));
			listPlayerLane1.push_back(move(m_creep));
		}
		if (touchData->position.x > 170 && touchData->position.x <= 300
			&& touchData->position.y >= 100 && touchData->position.y <= 650)
		{
			m_creep->setPosition(Vector2(230, 600));
			listPlayerLane2.push_back(move(m_creep));
		}
		if (touchData->position.x >= 300 && touchData->position.x <= 440
			&& touchData->position.y >= 100 && touchData->position.y <= 650)
		{
			m_creep->setPosition(Vector2(360, 600));
			listPlayerLane3.push_back(move(m_creep));
		}
		
	}
}

void GamePlayState::CreateEnemyCreep()
{
	if (isInited)
	{
		int size = rand() % 2 + 0;
		int lane = rand() % 3 + 1;
		if (size == k_big)
		{
			m_enemyImage = resource->getImageById('6');
		}
		else if (size == k_medium)
		{
			m_enemyImage = resource->getImageById('7');
		}
		else if (size == k_small)
		{
			m_enemyImage = resource->getImageById('8');
		}
		m_creep = make_shared<Object>(k_enemy, Size(size));
		if (lane == 1)
		{
			m_creep->setPosition(Vector2(90, 100));
			listEnemyLane1.push_back(move(m_creep));
		}
		else if (lane == 2)
		{
			m_creep->setPosition(Vector2(230, 100));
			listEnemyLane2.push_back(move(m_creep));
		}
		else if (lane == 3)
		{
			m_creep->setPosition(Vector2(360, 100));
			listEnemyLane3.push_back(move(m_creep));
		}
	}
}

void GamePlayState::UpdateGame(vector<shared_ptr<Object>>listPlayerLane1, vector<shared_ptr<Object>>listEnemyLane1, int totalpower1, bool first)
{
	if (listPlayerLane1.size() > 0 && listEnemyLane1.size() > 0)
	{
		if (first)
		{
			totalpower1 = listPlayerLane1.at(0)->GetPower() - listEnemyLane1.at(0)->GetPower();
			first == false;
		}
		for (int i = 1; i < listPlayerLane1.size(); i++)
		{
			if (listPlayerLane1.at(i - 1)->getPosition().y + 50 >= listPlayerLane1.at(i)->getPosition().y
				&& listPlayerLane1.at(i - 1)->getPosition().y - 25 <= listPlayerLane1.at(i)->getPosition().y && (i + 1))
			{
				listPlayerLane1.at(i)->setVelocity(listPlayerLane1.at(0)->getVelocity());
				totalpower1 += listPlayerLane1.at(i)->GetPower();
			}
			else
			{
				listPlayerLane1.at(i)->setVelocity(50);
			}
		}
		for (int i = 1; i < listEnemyLane1.size(); i++)
		{
			if (listEnemyLane1.at(i - 1)->getPosition().y + 25 >= listEnemyLane1.at(i)->getPosition().y
				&& listEnemyLane1.at(i - 1)->getPosition().y - 50 <= listEnemyLane1.at(i)->getPosition().y && (i + 1))
			{
				listEnemyLane1.at(i)->setVelocity(listEnemyLane1.at(0)->getVelocity());
				totalpower1 -= listEnemyLane1.at(i)->GetPower();
			}
			else
			{
				listEnemyLane1.at(i)->setVelocity(50);
			}
		}
		if(listPlayerLane1.at(0)->getPosition().y + 50 >= listEnemyLane1.at(0)->getPosition().y
			&& listPlayerLane1.at(0)->getPosition().y - 50 <= listEnemyLane1.at(0)->getPosition().y)
		{
			if (totalpower1 == 0)
			{
				listPlayerLane1.at(0)->setVelocity(0);
				listEnemyLane1.at(0)->setVelocity(0);
			}
			else if (totalpower1 > 0)
			{
				listPlayerLane1.at(0)->setVelocity(20);
				listEnemyLane1.at(0)->setVelocity(-20);
			}
			else if (totalpower1 < 0)
			{
				listPlayerLane1.at(0)->setVelocity(-20);
				listEnemyLane1.at(0)->setVelocity(20);
			}
		}
		else
		{
			listPlayerLane1.at(0)->setVelocity(50);
			listEnemyLane1.at(0)->setVelocity(50);
		}
	}
}

void GamePlayState::OnExit()
{
	delete this;
}
