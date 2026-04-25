#pragma once

namespace VisualEngine::Core
{
	class WindowMessageHandler
	{
	public:
		using CallBack = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

		void Hook(HWND window, CallBack cb);
		void Unhook();

		LRESULT ForwardMessage(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND mWindow = nullptr;
		CallBack mPreviousCallBack = nullptr;
	};
}