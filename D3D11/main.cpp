#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	// Define window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MyWindowClass";
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// Register window class
	RegisterClassEx(&wc);

	// Define window
	HWND hwnd = CreateWindowEx(
		0,
		L"MyWindowClass",
		L"D3D11",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Show and update window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Game loop
	MSG msg = { 0 };
	while (GetMessage(&msg, nullptr, NULL, NULL))
	{
		TranslateMessage(&msg); // translates raw input into character codes
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}