//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include "window.hpp"

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, [[maybe_unused]] LPSTR cmdLine, int cmdShow)
{
	Window window(instance);

	if (window.create(cmdShow))
	{
		window.logInformation(42, "Hello Jamie.", 1.0f);
		return window.run() ? 0 : 1;
	}
	
	return 1;
}
