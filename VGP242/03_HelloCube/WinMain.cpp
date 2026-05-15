#include <VisualEngine/Inc/VisualEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	VisualEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	VisualEngine::App& myApp = VisualEngine::MainApp();

	// needstates
	myApp.AddState<ShapeState>("ShapeState");
	myApp.Run(config);

	return 0;
}