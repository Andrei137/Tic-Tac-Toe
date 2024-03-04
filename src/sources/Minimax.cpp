#include "Minimax.hpp"
#include <algorithm>
#include <climits>
#include <random>

Minimax* Minimax::m_instance{ nullptr };
const std::vector<int> Minimax::m_depths{ 9, 8, 6, 5, 4, 4, 3, 3 };

Minimax& Minimax::get_instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Minimax();
    }
    return *m_instance;
}

char Minimax::opponent_symbol(char a_symbol)
{
    return a_symbol == 'X' ? 'O' : 'X';
}

int Minimax::minimax(Board& a_board, int a_depth, int a_alpha, int a_beta, bool a_is_maximizing, char a_symbol)
{
    int size{ a_board.get_size() };
    if (a_board.get_winner() == a_symbol)
    {
        return 10;
    }
    else if (a_board.get_winner() == opponent_symbol(a_symbol))
    {
        return -10;
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
                    char symbol{ a_symbol };
                    a_board.set_cell(i, j, symbol);
                    if (a_board.win(symbol, i, j))
                    {
                        a_board.set_winner(symbol);
                    }
                    int score{ minimax(a_board, a_depth + 1, a_alpha, a_beta, false, a_symbol) };
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
                    char symbol{ opponent_symbol(a_symbol) };
                    a_board.set_cell(i, j, symbol);
                    if (a_board.win(symbol, i, j))
                    {
                        a_board.set_winner(symbol);
                    }
                    int score{ minimax(a_board, a_depth + 1, a_alpha, a_beta, true, a_symbol) };
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

std::vector<int> Minimax::get_possible_moves(const Board& a_board, char a_symbol)
{
    int size{ a_board.get_size() };
    std::vector<int> possible_moves{};
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a_board.valid_move(i, j))
            {
                if (a_board.win(a_symbol, i, j))
                {
                    return { i * size + j + 1 };
                }
                possible_moves.push_back(i * size + j + 1);
            }
        }
    }
    return possible_moves;
}

std::vector<int> Minimax::get_moves(Board& a_board, char a_symbol, const str& a_difficulty)
{
    std::vector<int> possible_moves{ get_possible_moves(a_board, a_symbol) };
    std::vector<int> moves{};
    int size{ a_board.get_size() };
    int best_score{ INT_MIN };
    int worst_score{ INT_MAX };
    int alpha{ INT_MIN };
    int beta{ INT_MAX };
    for (const int index : possible_moves)
    {
        int i{ (index - 1) / size };
        int j{ (index - 1) % size };
        a_board.set_cell(i, j, a_symbol);
        int score{ minimax(a_board, 0, alpha, beta, false, a_symbol) };
        a_board.clear_cell(i, j);
        if (a_difficulty == "easy")
        {
            if (score < worst_score)
            {
                worst_score = score;
                moves.clear();
                moves.push_back(index);
            }
            else if (score == worst_score)
            {
                moves.push_back(index);
            }
        }
        if (a_difficulty == "hard")
        {
            if (1 + rand() % 100 <= 75 && score < 0)
            {
                moves.push_back(index);
            }
            if (score == 0)
            {
                moves.push_back(index);
            }
        }
        if (a_difficulty == "impossible")
        {
            if (score > best_score)
            {
                best_score = score;
                moves.clear();
                moves.push_back(index);
            }
            else if (score == best_score)
            {
                moves.push_back(index);
            }
        }
    }
    return moves;
}

int Minimax::get_random_move(Board& a_board, char a_symbol, const str& a_difficulty)
{   
    std::vector<int> a_moves{ get_moves(a_board, a_symbol, a_difficulty) };
    if (a_moves == std::vector<int>{})
    {
        return -1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(a_moves.begin(), a_moves.end(), g);
    return a_moves[0];
}
