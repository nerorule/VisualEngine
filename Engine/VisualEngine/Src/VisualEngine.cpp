#include "Precompiled.h"
#include "VisualEngine.h"

VisualEngine::App& VisualEngine::MainApp()
{
	static App sApp;
	return sApp;
}