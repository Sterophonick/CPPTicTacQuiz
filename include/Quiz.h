#pragma once
class Quiz : public BaseClass
{
public:
    void Run(int param) override;

private:
    void Render(int param) override;
    void Turn(int param) override;
    void CheckWin(int param) override;

    u8 m_completed;
    const char* operations[4] = { "+", "-", "*", "/" };
    u8 m_num1, m_num2;
    u8 m_operation;
    u8 m_wins;
    u8 m_winans;
    u8 m_counter;
    u8 m_correct;
    double m_ans;
    const char* answers[4] = {"A. ", "B. ", "C. ", "D. "};
    
};