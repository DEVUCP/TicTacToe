#define _GLIBCXX_USE_CXX11_ABI 1

#include <iostream>
#include <array>

#include <cctype>
#include <random>
#include <chrono>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

void platform_sleep(unsigned int seconds) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(seconds * 1000); // Convert seconds to milliseconds
#else
    sleep(seconds);
#endif
}

const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";


std::mt19937 createRNG() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    return std::mt19937(seed);
}

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

void mainGameLoop(Game game);

void playAgain(){
    while(true){
        std::string input;
        std::cin>>input;

        if(input.size() == 0) return;

        char choice = input[0];

        if(choice == 'Y' || choice == 'y') return;

        else exit(0);
    }
}

void won(){
    std::cout<<"You Won!!"<<std::endl
    <<"wanna play again? (y/n)"<<std::endl;

    playAgain();
    mainGameLoop(Game());
}


void lost(){
    std::cout<<"You Lost :("<<std::endl
    <<"wanna try again? (y/n)"<<std::endl;

    playAgain();
    mainGameLoop(Game());
}

char getSymbolChoice(){
    std::string input;
    while(true){
        std::cout << "Choose 'X' or 'O'"<<std::endl;
        std::cin>>input;

        if(input[0] == 'X' || input[0] == 'x') return 'X';
        else if(input[0] == 'O' || input[0] == 'o') return 'O';
        else std::cout<<"'"<<input[0]<<"' is not a valid option. choose either X or O\ntry again.."<<std::endl;    
    }
}

void doPlayerMove(Game &game){
    std::cout<<game.getBoardDisplay()<<std::endl;
    while(true){
        std::cout<<"\nYour move ? (x , y) -> "<<std::endl;
        int x, y;
        std::string coord;
        std::cin>>coord;
        if(coord.size()<3){std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid coord (too small)"; continue;}

        if(std::isdigit(coord[0])){x = coord[0] - '0';}
            else{std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid x coord"; continue;}

        if(std::isdigit(coord[2])){y = coord[2] - '0';}
            else{std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid y coord"; continue;}
        
        if(!game.UpdateBoard(x,y, game.getPlayer())){std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid coord"; continue;}
        
        break;
    }
    
}

void doCompMove(Game &game) {
    std::random_device rd;
    auto gen = createRNG();
    std::uniform_int_distribution<int> slots(0, 3);

    int x = -1;
    int y = -1;
    while (!game.IsCoordAvalaible(x, y)) {
        x = slots(gen);
        y = slots(gen);
    }
    game.UpdateBoard(x, y, game.getComputer());
}


void mainGameLoop(Game game = Game()){

    game.setPlayerAdvanced(getSymbolChoice());


    for(int i = 0; i < 8; i++){
        doPlayerMove(game);
        if(game.checkWin(game.getPlayer())){
            std::cout<<game.getBoardDisplay()<<std::endl;
            won();
        }

        std::cout<<game.getBoardDisplay()<<std::endl

        <<"Waiting for Computer's move . . . "<<std::endl;

        platform_sleep(3);
        doCompMove(game);

        if(game.checkWin(game.getComputer())){
            std::cout<<game.getBoardDisplay()<<std::endl;
            lost();
        }
    }
}

int main(){

    mainGameLoop();

    std::cout<<"Program Terminated"<<std::endl;
    return 0;
}