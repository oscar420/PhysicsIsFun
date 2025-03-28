#include "Inputs.h"
#include <conio.h>  // Windows only (use termios.h for Linux)

void Inputs::HandleInput(Warrior& player) {
    /*if (_kbhit()) {
        char key = _getch();
        if (key == 'a') { player.ApplyForce(-1, 0); player.moving = true; }
        if (key == 'd') { player.ApplyForce(1, 0); player.moving = true; }
        if (key == 'w' && player.position.y == FrameBuffer::SCREEN_HEIGHT - 8) {
            player.ApplyForce(0, -5);
        }
    } else {
        player.moving = false;
    }*/
}
