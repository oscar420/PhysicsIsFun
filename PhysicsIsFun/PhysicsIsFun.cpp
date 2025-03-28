#include <windows.h>
#include <chrono>
#include <thread>
#include "Game.h"

Game game;

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_KEYDOWN:
        game.key_down(static_cast<int>(wParam));  // ✅ Track pressed key
        InvalidateRect(hwnd, nullptr, FALSE);         // ✅ Trigger redraw
        return 0;

    case WM_KEYUP:
        game.key_up(static_cast<int>(wParam));   // ✅ Remove released key
        return 0;

    case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            game.framebuffer.clear(0xFFFFFFFF);
            game.draw_r(hdc);                              // 🎨 Redraw game
            EndPaint(hwnd, &ps);
            return 0;
    }

    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Declare timing constants
    const int TARGET_FPS = 60;
    const std::chrono::milliseconds frame_duration(1000 / TARGET_FPS);
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PhysicsIsFun";
    RegisterClass(&wc);

    RECT rect = { 0, 0, 1000, 1000 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    HWND hwnd = CreateWindow(L"PhysicsIsFun", L"Physics is Fun!",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             windowWidth, windowHeight,
                             nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Initialize game
    game.Initialize(hwnd);

    // Message loop
    MSG msg = {};
    auto last_frame = std::chrono::steady_clock::now();

    // ✅ Main game loop
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame);

            if (elapsed >= frame_duration)
            {
                last_frame = now;

                // ✅ Update physics, movement
                game.update();
                
                InvalidateRect(hwnd, nullptr, FALSE);  // ✅ Redraw
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Optional, reduces CPU usage
            }
        }
    }

    return 0;
}