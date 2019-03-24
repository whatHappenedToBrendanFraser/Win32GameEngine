#include <vector>
#include "Player.h"
#include "InputStream.h"
#include "Log.h"
#include "Graphics.h"

int x, y;

Player::Player(int x_, int y_)
{
    InputStream::addFilter('A', "");
    InputStream::addFilter('D', "");
    InputStream::addFilter('W', "");
    InputStream::addFilter('S', "");
}

void Player::update()
{
    if (InputStream::isPressed('A'))
        x--;
    if (InputStream::isPressed('D'))
        x++;
    if (InputStream::isPressed('W'))
        y--;
    if (InputStream::isPressed('S'))
        y++;
}

void Player::move(int xDist, int yDist)
{

}