#pragma once

namespace VisualEngine::Core
{
	class Window
	{
	public:
		void Intialize(HINSTANCE instance, const std::wstring& appName, uint32_t width, uint32_t height);
		void Terminate();

		void ProcessMessage();

		HWND GetWindowHandle() const;
		bool IsActive() const;

	private:
		HINSTANCE mInstance = nullptr;
		HWND mWindow = nullptr;
		RECT mScreenRect{};
		std::wstring mAppName;
		bool mIsActive = false;
	};
}