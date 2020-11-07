#include <iostream>
#include <libheart.h>
#include <maxmod.h>
#include "soundbank_bin.h"
#include "soundbank.h"
#include "BaseClass.h"
#include "TicTacToe.h"
#include "Quiz.h"
u16 keys_pressed = 0;
u16 keys_released = 0;
u16 keys_pressedonce = 0;
u16 keys_repeat = 0;

void vblFunc()
{
    hrt_ScanKeys();
    keys_pressed = hrt_KeysHeld();
	keys_released = hrt_KeysUp();
    keys_pressedonce = hrt_KeysDown();
    keys_repeat = hrt_KeysDownRepeat();
    hrt_CreateRNG();
    if((keys_pressed & KEY_A)&&(keys_pressed & KEY_B)&&(keys_pressed & KEY_SELECT)&&(keys_pressed & KEY_START))
        hrt_SoftReset(0);
}

int main()
{
    //Set up Game Boy Advance
    hrt_Init();
    hrt_SeedRNG(0xDEADBEEF);
    hrt_SetInputRepeat(10, 10);
    hrt_InitTextEngine(0);
    hrt_DSPConfigMode(DSP_MODE(0) | ENABLE_BG(0));

    //Set up MaxMod
    mmSetVBlankHandler((void*)vblFunc);
    mmInitDefault((mm_addr)soundbank_bin, 16);
    mmStart(MOD_SURFACE, MM_PLAY_LOOP);
    
    //Ask which game
    hrt_Print(0,0, (char*)"Which game? (a/b)");
    BaseClass* pGame = nullptr;

    //Get Input
    do {
        hrt_VblankIntrWait();
        mmFrame();
        mmVBlank();
    } while(!((keys_pressed & KEY_A) || (keys_pressed & KEY_B)));
    if(keys_pressed & KEY_A)
    {
        pGame = new Quiz();
    }else{
        pGame = new TicTacToe();
    }   
    
    //Execute Game
    hrt_ClearText();
    pGame->Run(0);
    do {
        hrt_VblankIntrWait();
        mmFrame();
        mmVBlank();
    } while(1);
    return 0;
}