//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include "window.hpp"

static char WINDOW_NAME[] = "Test";

static LRESULT CALLBACK _wndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	
	default:
		return ::DefWindowProc(wnd, message, wParam, lParam);
	}
	
	return 0;
}

Window::Window(HINSTANCE instance) : _instance(instance), Service("Test1")
{
}

Window::~Window()
{

}

void Window::_register()
{
	WNDCLASSEXA wcex{ 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = _wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _instance;
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszClassName = WINDOW_NAME;

	_atom = ::RegisterClassExA(&wcex);
}

bool Window::create(int cmdShow)
{
	_register();
	
	if (!_atom)
		return false;

	_wnd = ::CreateWindowA(WINDOW_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		_instance,
		nullptr);

	if (!_wnd)
		return false;

	ShowWindow(_wnd, cmdShow);
	UpdateWindow(_wnd);
	
	return true;
}

bool Window::run()
{
	MSG msg;

	while (::GetMessage(&msg, nullptr, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return msg.wParam == 0 ? true : false;
}
