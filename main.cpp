#include <iostream>
#include <array>
#include <string>

//the game array set by user/s
std::array<std::array<int, 3>, 3> GAME_ARR = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};


/**
 * Check if the user given had win
 * @param userToCheck the user value to check
 * @return true if he win else false
 */
bool checkWin(int userToCheck) {
    if (GAME_ARR[1][1] == userToCheck) {
        if (((GAME_ARR[0][0] == userToCheck) && (GAME_ARR[2][2] == userToCheck)) ||
            ((GAME_ARR[1][0] == userToCheck) && (GAME_ARR[1][2] == userToCheck)) ||
            ((GAME_ARR[2][0] == userToCheck) && (GAME_ARR[0][2] == userToCheck)) ||
            ((GAME_ARR[0][1] == userToCheck) && (GAME_ARR[2][1] == userToCheck)))
            return true;
        else return false;
    } else if (GAME_ARR[0][0] == userToCheck) {
        if (((GAME_ARR[0][1] == userToCheck) && (GAME_ARR[0][2] == userToCheck)) ||
            ((GAME_ARR[1][0] == userToCheck) && (GAME_ARR[2][0] == userToCheck)))
            return true;
        else return false;
    } else if (GAME_ARR[2][2] == userToCheck) {
        if (((GAME_ARR[0][2] == userToCheck) && (GAME_ARR[1][2] == userToCheck)) ||
            ((GAME_ARR[2][0] == userToCheck) && (GAME_ARR[2][1] == userToCheck)))
            return true;
        else return false;
    } else return false;
}

/**
 * Check if the user given had win
 * :this method can navigate every size of array (searching for 3 case checked)
 * @param userToCheck the user value to check
 * @return true if he win else false
 */
bool checkWinR(int userToCheck) {
    //iterate on each case of the array
    for (int y = 0; y < GAME_ARR.size(); y++) {
        for (int x = 0; x < GAME_ARR[0].size(); x++) {
            //if the case is checked by the user we want to win
            if (GAME_ARR[y][x] == userToCheck) {
                //check bounderies for have no error
                bool allowYplus1 = y + 1 - (int) GAME_ARR.size() < 0;
                bool allowYplus2 = y + 2 - (int) GAME_ARR.size() < 0;
                bool allowXplus1 = x + 1 - (int) GAME_ARR[y].size() < 0;
                bool allowXplus2 = x + 2 - (int) GAME_ARR[y].size() < 0;
                bool allowXsub2 = x - 2 >= 0;
                bool allowXsub1 = x - 1 >= 0;

                bool finalBool = false;
                if (allowYplus1 && allowYplus2) {
                    //check if a column of 3 case is checked
                    finalBool = (finalBool || (GAME_ARR[y + 1][x] == userToCheck && GAME_ARR[y + 2][x] == userToCheck));
                    if (allowXplus1 && allowXplus2) {
                        //check if a diagonal of 3 case is checked
                        finalBool = (finalBool ||
                                     (GAME_ARR[y + 1][x + 1] == userToCheck && GAME_ARR[y + 2][x + 2] == userToCheck));
                    }
                    if (allowXsub1 && allowXsub2) {
                        //check if a diagonal of 3 case is checked
                        finalBool = (finalBool ||
                                     (GAME_ARR[y + 1][x - 1] == userToCheck && GAME_ARR[y + 2][x - 2] == userToCheck));
                    }
                }
                if (allowXplus1 && allowXplus2) {
                    //check if a line of 3 case is checked
                    finalBool = (finalBool || (GAME_ARR[y][x + 1] == userToCheck && GAME_ARR[y][x + 2] == userToCheck));
                }
                if (finalBool) {
                    //if 3 case checked return true for win
                    return true;
                }
            }
        }
    }

    //if no 3 case is found not win so return false
    return false;
}

/**
 * This method ask the user to check a case and then save it on the array
 * @param user the current user
 * @param isComputer if true the case is asked by the computer
 * @return false if an error occurred
 */
bool addACase(int user, bool isComputer) {
    std::cout << "User " << user << " give some coordinate (format:x,y):" << std::endl;

    std::string xString = "";
    std::string yString = "";
    if (isComputer) {
        //generate random coordinate
        xString = std::to_string(rand() % GAME_ARR.size());
        yString = std::to_string(rand() % GAME_ARR[0].size());
    } else {
        //ask user the coordinate of the case to check
        std::string caseToAdd;
        getline(std::cin, caseToAdd);

        //get single coordinate x or y
        xString = caseToAdd.substr(0, caseToAdd.find(','));
        yString = caseToAdd.substr(caseToAdd.find(',') + 1);
    }

    //cast coordinate to int and get the asked case in the array
    int &askedCase = GAME_ARR[std::stoi(xString, nullptr, 10)][std::stoi(yString, nullptr, 10)];
    //check if the case hasn't been checked else return false
    if (askedCase == 0) {
        askedCase = user;
        return true;
    }
    std::cout << "An error occurred, please retry" << std::endl;
    return false;
}

/**
 * This method display as user-friendly as possible the array of the game
 */
void displayArray() {
    //iterate on each case of the array
    for (int y = 0; y < GAME_ARR.size(); y++) {
        for (int x = 0; x < GAME_ARR[0].size(); x++) {
            switch (GAME_ARR[y][x]) {
                case 2:
                    std::cout << " X ";
                    break;
                case 1:
                    std::cout << " O ";
                    break;
                case 0:
                default:
                    std::cout << " - ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 * This method create a new game and describe all the process of a game until someone win
 * @param isVsComputer if true user 2 is the computer
 */
void newGame(bool isVsComputer) {
    bool currentUser = false; //The current user is 1 if false else 2
    while (!(checkWinR(1) || checkWinR(2))) {
        bool isPassed = false;
        while (!isPassed) {
            isPassed = addACase(currentUser ? 2 : 1, isVsComputer && currentUser);
        }
        displayArray();
        currentUser = !currentUser;
    }

    if (checkWinR(1)) {
        if (isVsComputer) {
            std::cout << "Congratulation, you won !" << std::endl;
        } else {
            std::cout << "Congratulation, User 1 won !" << std::endl;
        }
    } else {
        if (isVsComputer) {
            std::cout << "Congratulation, you lost !" << std::endl;
        } else {
            std::cout << "Congratulation, User 2 won !" << std::endl;
        }
    }
}


int main() {
    std::cout << "Hello, do you want to play against computer (y to proceed) ?" << std::endl;
    std::string input = "";
    std::getline(std::cin, input);
    newGame(input.compare("y") == 0);

    return 0;
}