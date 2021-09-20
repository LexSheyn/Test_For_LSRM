#include "stdafx.h"

#include "Window.h"

int main()
{
	// Hiding console
	HWND console_window = GetConsoleWindow();
	ShowWindow(console_window, SW_HIDE);

	Window window;

	window.run();

	// Showing console
	ShowWindow(console_window, SW_SHOW);
	SetForegroundWindow(console_window);

	return 0;
}