/// Antonii Zlatarov 121220083 9p 41gr PIK1 Kursova rabota zadanie 10

#include<stdio.h>
#include<windows.h>

/// game entities
#define PLAYER 0
#define COMPUTER 1

/// field properties
#define GAME_FIELD_COLS 10
#define GAME_FIELD_ROWS 10
#define SHIPS_AMOUNT 5

/// ship positioning orientations
#define LEFT_ORIENTATION 1
#define RIGHT_ORIENTATION 2
#define BOTTOM_ORIENTATION 3
#define TOP_ORIENTATION 4

/// field cell properties
#define EMPTY_CELL 0
#define SHIP_CELL 1
#define SHIP_HIT_CELL 2
#define EMPTY_HIT_CELL 3

int currentShipHits[2], hitsToWin = 12;
int shipSize[SHIPS_AMOUNT] = {4, 3, 2, 2, 1};
int gameField[GAME_FIELD_COLS][GAME_FIELD_ROWS][2];

void beginTurnFights();
void checkWinConditions();
void initGameField(int entity);
void printGameField(int entity);
void attackCell(int col, int row, int entityAttacker, int entityDefender);
void placeShipAt(int col, int row, int shipSize, int entity, int orientation);

int canAttackCell(int col, int row, int entityDefender);
int canPlaceShipAt(int col, int row, int shipSize, int entity, int defaultOrientation);

int main()
{

    srand(time(0));

    initGameField(PLAYER);
    initGameField(COMPUTER);

    system("cls");

    printGameField(PLAYER);
    printGameField(COMPUTER);

    beginTurnFights();
    checkWinConditions();

    return 0;
}

void initGameField(int entity)
{
    int row, col, shipsPlaced = 0, placementOrientation;

    if(entity == PLAYER)
    {
        printf("Welcome to BattleShips! Please read the rules of the game =>\n\n");
        Sleep(3000);
        printf("(1) - You and the computer have five battleships placed in two separate 10x10 fields\n\n");
        Sleep(5000);
        printf("(2) - The locations of the computer's ships are random meanwhile you can choose where you want yours to be\n\n");
        Sleep(5000);
        printf("(3) - To win you have to eliminate the computer's ships before yours are eliminated, both of you take a turn to attack\n\n");
        Sleep(5000);
        printf("(4) - Each turn you can see your own field and what you have hit on the computer's field\n\n");
        Sleep(5000);
        printf("Good luck and wait 10 seconds until you can place ur ships!\n\n");
        Sleep(10000);
        system("cls");
        printf("Enter the 2d coordinates (x, y) and orientation (LEFT - 1, RIGHT - 2, BOTTOM - 3, TOP - 4) of your ships :\n\n");
    }

    while(shipsPlaced < SHIPS_AMOUNT)
    {
        if(entity == COMPUTER)
        {
            col = rand() % GAME_FIELD_COLS;
            row = rand() % GAME_FIELD_ROWS;

            placementOrientation = rand()%4 + 1;

            if(canPlaceShipAt(col, row, shipSize[shipsPlaced], entity, placementOrientation))
            {
                placeShipAt(col, row, shipSize[shipsPlaced], entity, placementOrientation);
                shipsPlaced++;
            }
        }
        else
        {
            printGameField(PLAYER);

            printf("Ship %d with size %d :\n",
                   shipsPlaced + 1, shipSize[shipsPlaced]);

            printf("x of ship : ");
            scanf("%d", &col);
            printf("y of ship : ");
            scanf("%d", &row);
            printf("orientation of ship : ");
            scanf("%d", &placementOrientation);

            if(!placementOrientation)
            {
                printf("\n\nError! You entered a wrong orientation for your ship! Try again!");
            }
            else if(canPlaceShipAt(col, row, shipSize[shipsPlaced], entity, placementOrientation))
            {
                placeShipAt(col, row, shipSize[shipsPlaced], entity, placementOrientation);
                shipsPlaced++;
            }
            else
            {
                printf("\n\nError! Your ship either goes out of the bounds or intersects with another ship. Try again!");
            }
            printf("\n\n");
        }

    }

    if(entity == PLAYER)
    {
        printGameField(PLAYER);
        printf("All your ships have been placed! Waiting for the computer's ships placements!\n");
    }
    else
    {
        printf("All of the computer's ships have been placed! Game is about to start in 5 seconds!\n");
    }

    Sleep(5000);
}

int canPlaceShipAt(int col, int row, int shipSize, int entity, int defaultOrientation)
{
    int placementCol, placementRow;

    if(defaultOrientation == RIGHT_ORIENTATION && col + shipSize <= GAME_FIELD_COLS - 1)
    {
        for(placementCol = col; placementCol < col + shipSize; placementCol++)
        {
            if(gameField[placementCol][row][entity])
            {
                break;
            }
        }
        if(placementCol == col + shipSize)
        {
            return 1;
        }
    }

    if(defaultOrientation == LEFT_ORIENTATION && col - shipSize >= -1)
    {
        for(placementCol = col; placementCol > col - shipSize; placementCol--)
        {
            if(gameField[placementCol][row][entity])
            {
                break;
            }
        }
        if(placementCol == col - shipSize)
        {
            return 1;
        }
    }

    if(defaultOrientation == BOTTOM_ORIENTATION && row + shipSize <= GAME_FIELD_ROWS - 1)
    {
        for(placementRow = row; placementRow < row + shipSize; placementRow++)
        {
            if(gameField[col][placementRow][entity])
            {
                break;
            }
        }
        if(placementRow == row + shipSize)
        {
            return 1;
        }
    }

    if(defaultOrientation == TOP_ORIENTATION && row - shipSize >= -1)
    {
        for(placementRow = row; placementRow > row - shipSize; placementRow--)
        {
            if(gameField[col][placementRow][entity])
            {
                break;
            }
        }
        if(placementRow == row - shipSize)
        {
            return 1;
        }
    }

    return 0;
}

