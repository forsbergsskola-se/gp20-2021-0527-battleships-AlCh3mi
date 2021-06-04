#include <iostream>

using namespace std;

enum BlockState { available, nought, cross };

void PrintGrid();
void ResetBoard();
void Place(BlockState, int);
bool IsAvailable(int);
bool CheckWin();
void PlayerTurn(BlockState);
void AiTurn(BlockState symbol);

BlockState Grid[3][3];
bool vsAI = false;

int main() {
    cout << "Tic Tac Toe" << endl;
    cout << "How many players? \n1 vs CPU \n2 HeadsUp" << endl;

    int input;
    cin >> input;
    if(input == 1)
        vsAI = true;

    ResetBoard();

    do{
        PlayerTurn(nought);
        if(CheckWin()) {
            cout << "Player " << nought <<" wins." << endl;
            break;
        }
        PrintGrid();

        if(vsAI)
            AiTurn(cross);
        else
            PlayerTurn(cross);

        if(CheckWin()) {
            cout << "Player " << cross <<" wins." << endl;
            break;
        }
        PrintGrid();

    }while(!CheckWin());
    PrintGrid();
    return 0;
}

void AiTurn(BlockState symbol) {
    int randomLocation;
    do{
        randomLocation = rand() % 9 + 1;
    }while(!IsAvailable(randomLocation));
    cout << "AI(Player " << symbol <<") placed at position :" << randomLocation << endl;
    Place(symbol, randomLocation);
}

void PlayerTurn(BlockState player) {
    int input;
    do {
        cout << "Where would Player " << player <<" like to place? index 1 - 9: ";
        cin >> input;
    } while (!(input > 0 && input < 10) || !IsAvailable(input));
    Place(player, input);
}

bool CheckWin(){
    for (int i = 0; i < 3; ++i) {
        if((Grid[i][0] != available) && (Grid[i][0] == Grid[i][1]) && (Grid[i][0] == Grid[i][2])) return true;
        if((Grid[0][i] != available) && (Grid[0][i] == Grid[1][i]) && (Grid[0][i] == Grid[2][i])) return true;
    }
    if((Grid[0][0] != available) && Grid[0][0] == Grid[1][1] && Grid[0][0] == Grid[2][2]) return true;
    if((Grid[0][2] != available) && Grid[0][2] == Grid[1][1] && Grid[0][2] == Grid[2][0]) return true;
    return false;
}

void Place(BlockState newState, int index){
    if(newState == available) return;
    if(IsAvailable(index))
        Grid[--index / 3][index % 3] = newState;
}

bool IsAvailable(int index){
    return (Grid[--index / 3][index % 3] == available);
}

void ResetBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Grid[i][j] = available;
        }
    }
}

void PrintGrid() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            switch (Grid[i][j]) {
                case nought: cout << "O"; break;
                case available: cout << " "; break;
                case cross: cout << "X"; break;
            }
            if(j != 2)
                cout << "|";
        }
        if(i != 2)
            cout << endl <<"-----" << endl;
    }
    cout << endl;
}