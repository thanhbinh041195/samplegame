#pragma once
#include<memory>
#include"GameEngine.h"
#include<map>
#include<vector>
#include <ctime>

using namespace std;

enum Type
{
	k_Player,
	k_enemy
};

enum Size
{
	k_big,
	k_medium,
	k_small
};

class Object
{
public:
	Object(Type,Size);
	~Object();
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	Type GetType();
	Vector2 getPosition();
	void setPosition(Vector2);
	float getVelocity();
	void setVelocity(float);
	Animation* GetAnimation();
	Image* GetImage();
	int GetPower();
private:
	int m_power;
	Vector2 m_position, m_velocity;
	Image* m_image;
	Animation* m_animation;
	bool isEnable;
	Type m_type;
	Size m_size;
};

