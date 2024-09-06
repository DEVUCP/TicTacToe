#define _GLIBCXX_USE_CXX11_ABI 1

#include <iostream>
#include <array>
#include <typeinfo>
#include <algorithm>
#include <cctype>
#include <random>

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

std::string username;


enum menuChoices{
    LEADERBOARD, NEWGAME, QUIT, CONTINUE
};

enum gameEndStatus{
    WIN, LOSS, TIE, INTERRUPT
};

const std::string LOGIN_MESSAGE = "Welcome to Tic-Tac-Toe\nEnter username to login: ";
const std::string MENU_MESSAGE = "\t\t-- MAIN MENU --\n\tchoose an option by entering it's number..\n1) Leaderboard\n2 ) New game\n3 ) Quit\n";


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
            computer = 'U';
            status = INTERRUPT;}

        // for when loading \/
        Game(std::array<std::array<char, 3>, 3> new_board, char p_symbol, char c_symbol, int n_status) {
            board = new_board;
            player = p_symbol;
            computer = c_symbol;
            n_status = status;}

        // Getters
        std::array<std::array<char, 3>, 3> getBoard() {return board;}

        char getPlayer() {return player;}

        char getComputer() {return computer;}

        int getStatus() {return status;}

        std::string getBoardDisplay() {
            std::string display = "";
            for(int i = 0; i < 3; i++){

                if(i != 0 && i !=3) display += "\n__________________\n";

                for(int j = 0; j < 3; j++){

                    if(j == 1) display += "|";

                    display += "  ";
                    std::cout<<board[i][j]<<" from "<<i<<j<<std::endl;
                    display.append(1,board[i][j]);
                    display += "  ";
                    

                    if(j == 1) display += "|";
                }
            }
            return display;
        }
        // Setters
        void setBoard(const std::array<std::array<char, 3>, 3> newBoard) {board = newBoard;}

        void setPlayer(char newPlayer) {player = newPlayer;}

        void setComputer(char newComputer) {computer = newComputer;}

        void setStatus(int newStatus) {status = newStatus;}

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

void won(){
    std::cout<<"You Won!!"<<std::endl;
}
void lost(){
    std::cout<<"You Lost :("<<std::endl;
}

void displayLeaderBoard(){
    std::cout<<"here would be a leader board"<<std::endl;
}

int getMenuChoice() {
    std::string input;
    int choice;
    while (true) {
        std::cout << MENU_MESSAGE;
        std::cin >> input;

        if (input.length() == 1 && input[0] >= '1' && input[0] <= '3') {
            choice = input[0] - '0';
            return choice;
        } else {
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
        }
    }
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
        std::cout<<"\nYour move ? -> "<<std::endl;
        int x, y;
        std::string coord;
        std::cin>>coord;
        if(coord.size()<3){std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid coord (too small)"; continue;}

        if(std::isdigit(coord[0])){x = coord[0] - '0';}
            else{std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid x coord"; continue;}

        if(std::isdigit(coord[2])){y = coord[2] - '0';}
            else{std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid y coord"; continue;}
        
        if(!game.UpdateBoard(x,y, game.getPlayer())){std::cout<<game.getBoardDisplay()<<std::endl<<"Invalid coord"; continue;}
        
        std::cout<<game.getPlayer()<<std::endl;
        break;
    }
    
}

void doCompMove(Game &game){
    std::random_device rd;
    std::uniform_int_distribution<int> slots(0,3);
    int x = -1;
    int y = -1;
    int c = 0;
    while(!game.IsCoordAvalaible(x,y)){
        x = slots(rd);
        y = slots(rd);
        if(c>20){break;}
    }
    game.UpdateBoard(x,y, game.getComputer());
}


int mainGameLoop(std::string username = "", Game game = Game()){

    std::cout<<"main game loop reached"<<std::endl;
    game.setPlayerAdvanced(getSymbolChoice());

    // Display
    // Do player move
    for(int i = 0; i < 8; i++){
    doPlayerMove(game);
    if(game.checkWin(game.getPlayer())){std::cout<<game.getBoardDisplay()<<std::endl;won(); return WIN;}
    // Display
    std::cout<<game.getBoardDisplay()<<std::endl<<"Waiting for Computer's move . . . "<<std::endl;
    // do an artificial wait timer (3-5 seconds)
    platform_sleep(3);
    // Do comp move
    doCompMove(game);
    // CheckWin
    if(game.checkWin(game.getComputer())){std::cout<<game.getBoardDisplay()<<std::endl;lost(); return LOSS;}   
    }
    return 3;
}


void mainMenu(){
    std::cout<<LOGIN_MESSAGE<<std::endl; // Display login message

    std::cin>>username; // Take username from player
}


int main(){
    // Display menu
    mainMenu();
    int choice = getMenuChoice();

    switch(choice){

        case LEADERBOARD:{
            displayLeaderBoard();
        }   break;

        case NEWGAME:{
            mainGameLoop(username); // mainGameLoop( std::string username , Game previous_game );

        }   break;
};
    // TODO : Take symbol choice
    // TODO : Check for Username in save file dict
    // TODO : if found data -> Retrieve data 
    // TODO : ifnot -> create new entry with username and gamestatus as "INTERRUPTED"
    std::cout<<"This program compiles and runs"<<std::endl;

    // switch(status){
    //     case WIN:
    //         // won();
    //     case LOSS:
    //         // lost();
    //     case INTERRUPT:
    //         // interrupted();
    //         // save individual game-board and player playing symbol with player data
    // }

    // TODO : File saving after WON, LOSS, TIE OR on program termination

    return 0;
}