#include "Game.h"

#include <iostream>

Game::Game()
    : framebuffer(128, 128), // Default size, will update after loading image
      renderer(&framebuffer),
      image(128, 128) {}

void Game::Initialize(HWND hwnd)
{
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;
    
    std::string bmpFile = "C:\\Users\\ocarrion\\warrior.bmp";  // Adjust path if needed
    if (!image.load_bmp(bmpFile)) {
        std::cerr << "Failed to load warrior image!" << std::endl;
        return;
    }

    // Resize framebuffer to match actual window client size
    framebuffer.resize(width, height);
    
    // Ensure player is properly assigned
    player = new Warrior(&framebuffer, image.get_pixels(), image.get_width(), image.get_height());

    if (!player) {
        std::cerr << "Error: Player initialization failed!" << std::endl;
        return;
    }

    std::cerr << "✅ Player initialized at (" << player->GetX() << ", " << player->GetY() << ")" << std::endl;
}

void Game::draw_r(HDC hdc)
{
    framebuffer.clear(0xFFFFFFFF); // ✅ Ensure screen clears (black background)
    player->Draw();              // ✅ Draw player AFTER clearing
    renderer.Draw(hdc);
}

void Game::update() const
{
    handle_input();
    player->apply_force_and_module_position(1.0f / 60.0f);
}

void Game::handle_input() const
{
    if (activeKeys.count('A')) {
        player->move(-1, 1.0f / 60.0f); // ✅ Move left
    }
    if (activeKeys.count('D')) {
        player->move(1, 1.0f / 60.0f);  // ✅ Move right
    }
    if (activeKeys.count(VK_SPACE)) {
        player->jump();  // ✅ Jump
    }
    else
    {
         player->set_direction(0);
    }
}

void Game::key_down(int key)
{
    activeKeys.insert(key);
}

void Game::key_up(int key)
{
    activeKeys.erase(key);
}
