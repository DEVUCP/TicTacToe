#include <array>
#include <iostream>

const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";

class Game {
    static char constexpr symbols[2] = {'X', 'O'};
    private:
        char player; // player assigned symbol
        char computer; // computer assigned symbol
        int status; // from enum GameEndStatus

    public:
        std::array<std::array<char, 3>, 3> board;
        // for new game \/
        Game() {
            board = {{
                {' ',' ',' '},
                {' ',' ',' '},
                {' ',' ',' '}
            }};
            player = 'U';
            computer = 'U';}

        // for when loading \/
        Game(std::array<std::array<char, 3>, 3> new_board, char p_symbol, char c_symbol) {
            board = new_board;
            player = p_symbol;
            computer = c_symbol;}

        // Getters
        std::array<std::array<char, 3>, 3> getBoard() {return board;}

        char getPlayer() {return player;}

        char getComputer() {return computer;}

        std::string getBoardDisplay() {
            std::string display = "";
            for(int i = 0; i < 3; i++){

                if(i != 0 && i !=3) display += "\n__________________\n";

                for(int j = 0; j < 3; j++){

                    std::string color;

                    if(board[i][j] == player) color = BLUE;
                    if(board[i][j] == computer) color = RED;

                    if(j == 1) display += "|";

                    display += "  " + color; // Adds spacing and color
                    display.append(1,board[i][j]);
                    display += "  " + RESET; // Adds spacing and removes color
                    

                    if(j == 1) display += "|";
                }
            }
            return display;
        }
        // Setters
        void setBoard(const std::array<std::array<char, 3>, 3> newBoard) {board = newBoard;}

        void setPlayer(char newPlayer) {player = newPlayer;}

        void setComputer(char newComputer) {computer = newComputer;}

        // Rest of the methods
        
        bool checkWin(char symbol) {
            // Check rows
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
                    return true;
                }
            }
            
            // Check columns
            for (int j = 0; j < 3; ++j) {
                if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
                    return true;
                }
            }
            
            // Check diagonals
            if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
                return true;
            }
            if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
                return true;
            }
            
            return false;
        }

        bool IsValidCoord(int row, int col){ return (row <= 2 && row >= 0 ) && (col <= 2 && col >= 0); }

        bool IsCoordAvalaible(int row, int col){

            if(!IsValidCoord(row, col)) return false; // Validates first
            if(board[row][col] == ' ') return true;
            else return false;
        }
        
        int UpdateBoard(int row, int col, char move){
            // validation
            if(!IsValidCoord(row, col)) return 0;
            if(IsCoordAvalaible(row, col));
            else return 0;
            board[row][col] = move;
            return 1;

        }

        void setPlayerAdvanced(char newPlayer) {
            player = newPlayer;
            switch(player)
            {
                case symbols[0]:{
                    computer = symbols[1];
                }break;

                case symbols[1]:{
                    computer = symbols[0];
                }break;
            }
        }
};