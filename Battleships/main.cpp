#include <iostream>

enum CellState{ EMPTY, OCCUPIED, DESTROYED, MISS };

class Coordinate{
public:
    int x, y;

public:
    Coordinate(char coordinate[2]){
        x =  toupper(coordinate[0]) - 65;
        y = coordinate[1] - 48;
    }
};

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
        /*Bonus
        //todo Check surrounding blocks for availability
        if((x > 0 && y > 0) && (x < 9 && y < 9)){
            for (int row = x-1; row < x+2; ++row) {
                for (int column = y-1; column < y+2; ++column) {
                    if(Board[row][column].State != EMPTY) return false;
                }
            }
        }*/
        return true;
    }
public:
    void ShowGrid(bool asEnemy = false) {
        std::cout <<"  |0|1|2|3|4|5|6|7|8|9";
        for (int i = 0; i < 10; ++i) {
            std::cout <<std::endl <<"  ---------------------" <<std::endl;
            char rowLetter = i+65;
            std::cout <<rowLetter <<" |";
            for (int j = 0; j < 10; ++j) {
                char output;
                switch (Board[i][j].State) {
                    case EMPTY:
                        output = '^';
                        break;
                    case OCCUPIED:
                        output = asEnemy ? '^' : 'U';
                        break;
                    case DESTROYED:
                        output = 'X';
                        break;
                    case MISS:
                        output = '@';
                }
                std::cout <<output <<"|";
            }
        }
        std::cout <<std::endl <<std::endl;
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

    bool Place(Coordinate coordinate){
        return Place(coordinate.x, coordinate.y);
    }

    bool Attack(int x, int y){
        if(grid.Board[x][y].State == OCCUPIED){
            grid.Board[x][y].State = DESTROYED;
            ShipsRemaining--;
            return true;
        }
        grid.Board[x][y].State = MISS;
        return false;
    }

    bool Attack(Coordinate coordinate){
        return Attack(coordinate.x, coordinate.y);
    }
};

void ClearScreen(){
    for (int i = 0; i < 20; ++i) {
        std::cout <<std::endl;
    }
}

void PlaceShips(Player &player) {
    std::cout <<"Player " <<player.Name <<"'s turn to place their ships." <<std::endl;
    while(player.ShipsToPlace > 0){
        std::cout <<"Place your ship! " <<player.ShipsToPlace <<" remaining." <<std::endl;
        char input[2];
        std::cin >> input;
        Coordinate placementLocation = *new Coordinate(input);
        if(!player.Place(placementLocation)) std::cout <<"Unable to place a ship there." <<std::endl;
    }
    player.grid.ShowGrid();
    ClearScreen();
}

void ShootAt(Player &target) {
    std::cout << "Enter coordinates to take your shot!" << std::endl;
    char input[2];
    std::cin >> input;
    Coordinate shotTarget = *new Coordinate(input);
    if(target.Attack(shotTarget))
        std::cout <<"HIT!" <<std::endl;
    else
        std::cout <<"MISS!" <<std::endl;
}

int main() {
    Player player1, player2;

    player1.Name = "1";
    player2.Name = "2";

    PlaceShips(player1);
    PlaceShips(player2);

    while(true){
        player2.grid.ShowGrid(true);
        std::cout <<"Player " <<player1.Name <<"'s Turn:" <<std::endl;
        ShootAt(player2);
        if(player2.ShipsRemaining <= 0) {
            player1.grid.ShowGrid(false);
            std::cout <<"Player " << player1.Name << "wins!" << std::endl;
            std::cout <<"Player " <<player1.Name <<"'s board at the end of the game." <<std::endl;
            break;
        }

        player1.grid.ShowGrid(true);
        std::cout <<"Player " <<player2.Name <<"'s Turn:" <<std::endl;
        ShootAt(player1);
        if(player1.ShipsRemaining <= 0) {
            player2.grid.ShowGrid(false);
            std::cout <<"Player " << player2.Name << "wins!" << std::endl;
            std::cout <<"Player " <<player2.Name <<"'s board at the end of the game." <<std::endl;
            break;
        }
    }
    std::cout <<"Game Over!" << std::endl;
    return 0;
}