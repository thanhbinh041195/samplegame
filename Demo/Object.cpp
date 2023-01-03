#include "Object.h"
#include"ResourceManager.h"

Object::Object(Type type,Size size)
{
	ResourceManager* resource = ResourceManager::GetInstance();
	m_type = type;
	m_size = size;
	m_velocity.x = 0;
	m_velocity.y = 50;
	if (m_type == k_Player)
	{
		if (size == k_big)
		{
			m_power = 3;
			m_image = resource->getImageById('3');
			m_animation = resource->getAnimationByID('0');
		}
		else if (size == k_medium)
		{
			m_power = 2;
			m_image = resource->getImageById('4');
			m_animation = resource->getAnimationByID('1');
		}
		else if (size == k_small)
		{
			m_power = 1;
			m_image = resource->getImageById('5');
			m_animation = resource->getAnimationByID('2');
		}
	}
	else if (m_type == k_enemy)
	{
		if (size == k_big)
		{
			m_power = 3;
			m_image = resource->getImageById('6');
			m_animation = resource->getAnimationByID('3');
		}
		else if (size == k_medium)
		{
			m_power = 2;
			m_image = resource->getImageById('7');
			m_animation = resource->getAnimationByID('4');
		}
		else if (size == k_small)
		{
			m_power = 1;
			m_image = resource->getImageById('8');
			m_animation = resource->getAnimationByID('5');
		}
	}
	m_animation->PlayAnimation();
}

Vector2 Object::getPosition()
{
	return m_position;
}
void Object::setPosition(Vector2 position)
{
	m_position = position;
}
float Object::getVelocity()
{
	return m_velocity.y;
}

void Object::setVelocity(float Velocity)
{
	m_velocity.y = Velocity;
}

Animation * Object::GetAnimation()
{
	return m_animation;
}

Image * Object::GetImage()
{
	return m_image;
}

void Object::Update(float deltaTime)
{
	if (m_type == k_Player)
	{
		m_position.y -= m_velocity.y * deltaTime;
	}
	else if (m_type == k_enemy)
	{
		m_position.y += m_velocity.y * deltaTime;
	}
}

void Object::Render(Graphics* graphics)
{
	graphics->SetColor(1.0f, 0.0f, 0.0f); //set red color
	graphics->DrawArc(m_position.x + 5, m_position.y + 30, 25);
	graphics->DrawAnimation(m_animation ,m_position.x, m_position.y, 2);
}

Type Object::GetType()
{
	return m_type;
}

int Object::GetPower()
{
	return m_power;
}

Object::~Object()
{

}
