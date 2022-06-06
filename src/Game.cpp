//
// Created by Cory Cobb on 6/5/22.
//

#include "Game.h"
#include <string>
#include <assert.h>

std::string Game::EMPTY_LOCATION = "-";

Game::Game() {
    this->game = CreateGame();
}

std::shared_ptr<Game_struct> Game::CreateGame() {
    std::string b;


    for(int i = 0; i < 9; i++)
    {
        b.append(Game::EMPTY_LOCATION);
    }

    std::shared_ptr<Game_struct> g = std::make_shared<Game_struct>();

    assert(g != nullptr);

    g->board_size = BOARD_SIZE;
    g->winner = false;
    g->current_player = 0;
    g->empty_location = EMPTY_LOCATION;
    g->board = b;
    g->players[0] = std::make_unique<Player>('X', "Player 1");
    g->players[1] = std::make_unique<Player>('O', "Player 2");


    return g;
}

void Game::Print_board() {
    int game_board_index = 0;
    for(int i = 0; i < 3; i++)
    {
        char row[6];
        row[5] = '\0';

        int column_index = 0;
        int board_sym_toggle = 1;

        int j = 0;
        while(j < 3)
        {
            if(board_sym_toggle == 1)
            {
                row[column_index] = this->game->board[game_board_index];
                j++;
                column_index++;
                game_board_index++;
                board_sym_toggle = 0;
            } else {
                row[column_index] = '|';
                column_index++;
                board_sym_toggle = 1;
            }
        }
        std::cout << row << std::endl;
    }
}

bool Game::Check_input_range(int choice) {
    if(choice > 0 and choice <=9)
    {
        return true;
    }

    return false;
}

bool Game::Get_player_input(int& choice) {
    std::string user_input;
    int number_input;
    bool is_correct = false;

    while(!is_correct)
    {
        std::cout << this->game->players[this->game->current_player]->play_name << " enter your choice: " << std::endl;
        std::cin >> user_input;

        try {
            number_input = std::stoi(user_input);
        } catch (std::exception &e) {
            std::cout << "You did not enter a number try again!" << std::endl;
            continue;
        }
        is_correct = Check_input_range(number_input);
        if(!is_correct)
        {
            std::cout << "You did not enter a correct number try again!" << std::endl;
        }
    }

    choice = number_input;
    return true;
}

void Game::Toggle_current_player() {
    if(this->game->current_player == 1)
    {
        this->game->current_player = 0;
        return;
    }

    this->game->current_player = 1;
}

void Game::Place_player_choice(int choice) {
    if(this->game->board[choice - 1] == this->game->empty_location[0])
    {
        this->game->board[choice - 1] = this->game->players[this->game->current_player]->player_symbol;
        Toggle_current_player();
    } else {
        std::cout << "Location is taken try again!" << std::endl;
    }
}

bool Game::Check_row(char a, char b, char c, char player_symbol) {
    if(a == player_symbol and b == player_symbol and c == player_symbol)
    {
        return true;
    }

    return false;
}

bool Game::Check_results(char player_symbol) {
    char top_left = this->game->board[0];
    char top_mid = this->game->board[1];
    char top_right = this->game->board[2];
    char mid_left = this->game->board[3];
    char mid_mid = this->game->board[4];
    char mid_right = this->game->board[5];
    char bot_left = this->game->board[6];
    char bot_mid = this->game->board[7];
    char bot_right = this->game->board[8];

    int results[] = {
            Check_row(top_left, top_mid, top_right, player_symbol),
            Check_row(mid_left, mid_mid, mid_right, player_symbol),
            Check_row(bot_left, bot_mid, bot_right, player_symbol),
            Check_row(top_left, mid_left, bot_left, player_symbol),
            Check_row(top_mid, mid_mid, bot_mid, player_symbol),
            Check_row(top_right, mid_right, bot_right, player_symbol),
            Check_row(top_left, mid_mid, bot_right, player_symbol),
            Check_row(bot_left, mid_mid, top_right, player_symbol)
    };

    int results_size = sizeof(results) / sizeof(int);

    for(int i = 0; i < results_size; i++)
    {
        if(results[i])
        {
            return true;
        }
    }

    return false;
}

bool Game::Check_for_winner() {
    if(Check_results(this->game->players[0]->player_symbol))
    {
        std::cout << this->game->players[0]->play_name << " wins!" << std::endl;
        return true;
    } else if(Check_results(this->game->players[1]->player_symbol))
    {
        std::cout << this->game->players[1]->play_name << " wins!" << std::endl;
        return true;
    }

    return false;
}

bool Game::Check_for_tie() {
    for(int i = 0; i < this->game->board_size; i++)
    {
        if(this->game->board[i] == this->game->empty_location[0])
        {
            return false;
        }
    }

    std::cout << "Cats game!" << std::endl;
    return true;
}

bool Game::Play_again() {
    std::string play_again;
    std::cout << "Play again? " << std::endl;
    std::cin >> play_again;
    if(play_again == "y" or play_again == "Y")
    {
        return true;
    }
    return false;
}

void Game::Game_loop() {
    Print_board();
    bool game_complete = false;
    while(!game_complete)
    {
        int choice;
        Get_player_input(choice);
        Place_player_choice(choice);
        Print_board();
        if(Check_for_winner() or Check_for_tie()) {
            game_complete = true;
        }
    }
    if(Play_again())
    {
        this->game = CreateGame();
        Game_loop();
    }
}