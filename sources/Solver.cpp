#include "../includes/Solver.h"
#include <climits>
#include <rlutil.h>

Solver::Solver(char a_symbol) : AI(a_symbol) {}

Solver& Solver::operator=(const Solver& a_other)
{
    if (this != &a_other)
    {
        AI::operator=(a_other);
    }
    return *this;
}

char Solver::opponent_symbol() const
{
    return m_symbol == 'X' ? 'O' : 'X';
}

int Solver::minimax(Board& a_board, int a_depth, int a_alpha, int a_beta, bool a_is_maximizing) const
{
    int size{ a_board.get_size() };
    if (a_board.get_winner() == m_symbol)
    {
        return 10 - a_depth;
    }
    else if (a_board.get_winner() == opponent_symbol())
    {
        return a_depth - 10;
    }
    else if (a_board.draw() || a_depth == 10)
    {
        return 0;
    }
    if (a_is_maximizing)
    {
        int best_score{ INT_MIN };
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (a_board.valid_move(i, j))
                {
                    char symbol{ m_symbol };
                    a_board.set_cell(i, j, symbol);
                    if (a_board.win(symbol, i, j))
                    {
                        a_board.set_winner(symbol);
                    }
                    int score{ minimax(a_board, a_depth + 1, a_alpha, a_beta, false) };
                    best_score = std::max(best_score, score);
                    a_alpha = std::max(a_alpha, score);
                    a_board.set_winner('-');
                    a_board.clear_cell(i, j);
                    if (a_beta <= a_alpha)
                    {
                        break;
                    }
                }
            }
        }
        return best_score;
    }
    else
    {
        int best_score{ INT_MAX };
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (a_board.valid_move(i, j))
                {
                    char symbol{ opponent_symbol() };
                    a_board.set_cell(i, j, symbol);
                    if (a_board.win(symbol, i, j))
                    {
                        a_board.set_winner(symbol);
                    }
                    int score{ minimax(a_board, a_depth + 1, a_alpha, a_beta, true) };
                    best_score = std::min(best_score, score);
                    a_beta = std::min(a_beta, score);
                    a_board.set_winner('-');
                    a_board.clear_cell(i, j);
                    if (a_beta <= a_alpha)
                    {
                        break;
                    }
                }
            }
        }
        return best_score;
    }
}

int Solver::get_best_move(Board& a_board) const
{
    int size{ a_board.get_size() };
    std::vector<std::pair<int, int>> possible_moves{};
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a_board.valid_move(i, j))
            {
                if (a_board.win(m_symbol, i, j))
                {
                    return i * size + j + 1;
                }
                possible_moves.push_back({i, j});
            }
        }
    }
    std::vector<int> best_moves{};
    int best_score{ INT_MIN };
    int alpha{ INT_MIN };
    int beta{ INT_MAX };
    for (const std::pair<int, int>& index : possible_moves)
    {
        int i{ index.first }, j{ index.second };
        a_board.set_cell(i, j, m_symbol);
        int score{ minimax(a_board, 0, alpha, beta, false) };
        a_board.clear_cell(i, j);
        if (score > best_score)
        {
            best_score = score;
            best_moves.clear();
            best_moves.push_back(i * size + j + 1);
        }
    }
    if (!best_moves.empty())
    {
        srand(time(0));
        return best_moves[rand() % static_cast<int>(best_moves.size())];
    }
    return -1;
}

std::pair<int, int> Solver::get_move(const Board& a_board) const
{
    std::cout << "\nComputer is thinking";
    for (int i = 0; i < 3; ++i)
    {
        rlutil::msleep(100);
        std::cout << '.';
        rlutil::msleep(400);
    }
    Board copy{ a_board };
    return convert(get_best_move(copy), a_board.get_size());
}