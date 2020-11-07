#pragma once
#include <libheart.h>

extern u16 keys_pressed;
extern u16 keys_released;
extern u16 keys_pressedonce;
extern u16 keys_repeat;

class BaseClass
{
public:
    virtual void Run(int param) = 0;

private:
    virtual void Render(int param) = 0;
    virtual void Turn(int param) = 0;
    virtual void CheckWin(int param) = 0;
};