#pragma once
#include"State.h"

using namespace std;

class GamePlayState : public State
{
public:
	GamePlayState();
	~GamePlayState();
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnRender(Graphics* graphics, Device* device) override;
	void OnExit() override;
	void CreatePlayerCreep();
	void UpdateGame(vector<shared_ptr<Object>>, vector<shared_ptr<Object>>, int, bool);
	void CreateEnemyCreep();
private:
	int m_playerHealth, m_enemyHeatlh, totalpower1, totalpower2, totalpower3;
	bool isFirstTimeList1, isFirstTimeList2, isFirstTimeList3, isInited;
	Font *m_playerName, *m_enemyName;
	vector<shared_ptr<Object>> listEnemyLane1, listEnemyLane2, listEnemyLane3,listPlayerLane1, listPlayerLane2 , listPlayerLane3;
	shared_ptr<Object> m_creep;
	UIButton *buttonExit;
	Image *m_playerImage, *m_enemyImage;
	float m_playerTimer, m_enemyTimer;
	Type m_type;
	Size m_size;
};

