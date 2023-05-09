#include "../includes/Solver.h"
#include <algorithm>
#include <climits>
#include <random>
#include <rlutil.h>

const std::vector<int> Solver::m_depths{ 9, 8, 6, 5, 4, 4, 3, 3 };

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
    else if (a_board.draw() || a_depth == m_depths[size - 3])
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
                    if (score > best_score)
                    {
                        best_score = score;
                    }
                    if (score > a_alpha)
                    {
                        a_alpha = score;
                    }
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
                    if (score < best_score)
                    {
                        best_score = score;
                    }
                    if (score < a_beta)
                    {
                        a_beta = score;
                    }
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
        else if (score == best_score)
        {
            best_moves.push_back(i * size + j + 1);
        }
    }
    if (!best_moves.empty())
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(best_moves.begin(), best_moves.end(), g);
        return best_moves[0];
    }
    return -1;
}

std::pair<int, int> Solver::get_move(const Board& a_board) const
{
    loading(a_board);
    Board copy{ a_board };
    return convert(get_best_move(copy), a_board.get_size());
}