#include <iostream>
#include <libheart.h>
#include <maxmod.h>
#include "BaseClass.h"
#include "Quiz.h"

//Essentially this creates a simple math problem and the players have to answer the questions
//What's 5 + 3?
//Player 1 answers and then Player 2 answers

void Quiz::Run(int param)
{
    for(u8 i = 0; i < 5; i++)
    {
        hrt_ClearText();
        m_completed = 0;
        hrt_Print(0, 0, (char*)"What is");
        Render(0);
        m_counter = i;
        Turn(0)
        ;
    }
    if(param == m_winans)
        m_correct++;
    hrt_ClearText();
    hrt_Print(0, 0, (char*)"The end!");
    hrt_Print(0, 1, (char*)"Score: %d/5", m_correct);
    while(1) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
}

void Quiz::Render(int param)
{
    m_num1 = hrt_RNGRange(1, 12);
    m_num2 = hrt_RNGRange(1, 12);

    m_operation = hrt_RNGRange(1, 4);

    if((m_num2 > m_num1) && ((m_operation == 2) || (m_operation == 4)))
    {
        m_operation = 1;
    }

    switch(m_operation)
    {
        case 1:
            m_ans = m_num1 + m_num2;
            break;
        case 2:
            m_ans = m_num1 - m_num2;
            break;
        case 3:
            m_ans = m_num1 * m_num2;
            break;
        case 4:
            m_ans = hrt_Div(m_num1, m_num2);
    }

    hrt_Print(0, 1, (char*)"%d %s %d?", m_num1, operations[m_operation-1], m_num2);

    for(u8 i = 0; i < 4; i++)
    {
        hrt_Print(1, i+3, (char*)answers[i]);
    }

    m_winans = hrt_RNGRange(0, 3);

    for(u8 i = 0; i < 4; i++)
    {
        if(i != m_winans)
            hrt_Print(4, i+3, (char*)"%2.2f", m_ans - (hrt_CreateRNG() % 10));
        else
            hrt_Print(4, i+3, (char*)"%2.2f", m_ans);
    }
    for(u8 i = 0; i < 60; i++) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
}

void Quiz::Turn(int param)
{
    u8 pos = 0;
    while(!m_completed)
    {
        hrt_VblankIntrWait();
        mmFrame();
        mmVBlank();
        hrt_Print(0, 3, (char*)">");
        do{
            if(keys_repeat & KEY_UP)
            {
                hrt_Print(0, pos + 3, (char*)" ");
                if(pos != 0) pos--;
                hrt_Print(0, pos + 3, (char*)">");
            }
            if(keys_repeat & KEY_DOWN)
            {
                hrt_Print(0, pos + 3, (char*)" ");
                if(pos < 3) pos++;
                hrt_Print(0, pos + 3, (char*)">");
            }
            hrt_VblankIntrWait();
            mmFrame();
            mmVBlank();
        }while(!(keys_pressed & KEY_A));
        if(keys_pressed & KEY_A)
        {
            m_completed = 1;
            hrt_ClearText();
            hrt_Print(0,0, (char*)"Waiting...");
            u8 i = 60;
            while(i--) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
        }
    }
    CheckWin(pos);
}

void Quiz::CheckWin(int param)
{

    hrt_ClearText();
    if(param == m_winans)
    {
        hrt_Print(0,0, (char*)"Correct!");
        m_correct++;
    }else{
        hrt_Print(0,0, (char*)"Incorrect!");
    }

    for(u8 i = 0; i < 60; i++) { hrt_VblankIntrWait(); mmFrame(); mmVBlank(); }
}