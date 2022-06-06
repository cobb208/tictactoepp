//
// Created by Cory Cobb on 6/5/22.
//

#ifndef TICTACTOEPP_GAME_H
#define TICTACTOEPP_GAME_H

#include <iostream>
#include <memory>
#include <utility>

struct Player {
    char player_symbol{};
    std::string play_name{};

    Player(char player_symbol, std::string play_name)
    {
        this->player_symbol = player_symbol;
        this->play_name = std::move(play_name);
    }
};

struct Game_struct {
    int board_size{};
    bool winner{};
    std::unique_ptr<Player> players[2];
    int current_player{};
    std::string empty_location;
    std::string board;
};


class Game {
    const int BOARD_SIZE = 10;
    std::string const EMPTY_LOCATION{"-"};
    std::shared_ptr<Game_struct> game;

    std::shared_ptr<Game_struct> CreateGame();
    void Print_board();
    bool Check_input_range(int choice);
    bool Get_player_input(int& choice);
    void Toggle_current_player();
    void Place_player_choice(int const& choice);
    bool Check_row(char a, char b, char c, char player_symbol);
    bool Check_results(char player_symbol);
    bool Check_for_winner();
    bool Check_for_tie();
    bool Play_again();


public:
    Game();
    void Game_loop();
};


#endif //TICTACTOEPP_GAME_H
