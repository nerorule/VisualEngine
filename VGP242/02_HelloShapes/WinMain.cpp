#include <VisualEngine/Inc/VisualEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	VisualEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	VisualEngine::App& myApp = VisualEngine::MainApp();

	// need states
	myApp.AddState<ShapeStates>("ShapeStates");
	myApp.AddState<QuadState>("QuadState");
	myApp.AddState<DiamondState>("DiamondState");
	myApp.AddState<HeartState>("HeartState");
	myApp.Run(config);

	return 0;
}