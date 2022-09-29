/**
 * @name TP_TicTacToe
 *
 * @author Guillaume Gonin
 * @date 29.09.2022
 */

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
    for (int x = 0; x < GAME_ARR.size(); x++) {
        for (int y = 0; y < GAME_ARR[0].size(); y++) {
            //if the case is checked by the user we want to win
            if (GAME_ARR[x][y] == userToCheck) {
                //check bounderies for have no error
                bool allowXplus1 = x + 1 - (int) GAME_ARR.size() < 0;
                bool allowXplus2 = x + 2 - (int) GAME_ARR.size() < 0;
                bool allowYplus1 = y + 1 - (int) GAME_ARR[x].size() < 0;
                bool allowYplus2 = y + 2 - (int) GAME_ARR[x].size() < 0;
                bool allowYsub2 = y - 2 >= 0;
                bool allowYsub1 = y - 1 >= 0;

                bool finalBool = false;
                if (allowXplus1 && allowXplus2) {
                    //check if a column of 3 case is checked
                    finalBool = (finalBool ||
                                 (GAME_ARR[x + 1][y] == userToCheck && GAME_ARR[x + 2][y] == userToCheck));
                    if (allowYplus1 && allowYplus2) {
                        //check if a diagonal of 3 case is checked
                        finalBool = (finalBool ||
                                     (GAME_ARR[x + 1][y + 1] == userToCheck && GAME_ARR[x + 2][y + 2] == userToCheck));
                    }
                    if (allowYsub1 && allowYsub2) {
                        //check if a diagonal of 3 case is checked
                        finalBool = (finalBool ||
                                     (GAME_ARR[x + 1][y - 1] == userToCheck && GAME_ARR[x + 2][y - 2] == userToCheck));
                    }
                }
                if (allowYplus1 && allowYplus2) {
                    //check if a line of 3 case is checked
                    finalBool = (finalBool ||
                                 (GAME_ARR[x][y + 1] == userToCheck && GAME_ARR[x][y + 2] == userToCheck));
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
 * Find the two mid case nearest of the given corner
 *
 * @param corner the corner to get mid 1 and mid 2
 * @return a array containing mid 1 and mid 2 coordinates ([x1, y1, x2, y2])
 */
std::array<int, 4> optimalAlgo_findMid1Mid2(std::array<int, 2> corner) {
    std::array<int, 4> res;
    if (corner[0] == 0) {
        if (corner[1] == 0) {
            res[0] = 0;
            res[1] = 1;
            res[2] = 1;
            res[3] = 0;
        } else {
            res[0] = 0;
            res[1] = corner[1] - 1;
            res[2] = 1;
            res[3] = corner[1];
        }
    } else {
        if (corner[1] == 0) {
            res[0] = corner[0] - 1;
            res[1] = 0;
            res[2] = corner[0];
            res[3] = 1;
        } else {
            res[0] = corner[0];
            res[1] = corner[1] - 1;
            res[2] = corner[0] - 1;
            res[3] = corner[1];
        }
    }
    return res;
}

/**
 * This method is a sub method for optimalAlgo
 * It's basically a switch for each value of the corner (for each corner) and a logic for each case
 *
 * @return the chosen case
 */
std::array<std::string, 2> optimalAlgo_logical4Corners() {
    //first let's find the four corners
    std::array<std::array<int, 2>, 4> corners = {{{0, 0}, {0, GAME_ARR[0].size() - 1},
                                                  {GAME_ARR.size() - 1, 0},
                                                  {GAME_ARR.size() - 1, GAME_ARR[0].size() - 1}}};

    for (std::array corner: corners) {
        //find the two near case coordinates for this corner
        std::array<int, 4> mid1Mid2Coord = optimalAlgo_findMid1Mid2(corner);

        //for each corner we will react differently if the corner is taken or
        switch (GAME_ARR[corner[0]][corner[1]]) {
            case 0:
                //if the center is ours and the iterated corner too let's take it
                return std::array<std::string, 2>({std::to_string(corner[0]), std::to_string(corner[1])});
            case 2:
                //if the center is ours and the corner too let's try to take a case near the corner
                if (GAME_ARR[mid1Mid2Coord[0]][mid1Mid2Coord[1]] == 0) {
                    //if the first mid is free take this one
                    return std::array<std::string, 2>(
                            {std::to_string(mid1Mid2Coord[0]), std::to_string(mid1Mid2Coord[1])});
                } else if (GAME_ARR[mid1Mid2Coord[2]][mid1Mid2Coord[1]] == 0) {
                    //if the second mid is free take this one
                    return std::array<std::string, 2>(
                            {std::to_string(mid1Mid2Coord[0]), std::to_string(mid1Mid2Coord[1])});
                }
                //else if no mid is avalaible let's go to the next corner
                break;
            case 1:
            default:
                break;
        }
    }
    //if no case found mid or corner let's take one randomly (but it surely means no case is available so surely never run (it's just by security)
    return std::array<std::string, 2>(
            {std::to_string(rand() % GAME_ARR.size()), std::to_string(rand() % GAME_ARR[0].size())});

}

/**
 * This method is a sub method for optimalAlgo
 * It's basically a switch for each value of the center and a logic for each case
 *
 * @param center The coordinate of the center
 * @return the chosen case
 */
std::array<std::string, 2> optimalAlgo_logical4Center() {
    //first we need to find the center
    std::array<int, 2> center = {(GAME_ARR.size() - 1) / 2, (GAME_ARR[0].size() - 1) / 2};

    //all the logic depend on if the center is taken or not and by whom
    switch (GAME_ARR[center[0]][center[1]]) {
        case 0:
            //if the center is free let's take it
            return std::array<std::string, 2>({std::to_string(center[0]), std::to_string(center[1])});
        case 2:
        case 1:
        default:
            return optimalAlgo_logical4Corners();
    }
};

/**
 * This method check if the user 1 is about to win
 *
 * @param coordToNotLoseCase a ref to a array (std::array<int, 2>) who will contain the two coordinates if found
 * @return true if near to win
 */
bool oppenentNear2Win(std::array<int, 2> &coordToNotLoseCase) {
    int userToCheck = 2;
    //iterate on each case of the array
    for (int x = 0; x < GAME_ARR.size(); x++) {
        for (int y = 0; y < GAME_ARR[0].size(); y++) {
            //if the case is checked by the user we want to win
            if (GAME_ARR[x][y] == userToCheck - 1) {
                //check boundaries for have no error
                bool allowXplus1 = x + 1 - (int) GAME_ARR.size() < 0;
                bool allowXplus2 = x + 2 - (int) GAME_ARR.size() < 0;
                bool allowYplus1 = y + 1 - (int) GAME_ARR[x].size() < 0;
                bool allowYplus2 = y + 2 - (int) GAME_ARR[x].size() < 0;
                bool allowYsub2 = y - 2 >= 0;
                bool allowYsub1 = y - 1 >= 0;

                if (allowXplus1 && allowXplus2) {
                    //check if on a column of 3 case 2 is checked
                    if (GAME_ARR[x + 1][y] < userToCheck || GAME_ARR[x + 2][y] < userToCheck
                                                            && !(GAME_ARR[x + 1][y] == 0 && GAME_ARR[x + 2][y] == 0)) {
                        if (GAME_ARR[x + 1][y] == userToCheck - 1) {
                            coordToNotLoseCase.at(0) = x + 2;
                            coordToNotLoseCase.at(1) = y;
                            return true;
                        } else {
                            coordToNotLoseCase.at(0) = x + 1;
                            coordToNotLoseCase.at(1) = y;
                            return true;
                        }
                    }
                    if (allowYplus1 && allowYplus2) {
                        //check if on a diagonal of 3 case 2 is checked
                        if (GAME_ARR[x + 1][y + 1] < userToCheck || GAME_ARR[x + 2][y + 2] < userToCheck
                                                                    && !(GAME_ARR[x + 1][y + 1] == 0 &&
                                                                         GAME_ARR[x + 2][y + 2] == 0)) {
                            if (GAME_ARR[x + 1][y + 1] == userToCheck - 1) {
                                coordToNotLoseCase.at(0) = x + 2;
                                coordToNotLoseCase.at(2) = y + 2;
                                return true;
                            } else {
                                coordToNotLoseCase.at(0) = x + 1;
                                coordToNotLoseCase.at(1) = y + 1;
                                return true;
                            }
                        }
                    }
                    if (allowYsub1 && allowYsub2) {
                        //check if on a diagonal of 3 case 2 is checked
                        if (GAME_ARR[x + 1][y - 1] < userToCheck || GAME_ARR[x + 2][y - 2] < userToCheck
                                                                    && !(GAME_ARR[x + 1][y - 1] == 0 &&
                                                                         GAME_ARR[x + 2][y - 2] == 0)) {
                            if (GAME_ARR[x + 1][y - 1] == userToCheck - 1) {
                                coordToNotLoseCase.at(0) = x + 2;
                                coordToNotLoseCase.at(1) = y - 2;
                                return true;
                            } else {
                                coordToNotLoseCase.at(0) = x + 1;
                                coordToNotLoseCase.at(1) = y - 1;
                                return true;
                            }
                        }
                    }
                }
                if (allowYplus1 && allowYplus2) {
                    //check if on a line of 3 case 2 is checked
                    if (GAME_ARR[x][y + 1] < userToCheck || GAME_ARR[x][y + 2] < userToCheck
                                                            && !(GAME_ARR[x][y + 1] == 0 && GAME_ARR[x][y + 2] == 0)) {
                        if (GAME_ARR[x][y + 1] == userToCheck - 1) {
                            coordToNotLoseCase.at(0) = x;
                            coordToNotLoseCase.at(1) = y + 2;
                            return true;
                        } else {
                            coordToNotLoseCase.at(0) = x;
                            coordToNotLoseCase.at(1) = y + 1;
                            return true;
                        }
                    }
                }
            }
        }
    }

    //if no 2 case is found not about win so return empty
    return false;
}

/**
 * This method chose the optimal case to check
 * TODO find and change parts of code who miss-works (not had the time to test that part of the code)
 *
 * @return the chosen case
 */
std::array<std::string, 2> optimalAlgo() {
    std::array<int, 2> caseToCheck = {-1, -1};
    if (oppenentNear2Win(caseToCheck)) {
        return std::array<std::string, 2>({std::to_string(caseToCheck[0]), std::to_string(caseToCheck[1])});
    } else {
        return optimalAlgo_logical4Center();
    }
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
        
        bool computerPlayOptimal;
        if (computerPlayOptimal) {
            std::array<std::string, 2> caseChosed = optimalAlgo();
            xString = caseChosed[0];
            yString = caseChosed[1];
        } else {
            //generate random coordinate
            xString = std::to_string(rand() % GAME_ARR.size());
            yString = std::to_string(rand() % GAME_ARR[0].size());
        }
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
    for (int x = 0; x < GAME_ARR.size(); x++) {
        for (int y = 0; y < GAME_ARR[0].size(); y++) {
            switch (GAME_ARR[x][y]) {
                case 2:
                    std::cout << "  X  ";
                    break;
                case 1:
                    std::cout << "  *  ";
                    break;
                case 0:
                default:
                    std::cout << " " << x << "," << y << " ";
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
    bool currentUser = false; //The current user is 1 if false else 2 (or computer)
    displayArray();
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