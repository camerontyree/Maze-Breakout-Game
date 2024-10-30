/*
#include "personalLibrary.h"

const int WIDTH = 32;
const int HEIGHT = 22;
const int FOV = 40;
const int NUM_ROOMS = 5;

class Character {
protected:
    int posX;
    int posY;

public:
    Character(int x = 1, int y = 1) : posX(x), posY(y) {}
    virtual ~Character() {}

    int getX() const { return posX; }
    int getY() const { return posY; }

    virtual void move(int direction, bool blockades[][WIDTH]) = 0;
};
class Player : public Character {
public:
    Player(int x = 1, int y = 1) : Character(x, y) {}

    void move(int direction, bool blockades[][WIDTH]) override {
        switch (direction) {
        case 0:
            if (posY > 0 && !blockades[posY - 1][posX])
                posY--;
            break;
        case 1:
            if (posY < HEIGHT - 1 && !blockades[posY + 1][posX])
                posY++;
            break;
        case 2:
            if (posX > 0 && !blockades[posY][posX - 1])
                posX--;
            break;
        case 3:
            if (posX < WIDTH - 1 && !blockades[posY][posX + 1])
                posX++;
            break;
        }
    }
};
class Guard : public Character {
public:
    Guard(int x = 1, int y = 1) : Character(x, y) {}

    using Character::getX;
    using Character::getY;

    void move(int direction, bool blockades[][WIDTH]) override {
        switch (direction) {
        case 0:
            if (posY > 0 && !blockades[posY - 1][posX])
                posY--;
            break;
        case 1:
            if (posY < HEIGHT - 1 && !blockades[posY + 1][posX])
                posY++;
            break;
        case 2:
            if (posX > 0 && !blockades[posY][posX - 1])
                posX--;
            break;
        case 3:
            if (posX < WIDTH - 1 && !blockades[posY][posX + 1])
                posX++;
            break;
        }
    }
};
class Clue {
private:
    int posX;
    int posY;
    std::string riddle;

public:
    Clue(int x = 1, int y = 1, const std::string& r = "") : posX(x), posY(y), riddle(r) {}

    int getX() const { return posX; }
    int getY() const { return posY; }
    std::string getRiddle() const { return riddle; }
};
class SecretDoor
{
private:
    int posX;
    int posY;
public:
    SecretDoor(int x = 1, int y = 1, const std::string& r = "") : posX(x), posY(y) {}
    int getX() const { return posX; }
    int getY() const { return posY; }
};
int random(int min, int max) {
    return min + rand() % (max - min + 1);
} 
double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void clearScreen() {
    system("cls");
}
void moveGuards(Guard guards[], bool blockades[][WIDTH]) {
    for (int i = 0; i < 3; ++i) {
        int direction = random(0, 3);
        guards[i].move(direction, blockades);
    }
}
void saveGame(const std::string& filename, int posX, int posY, const Clue& clue, bool foundClue) {
    std::ofstream file(filename); 
    if (file.is_open()) {

        file << posX << " " << posY << "\n";
        file << clue.getX() << " " << clue.getY() << " " << foundClue << "\n";
        
        file.close();
        std::cout << "Game saved successfully.\n";
    }
    else {
        std::cerr << "Unable to open file for saving.\n";
    }
}
void loadGame(const std::string& filename, int& posX, int& posY, Clue& clue, bool& foundClue) {
    std::ifstream file(filename); 
    if (file.is_open()) {
        
        file >> posX >> posY;
        int clueX, clueY;
        file >> clueX >> clueY >> foundClue;
        clue = Clue(clueX, clueY, "");
       
        file.close();
        std::cout << "Game loaded successfully.\n";
    }
    else {
        std::cerr << "Unable to open file for loading. Starting a new game.\n";
    }
}

int main() {
    srand(time(0));
   
    int roomChoice = 0;
    bool gameRunning = true;
    Clue clue;
    SecretDoor secretDoor;
    bool foundClue = false;

    while (gameRunning) {
       
        int posX = 1;
        int posY = 1;
        int doorX = 30;
        int doorY = 20;
        int secretDoorX = 7;
        int secretDoorY = 20;
        bool atDoor = false;

        cout << "\nWelcome to my stealth game!\n\n";
        cout << "=======================================================================================================\n\n";
        cout << "--- Description ---\n";
        cout << "MAIN GOAL = FIND THE SECRET BEHIND THE FINAL ROOM\n";
        cout << "HOW? = Find clues throughout the game\n"; 
        cout << "5 Clues\nClues = Riddles \nRiddles = Numbers \nNumbers = Final Code \nFinal code = Secret\n";
        cout << "\n---CONTROLS ---\n";
        cout << "'w' = Move Up, 'a' = Move Left, 's' = Move Down, 'd' = Move Right\n";
        cout << "'q' = Quit The Game\n";
        cout << "'l' = Leave the room once you get to the door\n";
        cout << "'G' = Guards, stay away from them at all cost. If you get caught by one, you will be caught and lose\n";
        cout << "'C' = Clue, find these to help you win the game\n";
        cout << "'D' = Door, go to this when you wish to leave the room\n\n";
        cout << "=======================================================================================================\n\n";
        cout << "Stealth Game Menu:\n";
        cout << "1) Enter Room 1\n";
        cout << "2) Enter Room 2\n";
        cout << "3) Enter Room 3\n";
        cout << "4) Enter Room 4\n";
        cout << "5) Enter Room 5\n";
        cout << "6) Enter Final Room\n";
        cout << "7) Exit\n";
        cout << "8) Save game\n";
        cout << "9) Load game\n";
        roomChoice = validateNumMinAndMax("Enter your choice: ", 1 , 9);

        if (roomChoice == 1) {
            bool blockades[HEIGHT][WIDTH] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1},
            {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1},
            {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1},
            {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };


            Guard guards[3];

            do {
                guards[0] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[0].getY()][guards[0].getX()]);

            do {
                guards[1] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[1].getY()][guards[1].getX()] || (guards[1].getX() == guards[0].getX() && guards[1].getY() == guards[0].getY()));

            do {
                guards[2] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[2].getY()][guards[2].getX()] ||
                (guards[2].getX() == guards[0].getX() && guards[2].getY() == guards[0].getY()) ||
                (guards[2].getX() == guards[1].getX() && guards[2].getY() == guards[1].getY()));

            do {
                int clueX = random(1, WIDTH - 2);
                int clueY = random(1, HEIGHT - 2);
                clue = Clue(clueX, clueY, "If two's company\nand three's a crowd,\nwhat are four and five?\n");
            } while (blockades[clue.getY()][clue.getX()]);
            bool caught = false;
            bool foundClue = false;

            Player player(posX, posY);

            while (!caught && !atDoor) {
                if (player.getX() == clue.getX() && player.getY() == clue.getY() && !foundClue) {
                    clearScreen();
                    cout << "=== Clue ===\n";
                    cout << clue.getRiddle() << "\n\n";
                    cout << "Think about the answer, then press any key to continue...\n";
                    foundClue = true;
                    _getch();
                }

                bool leavingRoom = false;
                if (player.getX() == doorX && player.getY() == doorY) {
                    cout << "You are at the exit. Press 'L' to leave.\n";
                    while (!leavingRoom) {
                        char exitChoice = _getch();
                        if (exitChoice == 'l' || exitChoice == 'L') {
                            cout << "You left the room.\n";
                            atDoor = true;
                            leavingRoom = true;
                        }
                    }
                }

                clearScreen();
                for (int y = 0; y < HEIGHT; ++y) {
                    for (int x = 0; x < WIDTH; ++x) {
                        if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                            cout << "# ";
                        }
                        else if (abs(x - player.getX()) <= FOV && abs(y - player.getY()) <= FOV) {
                            if (x == player.getX() && y == player.getY()) {
                                cout << "P ";
                            }
                            else if (x == doorX && y == doorY) {
                                cout << "D ";
                            }
                            else if (x == clue.getX() && y == clue.getY() && !foundClue) {
                                cout << "C ";
                            }
                            else {
                                bool isGuard = false;
                                for (int i = 0; i < 3; ++i) {
                                    if (x == guards[i].getX() && y == guards[i].getY()) {
                                        cout << "G ";
                                        isGuard = true;
                                        break;
                                    }
                                }
                                if (!isGuard && blockades[y][x]) {
                                    cout << "# ";
                                }
                                else if (!isGuard) {
                                    cout << ". ";
                                }
                            }
                        }
                        else {
                            cout << "  ";
                        }
                    }
                    cout << endl;
                }


                char movement = _getch();

                switch (movement) {
                case 'w':
                    player.move(0, blockades);
                    break;
                case 's':
                    player.move(1, blockades);
                    break;
                case 'a':
                    player.move(2, blockades);
                    break;
                case 'd':
                    player.move(3, blockades);
                    break;
                case 'q':
                    cout << "Thanks for playing!\n\n\n";
                    return 0;
                case 'm':
                    if (player.getX() == doorX && player.getY() == doorY) {
                        cout << "You left the room.\n";
                        atDoor = true;
                    }
                    break;
                }

                moveGuards(guards, blockades);

                for (int i = 0; i < 3; ++i) {
                    if (distance(player.getX(), player.getY(), guards[i].getX(), guards[i].getY()) <= 1) {
                        caught = true;
                        break;
                    }
                }

                if (caught) {
                    clearScreen();
                    cout << "You have been caught by a guard! Game Over.\n\n\n";
                    Sleep(2000);
                    return 0;
                }
                saveGame("save.txt", posX, posY, clue, foundClue);
            }
            
        }
        if (roomChoice == 2) {
            bool blockades[HEIGHT][WIDTH] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };


            Guard guards[3];

            do {
                guards[0] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[0].getY()][guards[0].getX()]);

            do {
                guards[1] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[1].getY()][guards[1].getX()] || (guards[1].getX() == guards[0].getX() && guards[1].getY() == guards[0].getY()));

            do {
                guards[2] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[2].getY()][guards[2].getX()] ||
                (guards[2].getX() == guards[0].getX() && guards[2].getY() == guards[0].getY()) ||
                (guards[2].getX() == guards[1].getX() && guards[2].getY() == guards[1].getY()));

            do {
                int clueX = random(1, WIDTH - 2);
                int clueY = random(1, HEIGHT - 2);
                clue = Clue(clueX, clueY, "As straigh as a spear I stand,\nTo reach for the sky with both my hands.\nMy shape reveals how many 'I am'\n");
            } while (blockades[clue.getY()][clue.getX()]);
            

            bool caught = false;
            bool foundClue = false;

            Player player(posX, posY);

            while (!caught && !atDoor) {
                if (player.getX() == clue.getX() && player.getY() == clue.getY() && !foundClue) {
                    clearScreen();
                    cout << "=== Clue ===\n";
                    cout << clue.getRiddle() << "\n\n";
                    cout << "Think about the answer, then press any key to continue...\n";
                    foundClue = true;
                    _getch();
                }

                bool leavingRoom = false;
                if (player.getX() == doorX && player.getY() == doorY) {
                    cout << "You are at the exit. Press 'L' to leave.\n";
                    while (!leavingRoom) {
                        char exitChoice = _getch();
                        if (exitChoice == 'l' || exitChoice == 'L') {
                            cout << "You left the room.\n";
                            atDoor = true;
                            leavingRoom = true;
                        }
                    }
                }

                clearScreen();
                for (int y = 0; y < HEIGHT; ++y) {
                    for (int x = 0; x < WIDTH; ++x) {
                        if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                            cout << "# ";
                        }
                        else if (abs(x - player.getX()) <= FOV && abs(y - player.getY()) <= FOV) {
                            if (x == player.getX() && y == player.getY()) {
                                cout << "P ";
                            }
                            else if (x == doorX && y == doorY) {
                                cout << "D ";
                            }
                            else if (x == clue.getX() && y == clue.getY() && !foundClue) {
                                cout << "C ";
                            }
                            else {
                                bool isGuard = false;
                                for (int i = 0; i < 3; ++i) {
                                    if (x == guards[i].getX() && y == guards[i].getY()) {
                                        cout << "G ";
                                        isGuard = true;
                                        break;
                                    }
                                }
                                if (!isGuard && blockades[y][x]) {
                                    cout << "# ";
                                }
                                else if (!isGuard) {
                                    cout << ". ";
                                }
                            }
                        }
                        else {
                            cout << "  ";
                        }
                    }
                    cout << endl;
                }


                char movement = _getch();

                switch (movement) {
                case 'w':
                    player.move(0, blockades);
                    break;
                case 's':
                    player.move(1, blockades);
                    break;
                case 'a':
                    player.move(2, blockades);
                    break;
                case 'd':
                    player.move(3, blockades);
                    break;
                case 'q':
                    cout << "Thanks for playing!\n\n\n";
                    return 0;
                case 'm':
                    if (player.getX() == doorX && player.getY() == doorY) {
                        cout << "You left the room.\n";
                        atDoor = true;
                    }
                    break;
                }

                moveGuards(guards, blockades);

                for (int i = 0; i < 3; ++i) {
                    if (distance(player.getX(), player.getY(), guards[i].getX(), guards[i].getY()) <= 1) {
                        caught = true;
                        break;
                    }
                }

                if (caught) {
                    clearScreen();
                    cout << "You have been caught by a guard! Game Over.\n\n\n";
                    Sleep(2000);
                    return 0;
                }
                saveGame("save.txt", posX, posY, clue, foundClue);
            }
            
        }
        if (roomChoice == 3) {
            bool blockades[HEIGHT][WIDTH] = {
             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
             {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
             {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
             {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
             {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
             {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
             {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1},
             {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
             {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
             {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
             {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
             {1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
             {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
             {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
             {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1},
             {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
             {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
             {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
             {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
             {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
             {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };

            Guard guards[3];

            do {
                guards[0] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[0].getY()][guards[0].getX()]);

            do {
                guards[1] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[1].getY()][guards[1].getX()] || (guards[1].getX() == guards[0].getX() && guards[1].getY() == guards[0].getY()));

            do {
                guards[2] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[2].getY()][guards[2].getX()] ||
                (guards[2].getX() == guards[0].getX() && guards[2].getY() == guards[0].getY()) ||
                (guards[2].getX() == guards[1].getX() && guards[2].getY() == guards[1].getY()));

            do {
                int clueX = random(1, WIDTH - 2);
                int clueY = random(1, HEIGHT - 2);
                clue = Clue(clueX, clueY, "From the North, from the West\nFrom the South, from the east\nWhen we push a door and find it shut\nWe slip in underneath\nWe whistle and blow\nOur number you know\nBut who are we?\n");
            } while (blockades[clue.getY()][clue.getX()]);
           

            bool caught = false;
            bool foundClue = false;  

            Player player(posX, posY);

            while (!caught && !atDoor) {
                if (player.getX() == clue.getX() && player.getY() == clue.getY() && !foundClue) {
                    clearScreen();
                    cout << "=== Clue ===\n";
                    cout << clue.getRiddle() << "\n\n";
                    cout << "Think about the answer, then press any key to continue...\n";
                    foundClue = true;
                    _getch();
                }

                bool leavingRoom = false;
                if (player.getX() == doorX && player.getY() == doorY) {
                    cout << "You are at the exit. Press 'L' to leave.\n";
                    while (!leavingRoom) {
                        char exitChoice = _getch();
                        if (exitChoice == 'l' || exitChoice == 'L') {
                            cout << "You left the room.\n";
                            atDoor = true;
                            leavingRoom = true;
                        }
                    }
                }

                clearScreen();
                for (int y = 0; y < HEIGHT; ++y) {
                    for (int x = 0; x < WIDTH; ++x) {
                        if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                            cout << "# ";
                        }
                        else if (abs(x - player.getX()) <= FOV && abs(y - player.getY()) <= FOV) {
                            if (x == player.getX() && y == player.getY()) {
                                cout << "P ";
                            }
                            else if (x == doorX && y == doorY) {
                                cout << "D ";
                            }
                            else if (x == clue.getX() && y == clue.getY() && !foundClue) {
                                cout << "C ";
                            }
                            else {
                                bool isGuard = false;
                                for (int i = 0; i < 3; ++i) {
                                    if (x == guards[i].getX() && y == guards[i].getY()) {
                                        cout << "G ";
                                        isGuard = true;
                                        break;
                                    }
                                }
                                if (!isGuard && blockades[y][x]) {
                                    cout << "# ";
                                }
                                else if (!isGuard) {
                                    cout << ". ";
                                }
                            }
                        }
                        else {
                            cout << "  ";
                        }
                    }
                    cout << endl;
                }


                char movement = _getch();

                switch (movement) {
                case 'w':
                    player.move(0, blockades);
                    break;
                case 's':
                    player.move(1, blockades);
                    break;
                case 'a':
                    player.move(2, blockades);
                    break;
                case 'd':
                    player.move(3, blockades);
                    break;
                case 'q':
                    cout << "Thanks for playing!\n\n\n";
                    return 0;
                case 'm':
                    if (player.getX() == doorX && player.getY() == doorY) {
                        cout << "You left the room.\n";
                        atDoor = true;
                    }
                    break;
                }

                moveGuards(guards, blockades);

                for (int i = 0; i < 3; ++i) {
                    if (distance(player.getX(), player.getY(), guards[i].getX(), guards[i].getY()) <= 1) {
                        caught = true;
                        break;
                    }
                }

                if (caught) {
                    clearScreen();
                    cout << "You have been caught by a guard! Game Over.\n\n\n";
                    Sleep(2000);
                    return 0;
                }
                saveGame("save.txt", posX, posY, clue, foundClue);
            }
            
        }
        if (roomChoice == 4) {
            bool blockades[HEIGHT][WIDTH] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
            {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };


            Guard guards[3];

            do {
                guards[0] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[0].getY()][guards[0].getX()]);

            do {
                guards[1] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[1].getY()][guards[1].getX()] || (guards[1].getX() == guards[0].getX() && guards[1].getY() == guards[0].getY()));

            do {
                guards[2] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[2].getY()][guards[2].getX()] ||
                (guards[2].getX() == guards[0].getX() && guards[2].getY() == guards[0].getY()) ||
                (guards[2].getX() == guards[1].getX() && guards[2].getY() == guards[1].getY()));


            do {
                int clueX = random(1, WIDTH - 2);
                int clueY = random(1, HEIGHT - 2);
                clue = Clue(clueX, clueY, "In all the world\nNothing compares\nTo this weaver's cloth\nTiny,\nDeadly,\nSilky,\nand fair.\n");
            } while (blockades[clue.getY()][clue.getX()]);

            bool caught = false;
            bool foundClue = false;

            Player player(posX, posY);

            while (!caught && !atDoor) {
                if (player.getX() == clue.getX() && player.getY() == clue.getY() && !foundClue) {
                    clearScreen();
                    cout << "=== Clue ===\n";
                    cout << clue.getRiddle() << "\n\n";
                    cout << "Think about the answer, then press any key to continue...\n";
                    foundClue = true;
                    _getch();
                }

                bool leavingRoom = false;
                if (player.getX() == doorX && player.getY() == doorY) {
                    cout << "You are at the exit. Press 'L' to leave.\n";
                    while (!leavingRoom) {
                        char exitChoice = _getch();
                        if (exitChoice == 'l' || exitChoice == 'L') {
                            cout << "You left the room.\n";
                            atDoor = true;
                            leavingRoom = true;
                        }
                    }
                }

                clearScreen();
                for (int y = 0; y < HEIGHT; ++y) {
                    for (int x = 0; x < WIDTH; ++x) {
                        if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                            cout << "# ";
                        }
                        else if (abs(x - player.getX()) <= FOV && abs(y - player.getY()) <= FOV) {
                            if (x == player.getX() && y == player.getY()) {
                                cout << "P ";
                            }
                            else if (x == doorX && y == doorY) {
                                cout << "D ";
                            }
                            else if (x == clue.getX() && y == clue.getY() && !foundClue) {
                                cout << "C ";
                            }
                            else {
                                bool isGuard = false;
                                for (int i = 0; i < 3; ++i) {
                                    if (x == guards[i].getX() && y == guards[i].getY()) {
                                        cout << "G ";
                                        isGuard = true;
                                        break;
                                    }
                                }
                                if (!isGuard && blockades[y][x]) {
                                    cout << "# ";
                                }
                                else if (!isGuard) {
                                    cout << ". ";
                                }
                            }
                        }
                        else {
                            cout << "  ";
                        }
                    }
                    cout << endl;
                }


                char movement = _getch();

                switch (movement) {
                case 'w':
                    player.move(0, blockades);
                    break;
                case 's':
                    player.move(1, blockades);
                    break;
                case 'a':
                    player.move(2, blockades);
                    break;
                case 'd':
                    player.move(3, blockades);
                    break;
                case 'q':
                    cout << "Thanks for playing!\n\n\n";
                    return 0;
                case 'm':
                    if (player.getX() == doorX && player.getY() == doorY) {
                        cout << "You left the room.\n";
                        atDoor = true;
                    }
                    break;
                }

                moveGuards(guards, blockades);

                for (int i = 0; i < 3; ++i) {
                    if (distance(player.getX(), player.getY(), guards[i].getX(), guards[i].getY()) <= 1) {
                        caught = true;
                        break;
                    }
                }

                if (caught) {
                    clearScreen();
                    cout << "You have been caught by a guard! Game Over.\n\n\n";
                    Sleep(2000);
                    return 0;
                }
                saveGame("save.txt", posX, posY, clue, foundClue);
            }
            
        }
        if (roomChoice == 5) {
            bool blockades[HEIGHT][WIDTH] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            };


            Guard guards[3];

            do {
                guards[0] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[0].getY()][guards[0].getX()]);

            do {
                guards[1] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[1].getY()][guards[1].getX()] || (guards[1].getX() == guards[0].getX() && guards[1].getY() == guards[0].getY()));

            do {
                guards[2] = Guard(random(1, WIDTH - 2), random(1, HEIGHT - 2));
            } while (blockades[guards[2].getY()][guards[2].getX()] ||
                (guards[2].getX() == guards[0].getX() && guards[2].getY() == guards[0].getY()) ||
                (guards[2].getX() == guards[1].getX() && guards[2].getY() == guards[1].getY()));

            do {
                int clueX = random(1, WIDTH - 2);
                int clueY = random(1, HEIGHT - 2);
                clue = Clue(clueX, clueY, "For me and you, we each have two\nIt's not our feet or hands to eat.\nOur legs are strong, but that too is wrong.\nOur arms are bold, but this we can not hold.\nWith these you see with so much glee...\nWhat am I?\n");
            } while (blockades[clue.getY()][clue.getX()]);

            bool caught = false;
            bool foundClue = false;

            Player player(posX, posY);

            while (!caught && !atDoor) {
                if (player.getX() == clue.getX() && player.getY() == clue.getY() && !foundClue) {
                    clearScreen();
                    cout << "=== Clue ===\n";
                    cout << clue.getRiddle() << "\n\n";
                    cout << "Think about the answer, then press any key to continue...\n";
                    foundClue = true;
                    _getch();
                }
                
                    if (player.getX() == secretDoorX && player.getY() == secretDoorY) {
                        clearScreen();
                        cout << "You found the secret room!\nIf you see this message, walk up to me and say 'Lebron James is the GOAT'\n";
                        cout << "\n\nPress any key to return to the map";
                        _getch();
                    }

                    bool leavingRoom = false;
                    if (player.getX() == doorX && player.getY() == doorY) {
                        cout << "You are at the exit. Press 'L' to leave.\n";
                        while (!leavingRoom) {
                            char exitChoice = _getch();
                            if (exitChoice == 'l' || exitChoice == 'L') {
                                cout << "You left the room.\n";
                                atDoor = true;
                                leavingRoom = true;
                            }
                        }
                    }

                    clearScreen();
                    for (int y = 0; y < HEIGHT; ++y) {
                        for (int x = 0; x < WIDTH; ++x) {
                            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                                cout << "# ";
                            }
                            else if (abs(x - player.getX()) <= FOV && abs(y - player.getY()) <= FOV) {
                                if (x == player.getX() && y == player.getY()) {
                                    cout << "P ";
                                }
                                else if (x == doorX && y == doorY) {
                                    cout << "D ";
                                }

                                else if (x == clue.getX() && y == clue.getY() && !foundClue) {
                                    cout << "C ";
                                }
                                else {
                                    bool isGuard = false;
                                    for (int i = 0; i < 3; ++i) {
                                        if (x == guards[i].getX() && y == guards[i].getY()) {
                                            cout << "G ";
                                            isGuard = true;
                                            break;
                                        }
                                    }
                                    if (!isGuard && blockades[y][x]) {
                                        cout << "# ";
                                    }
                                    else if (!isGuard) {
                                        cout << ". ";
                                    }
                                }
                            }
                            else {
                                cout << "  ";
                            }
                        }
                        cout << endl;
                    }


                    char movement = _getch();

                    switch (movement) {
                    case 'w':
                        player.move(0, blockades);
                        break;
                    case 's':
                        player.move(1, blockades);
                        break;
                    case 'a':
                        player.move(2, blockades);
                        break;
                    case 'd':
                        player.move(3, blockades);
                        break;
                    case 'q':
                        cout << "Thanks for playing!\n\n\n";
                        return 0;
                    case 'm':
                        if (player.getX() == doorX && player.getY() == doorY) {
                            cout << "You left the room.\n";
                            atDoor = true;
                        }
                        break;
                    }

                    moveGuards(guards, blockades);

                    for (int i = 0; i < 3; ++i) {
                        if (distance(player.getX(), player.getY(), guards[i].getX(), guards[i].getY()) <= 1) {
                            caught = true;
                            break;
                        }
                    }

                    if (caught) {
                        clearScreen();
                        cout << "You have been caught by a guard! Game Over.\n\n\n";
                        Sleep(2000);
                        return 0;
                    }
                
                saveGame("save.txt", posX, posY, clue, foundClue);
            }
        }
        if (roomChoice == 6) {

            const string secretCode = "91482";
            cout << "Enter the 5-digit code to unveil the secret: ";
            string userInput;
            cin >> userInput;
            if (userInput == secretCode) {

                ifstream secretFile("SECRET.txt");

                if (secretFile.is_open()) {

                    string secret;
                    while (getline(secretFile, secret)) {}
                    secretFile.close();
                    cout << "CONGRATS YOU WON!" << endl;
                    cout << "THE SECRET IS: " << secret << endl;
                    cout << "Thanks for playing! Press enter to exit\n\n\n\n";
                    return 0;
                }
                    
                else {
                    cout << "Unable to open secret file." << endl;
                }
            }
            else {
                cout << "Incorrect code. Access denied!" << endl;
            }
            saveGame("save.txt", posX, posY, clue, foundClue);
        }
        if (roomChoice == 7) {
            gameRunning = false;
            endProgram();
        }
        if (roomChoice == 8) {
            saveGame("save.txt", posX, posY, clue, foundClue);
        }
        if (roomChoice == 9) {
            loadGame("save.txt", posX, posY, clue, foundClue);
        }
    }

    return 0;
}






                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
l                {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}












*/