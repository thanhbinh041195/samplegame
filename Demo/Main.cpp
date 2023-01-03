#include <stdlib.h>
#include"GameStateMachine.h"
#include"ResourceManager.h"
//#include <vld.h>



const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 800;

/**
* The main Program
**/
int main()
{
	// Init Game 
	srand(time(NULL));
	Device *device = Device::GetInstance();
	device->InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	Graphics *graphics = device->GetGraphics();
	InputManager *inputManager = InputManager::GetInstance();
	GameStateMachine* machine = GameStateMachine::GetInstance();
	ResourceManager* resource = ResourceManager::GetInstance();
	machine->Init();
	// Game Loop
	while (device->IsRunning())
	{
		// Update game status 
		// deltaTime = time of that frame
		float deltaTime = GameTime::GetFrameTime();

		TouchData *touchData = inputManager->GetTouch();

		if (touchData != NULL
			&& (touchData->state == TOUCH_DOWN )
			)
		{
			// handle touch
			Logger::Debug("Touch::", "Touch state: %d x: %f y: %f", touchData->state, touchData->position.x, touchData->position.y);
		}


		//Update
		machine->Update(deltaTime);
		// Render the scene
		machine->Render(graphics , device);
    }

	//Exit Game
	machine->DestroyInstance();
	resource->DestroyInstance();
    InputManager::DestroyInstance();
    Device::DestroyInstance();
    return 0;
}