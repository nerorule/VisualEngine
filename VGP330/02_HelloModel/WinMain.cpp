#include "GameState.h"

using namespace VisualEngine;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Final Project";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	return 0;
}