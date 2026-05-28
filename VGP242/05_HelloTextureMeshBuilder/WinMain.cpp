#include <VisualEngine/Inc/VisualEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	VisualEngine::AppConfig config;
	config.appName = L"Hello Mesh Builder";

	VisualEngine::App& myApp = VisualEngine::MainApp();

	// need states
	myApp.AddState<ShapeStates>("ShapeStates");
	myApp.Run(config);

	return 0;
}