#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}

ResourceManager* ResourceManager::instance = 0;

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::Init(const char *path)
{
	FILE *pFile;
	pFile = fopen(path, "r");
	list<Image*> listTempAnimation;
	int numImage, numUI, numFont;
	char PATH[250], PATH1[250], numID;
	if (!pFile)
	{
		printf("Cant open file. \n");
	}
	//Read image and animation form file
	fscanf(pFile, "#IMAGES %d\n", &numImage);
	for (int i = 0; i < numImage; i++)
	{
		fscanf(pFile, "ID: %c\n", &numID);
		fscanf(pFile, "PATH: %s\n", PATH);
		images[numID] = new Image(PATH);
	}

	//Read animation list
	fscanf(pFile, "#ANIMATION %d\n", &numImage);
	for (int i = 0; i < numImage; i++)
	{
		
		fscanf(pFile, "ID: %c\n", &numID);
		fscanf(pFile, "PATH: %s\n", PATH);
		for (int j = 1; j <= 7; j++)
		{
			char buffer[100],temp[10];
			itoa(j, temp, 10);
			strcpy(buffer, PATH);
			strcat(buffer, temp);
			strcat(buffer, ".png");
			listTempAnimation.push_back(new Image(buffer));
		}
		listAnimation[numID] = new Animation(listTempAnimation, 6);
		listTempAnimation.clear();
	}

	//Read uibutton form file
	fscanf(pFile, "#UIBUTTON %d\n", &numUI);
	for (int i = 0; i < numUI; i++)
	{
		fscanf(pFile, "ID: %c\n", &numID);
		fscanf(pFile, "NORMAL_PATH: %s\n", PATH);
		fscanf(pFile, "PRESSED_PATH: %s\n", PATH1);
		button[numID] = new UIButton(PATH, PATH1);;
	}

	//Read font form file
	fscanf(pFile, "#FONT %d\n", &numFont);
	for (int i = 0; i < numFont; i++)
	{
		fscanf(pFile, "ID: %c\n", &numID);
		fscanf(pFile, "PATH: %s\n", PATH);
		font[numID] = new Font(PATH);
	}

	fclose(pFile);
}


Image* ResourceManager::getImageById(char id)
{
	return images[id];
}
Font* ResourceManager::getFontById(char id)
{
	return font[id];
}
UIButton* ResourceManager::getUIButtonById(char id)
{
	return button[id];
}

Animation* ResourceManager::getAnimationByID(char id)
{
	return listAnimation[id];
}

ResourceManager::~ResourceManager()
{
	for (map<char, UIButton*>::iterator i = button.begin(); i != button.end(); i++)
	{
		delete i->second;
	}
	for (map<char, Font*>::iterator i = font.begin(); i != font.end(); i++)
	{
		delete i->second;
	}
	for (map<char, Image*>::iterator i = images.begin(); i != images.end(); i++)
	{
		delete i->second;
	}
	for (std::map<char, Animation*>::iterator i = listAnimation.begin(); i != listAnimation.end(); i++)
	{
		delete i->second;
	}
}

void ResourceManager::DestroyInstance()
{
	delete instance;
}
