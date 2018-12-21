//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include "window.hpp"

int APIENTRY WinMain(HINSTANCE instance, [[maybe_unused]] HINSTANCE prevInstance, [[maybe_unused]] LPSTR cmdLine, int cmdShow)
{
	Window window(instance);

	if (window.create(cmdShow))
	{
		window.logInformation("Hello Jamie.");
		return window.run() ? 0 : 1;
	}
	
	return 1;
}
