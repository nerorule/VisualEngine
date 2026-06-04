#pragma once

namespace VisualEngine::Graphics::DebugUI
{
	enum class Theme
	{
		Classic,
		Dark,
		Light
	};

	void StaticInitialize(HWND window, bool docking = false, bool multiViewPoint = false);
	void StaticTerminate();
	void SetTheme(Theme theme);

	void BeginDraw();
	void EndDraw();
}