void placeShipAt(int col, int row, int shipSize, int entity, int orientation)
{
    int placementCol, placementRow;

    if(orientation == LEFT_ORIENTATION)
    {
        for(placementCol = col; placementCol > col - shipSize; placementCol--)
        {
            gameField[placementCol][row][entity] = SHIP_CELL;
        }
    }

    else if(orientation == RIGHT_ORIENTATION)
    {
        for(placementCol = col; placementCol < col + shipSize; placementCol++)
        {
            gameField[placementCol][row][entity] = SHIP_CELL;
        }
    }

    else if(orientation == BOTTOM_ORIENTATION)
    {
        for(placementRow = row; placementRow < row + shipSize; placementRow++)
        {
            gameField[col][placementRow][entity] = SHIP_CELL;
        }
    }

    else if(orientation == TOP_ORIENTATION)
    {
        for(placementRow = row; placementRow > row - shipSize; placementRow--)
        {
            gameField[col][placementRow][entity] = SHIP_CELL;
        }
    }
}

void printGameField(int entity)
{
    if(entity == PLAYER)
    {
        printf("\n---- YOUR FIELD : \n\n");
    }
    else
    {
        printf("\n---- THE COMPUTER'S FIELD : \n\n");
    }

    int row, col;
    for(row = 0; row < GAME_FIELD_ROWS; row++)
    {
        for(col = 0; col < GAME_FIELD_COLS; col++)
        {
            if(entity == PLAYER)
            {
                if(gameField[col][row][entity] == SHIP_CELL)
                {
                    printf("%c", 'S');
                }
            }
            else
            {
                if(gameField[col][row][entity] == SHIP_CELL)
                {
                    printf("%c", '.');
                }
            }

            if(gameField[col][row][entity] == EMPTY_CELL)
            {
                printf("%c", '.');
            }
            else if(gameField[col][row][entity] == SHIP_HIT_CELL)
            {
                printf("%c", 'x');
            }
            else if(gameField[col][row][entity] == EMPTY_HIT_CELL)
            {
                printf("%c", 'o');
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int canAttackCell(int col, int row, int entityDefender)
{
    if(row < 0 || row > GAME_FIELD_ROWS - 1 || col < 0 || col > GAME_FIELD_COLS - 1)
    {
        return 0;
    }

    if(gameField[col][row][entityDefender] == SHIP_HIT_CELL ||
            gameField[col][row][entityDefender] == EMPTY_HIT_CELL)
    {
        return 0;
    }

    return 1;
}

void attackCell(int col, int row, int entityAttacker, int entityDefender)
{
    if(gameField[col][row][entityDefender] == SHIP_CELL)
    {
        gameField[col][row][entityDefender] = SHIP_HIT_CELL;
        currentShipHits[entityAttacker]++;
    }
    else if (gameField[col][row][entityDefender] == EMPTY_CELL)
    {
        gameField[col][row][entityDefender] = EMPTY_HIT_CELL;
    }
}

void beginTurnFights()
{

    int currentTurn = 1, nextToAttack = rand()%2;

    while(currentShipHits[PLAYER] < hitsToWin || currentShipHits[COMPUTER] < hitsToWin)
    {
        system("cls");
        printGameField(PLAYER);
        printGameField(COMPUTER);

        if(nextToAttack == PLAYER)
        {
            printf("Turn %d - You are attacking...\n", currentTurn);

            int col, row;
            printf("target x : ");
            scanf("%d", &col);
            printf("target y : ");
            scanf("%d", &row);

            while(!canAttackCell(col, row, COMPUTER))
            {
                printf("\nError: That target cell is out of bounds or already hit, try again!\n\n");

                printf("target x : ");
                scanf("%d", &col);
                printf("target y : ");
                scanf("%d", &row);
            }
            attackCell(col, row, PLAYER, COMPUTER);

            if(gameField[col][row][COMPUTER] == SHIP_HIT_CELL)
            {
                printf("(!!!) You hit the computer's ship at (x, y) => {%d, %d}\n", col, row);
            }
            else if(gameField[col][row][COMPUTER] == EMPTY_HIT_CELL)
            {
                printf("(-) You missed at (x, y) => {%d, %d}\n", col, row);
            }
            printGameField(COMPUTER);

        }
        else
        {
            printf("Turn %d - The computer is attacking...\n", currentTurn);
            Sleep(5000);

            int col = rand() % GAME_FIELD_COLS;
            int row = rand() % GAME_FIELD_ROWS;

            while(!canAttackCell(col, row, PLAYER))
            {
                col = rand() % GAME_FIELD_COLS;
                row = rand() % GAME_FIELD_ROWS;
            }

            attackCell(col, row, COMPUTER, PLAYER);

            if(gameField[col][row][PLAYER] == SHIP_HIT_CELL)
            {
                printf("(!!!) The computer hit your ship at (x, y) => {%d, %d}\n", col, row);
            }
            else if(gameField[col][row][PLAYER] == EMPTY_HIT_CELL)
            {
                printf("(-) The computer missed at (x, y) => {%d, %d}\n", col, row);
            }
            printGameField(PLAYER);

        }
        Sleep(5000);
        nextToAttack = !nextToAttack;
        currentTurn++;
    }
}

void checkWinConditions()
{
    if(currentShipHits[PLAYER] == hitsToWin)
    {
        printf("\n\nYOU WIN!!!\n");
    }
    else if(currentShipHits[COMPUTER] == hitsToWin)
    {
        printf("\n\nThe computer won this time, restart and try again!");
    }
}
