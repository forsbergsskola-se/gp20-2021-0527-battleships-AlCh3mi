#include <iostream>

enum CellState{ EMPTY, OCCUPIED, DESTROYED };

class Cell{
public:
    CellState State = EMPTY;

public:
    Cell(CellState state = EMPTY){
        State = state;
    }
};

class Grid{
public:
    Cell Board[10][10];
private:
    bool CanPlaceShip(int x, int y){
        if(Board[x][y].State != EMPTY)
            return false;
        //todo Check surrounding blocks for availability
        return true;
    }
public:
    void ResetGrid(){
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Board[i][j] = EMPTY;
            }
        }
    }

    void ShowGrid() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::cout <<Board[i][j].State <<" ";
            }
            std::cout <<std::endl;
        }
    }

    bool PlaceShip(int x, int y){
        if(!CanPlaceShip(x, y))
            return false;

        Board[x][y] = OCCUPIED;
        return true;
    }
};

class Player{
public:
    Grid grid;
    std::string Name;
    int ShipsToPlace = 5;
    int ShipsRemaining = 0;

public:
    bool Place(int x, int y){
        if(grid.PlaceShip(x, y)){
            ShipsToPlace--;
            ShipsRemaining++;
            return true;
        }
        return false;
    }

    bool Attack(int x, int y){
        if(grid.Board[x][y].State == OCCUPIED){
            grid.Board[x][y].State = DESTROYED;
            ShipsRemaining--;
            return true;
        }
        return false;
    }
};

void PlaceShips(Player &player) {
    std::cout <<"Player " <<player.Name <<"'s turn to place their ships." <<std::endl;
    while(player.ShipsToPlace > 0){
        std::cout <<"Place your ship! " <<player.ShipsToPlace <<"remaining." <<std::endl;
        int x, y; std::cout <<"x: "; std::cin >> x; std::cout <<"y: "; std::cin >> y;
        if(!player.Place(x, y)) std::cout <<"Unable to place a ship there." <<std::endl;
    }
    player.grid.ShowGrid();
}

int main() {

    Player player1, player2;
    player1.Name = "1";
    player2.Name = "2";

    bool GameOver = false;

    PlaceShips(player1);
    PlaceShips(player2);

    while(true){
        //Player 1 attacks till player 2 has no shipsRemaining
        player1.grid.ShowGrid();
        std::cout <<"Player1, enter coordinates to take your shot!" <<std::endl;
        int x, y; std::cout <<"x: "; std::cin >> x; std::cout <<"y: "; std::cin >> y;
        if(player2.Attack(x, y)){
            std::cout <<"HIT!" <<std::endl;
            if(player2.ShipsRemaining <= 0) break;
        }
        else
            std::cout <<"MISS!" <<std::endl;

        //Player 2 attacks till player 1 has no shipsRemaining
        std::cout <<"Player2, enter coordinates to take your shot!" <<std::endl;
        std::cout <<"x: "; std::cin >> x; std::cout <<"y: "; std::cin >> y;
        if(player1.Attack(x, y)){
            std::cout <<"HIT!" <<std::endl;
            if(player1.ShipsRemaining <= 0) break;
        }
        else{
            std::cout <<"MISS!" <<std::endl;
        }
    }

    std::cout <<"Game Over!" << std::endl;
    return 0;
}




