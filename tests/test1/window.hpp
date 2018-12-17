//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#pragma once

#include "win32api.hpp"
#include <logService.hpp>

/// Window for the test case.
class Window : public wls::Service
{
public:
	/// Constructor.
	Window(HINSTANCE instance);
	
	/// Destructor.
	~Window();

	bool create(int cmdShow);
	bool run();

private:
	void _register();

private:
	ATOM _atom{ 0 };
	HINSTANCE _instance{ nullptr };
	HWND _wnd{ nullptr };
};
