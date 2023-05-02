#define EMPTY_PLOT -1
#define TEAM_A 0
#define TEAM_B 1

struct Plot{
    int currentOwner;
    bool PROTECTED;
};
class Board{
public:
    Board();
    Board(int rows, int columns);
    void printBoard();
    int fireMissle(int row, int column, int TEAM);
    bool placePlayer(int row, int column, int TEAM);
    bool isOccupied(int row, int column);
    bool getTeam(int row, int column); // returns the ID of current occupied team
    int getRow();
    int getCol();
    bool isFull();
    int Winner();
    void test();
private:
    void updateSurrounding(int row, int column, int TEAM);
    void updatePlot(int row, int column, int TEAM);
    int hasMaj(int row, int column);
    Plot** board;
    int rows;
    int columns;
};