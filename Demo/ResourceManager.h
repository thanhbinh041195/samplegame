#pragma once
#include"GameStateMachine.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* GetInstance();
	void Init(const char *path);
	Image* getImageById(char id);
	Font* getFontById(char id);
	UIButton* getUIButtonById(char id);
	Animation* getAnimationByID(char id);
	void DestroyInstance();
private:
	static ResourceManager* instance;
	map<char, Image*> images;
	map<char, Font*> font;
	map<char, UIButton*> button;
	map<char, Animation*> listAnimation;
};

