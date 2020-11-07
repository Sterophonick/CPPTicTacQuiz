#pragma once
class TicTacToe : public BaseClass
{
public:
    void Run(int param) override;

private:
    void Render(int param) override;
    void Turn(int param) override;
    void CheckWin(int param) override;

    void CPUTurn(int param);

    unsigned char m_xpos;
    unsigned char m_ypos;

    const char* letters[3] = { "- ", "X ", "O " };
    uint8_t winnings[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    uint8_t table[3 * 3];
    uint16_t m_index, m_index2;
    uint8_t m_win;
    uint8_t m_plays;

    uint8_t m_completed;

    uint8_t m_i;
};