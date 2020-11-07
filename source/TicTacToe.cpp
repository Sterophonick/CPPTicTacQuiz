#include <string.h>
#include <libheart.h>
#include <maxmod.h>
#include <iostream>
#include "BaseClass.h"
#include "TicTacToe.h"

constexpr int X = 1;
constexpr int O = 2;
#define tableElement(x, y) table[y*3+x]

void TicTacToe::Run(int param)
{
    m_win = 0;
    do {
        Turn(0);
        CheckWin(0);
        CPUTurn(0);
        CheckWin(0);
        Render(0);
    } while(1);
}

void TicTacToe::Render(int param)
{
    hrt_ClearText();
    for (m_index = 0; m_index < 3; m_index++) //x
    {
        for (m_index2 = 0; m_index2 < 3; m_index2++) //y
        {
            switch(tableElement(m_index2, m_index))
            {
                case 0:
                    hrt_Print(m_index2, m_index, (char*)"-");
                    break;
                case 1:
                    hrt_Print(m_index2, m_index, (char*)"X");
                    break;
                case 2:
                    hrt_Print(m_index2, m_index, (char*)"O");
                    break;
            }
        }
    }
    do{
        hrt_VblankIntrWait();
        mmFrame();
        mmVBlank();
    }while(!(keys_pressed & KEY_A));
    do{
        hrt_VblankIntrWait();
        mmFrame();
        mmVBlank();
    }while(keys_pressed & KEY_A);
}


void TicTacToe::Turn(int param)
{
    m_completed = 0;
    m_xpos = 0;
    m_ypos = 0;
    hrt_ClearText();
    while(!(m_completed))
    {
        hrt_Print(0,0, (char*)"Tic-Tac-Toe Advance");
        hrt_Print(0,1, (char*)"Where is your X Position (0-2)");
        do{
            if(keys_repeat & KEY_LEFT)
            {
                if(m_xpos != 0) m_xpos--;
            }
            if(keys_repeat & KEY_RIGHT)
            {
                if(m_xpos < 2) m_xpos++;
            }
            hrt_Print(0,2, (char*)"%d", m_xpos);
            hrt_VblankIntrWait();
            mmFrame();
            mmVBlank();
        }while(!(keys_pressed & KEY_A));
        hrt_Print(0,4, (char*)"OK");
        m_i = 60;
        while(m_i--) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
        hrt_ClearText();
        hrt_Print(0,0, (char*)"Tic-Tac-Toe Advance");
        hrt_Print(0,1, (char*)"Where is your Y Position (0-2)");
        do{
            if(keys_repeat & KEY_LEFT)
            {
                if(m_ypos != 0) m_ypos--;
            }
            if(keys_repeat & KEY_RIGHT)
            {
                if(m_ypos < 2) m_ypos++;
            }
            hrt_Print(0,2, (char*)"%d", m_ypos);
            hrt_VblankIntrWait();
            mmFrame();
            mmVBlank();
        }while(!(keys_pressed & KEY_A));
        hrt_Print(0,4, (char*)"OK");
        m_i = 60;
        while(m_i--) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
        if (tableElement(m_xpos, m_ypos))
        {
            hrt_ClearText();
            hrt_Print(0,0, (char*)"Spot already used!");
        }
        else {
            tableElement(m_xpos, m_ypos) = X;
            m_completed = 1;
            hrt_ClearText();
            hrt_Print(0,0, (char*)"Waiting...");
        }
        m_i = 60;
        while(m_i--) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
    }
}

void TicTacToe::CPUTurn(int param)
{
    m_completed = 0;
    u8 m_attempts = 0;
    while(!(m_completed))
    {
        m_xpos = hrt_CreateRNG() % 3;
        m_ypos = hrt_CreateRNG() % 3;
        if (!(tableElement(m_xpos, m_ypos)))
        {
            tableElement(m_xpos, m_ypos) = O;
            m_completed = 1;
        }
        m_attempts++;
        if(m_attempts == 9)
        {
            m_completed = 1;
        }
    }
}

void TicTacToe::CheckWin(int param)
{
        uint8_t t;
        hrt_ClearText();
        for (t = 0; t < 7; t++)
        {
            if ((table[(winnings[t][0])] == 1)&&(table[(winnings[t][1])] == 1)&&(table[(winnings[t][2])] == 1))
            {
                m_win = 1;
            }else if ((table[(winnings[t][0])] == 2)&&(table[(winnings[t][1])] == 2)&&(table[(winnings[t][2])] == 2))
            {
                m_win = 2;
            }else{
                m_win = 0;
            }
        }
        switch(m_win)
        {
            case 1:
                hrt_Print(0,0, (char*)"You win!");
                do{
                    hrt_VblankIntrWait();
                    mmFrame();
                    mmVBlank();
                }while(1);
                break;
            case 2:
                hrt_Print(0,0, (char*)"CPU wins!");
                do{
                    hrt_VblankIntrWait();
                    mmFrame();
                    mmVBlank();
                }while(1);
                break; 
        }
}