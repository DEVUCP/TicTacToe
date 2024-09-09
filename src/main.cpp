#define _GLIBCXX_USE_CXX11_ABI 1

#include "game.cpp"

#include <cctype>
#include <random>
#include <chrono>

#include <thread>

using std::cout;
using std::string;
using std::cin;
using std::endl;

std::mt19937 createRNG() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    return std::mt19937(seed);
}


void mainGameLoop(Game game);

void playAgain(){

    while(true){
        
        string input;
        cin>>input;

        if(input.size() == 0) return;

        char choice = input[0];

        if(choice == 'Y' || choice == 'y') return;

        else exit(0);
    }
}

void won(){

    cout<<"You Won!!"<<endl
    <<"wanna play again? (y/n)"<<endl;

    playAgain();
    mainGameLoop(Game());
}


void lost(){

    cout<<"You Lost :("<<endl
    <<"wanna try again? (y/n)"<<endl;

    playAgain();
    mainGameLoop(Game());
}

char getSymbolChoice(){
    string input;
    while(true){
        cout << "Choose 'X' or 'O'"<<endl;
        cin>>input;

        if(input[0] == 'X' || input[0] == 'x') return 'X';

        else if(input[0] == 'O' || input[0] == 'o') return 'O';

        else cout<<"'"<<input[0]<<"' is not a valid option. choose either X or O\ntry again.."<<endl;    
    }
}

void doPlayerMove(Game &game){

    cout<<game.getBoardDisplay()<<endl;

    while(true){
        cout<<"\nYour move ? (x , y) -> "<<endl;

        int x, y;
        string coord;

        cin>>coord;

        if(coord.size()<3){cout<<game.getBoardDisplay()<<endl<<"Invalid coord (too small)"; continue;}

        if(std::isdigit(coord[0])){x = coord[0] - '0';}
            else{cout<<game.getBoardDisplay()<<endl<<"Invalid x coord"; continue;}

        if(std::isdigit(coord[2])){y = coord[2] - '0';}
            else{cout<<game.getBoardDisplay()<<endl<<"Invalid y coord"; continue;}
        
        if(!game.UpdateBoard(x,y, game.getPlayer())){cout<<game.getBoardDisplay()<<endl<<"Invalid coord"; continue;}
        
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
            cout<<game.getBoardDisplay()<<endl;
            won();

        }

        cout<<game.getBoardDisplay()<<endl

        <<"Waiting for Computer's move . . . "<<endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Stopping program for 2 seconds.

        doCompMove(game);

        if(game.checkWin(game.getComputer())){

            cout<<game.getBoardDisplay()<<endl;
            lost();
        }
    }
}

int main(){
    
    mainGameLoop();

    cout<<"Program Terminated"<<endl;
    return 0;
}