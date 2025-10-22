#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <string>

//Class templates
//Player class
class Player{
public:
    Player(std::string inputName, int inputNumber)
    :playerName(inputName), number(inputNumber){};

    ~Player(void){};

    std::string getPlayerName(void){
        return this->playerName;
    };

    int getPlayerNumber(void){
        return this->number;
    }
private:
    const std::string playerName;
    const int number;
};

//Function templates
//Assign board state information
std::vector<int> initBoardState(void);
std::vector<int> getPlayerBoardChoice(Player inputPlayer, std::vector<int> inputBoardState);

//Draw the board out on the screen
void drawBoard(std::vector<int> boardState);
char drawCharacter(int drawWidthIterator, int drawDepthIterator, int boardSize, std::vector<int> boardState);
void printBoardStateToConsole(std::vector<int> inputBoardState);

//Check for end states
int checkWinner(std::vector<int> boardState);
bool isInDrawState(std::vector<int> inputBoardState);

//Detect os type and clear the board
int detectOSType(void);
void clearScreen(const int OSType);

//Main functino
int main(void){
    //Init the players
    Player Player1("Player 1", 1);
    Player Player2("Player 2", 2);

    int winner = 0;
    bool draw = false;

    const int maximumLoopTimes = 10;
    int loopCounter = 0;

    std::vector<int> boardState = initBoardState();

    //Clear the board
    bool boardPlayerSwitch = false;
    do{
        //Game loop
        clearScreen(detectOSType());

        drawBoard(boardState);

        winner = checkWinner(boardState);
        draw = isInDrawState(boardState);

        if(winner != 0){
            std::cout << "Well played " << ((winner == 1) ? Player1.getPlayerName() : Player2.getPlayerName()) << std::endl;
        }else if(draw == true){
            std::cout << "Draw! Well played Both!" << std::endl;
        }else{
            if(boardPlayerSwitch == false){
                boardState = getPlayerBoardChoice(Player1, boardState);
            }else{
                boardState = getPlayerBoardChoice(Player2, boardState);
            }
        }
        boardPlayerSwitch = not(boardPlayerSwitch); //Switch current player

        assert(loopCounter++ < maximumLoopTimes); //Makes sure that the program cant run away

    }while(winner == 0 and draw == false);

    std::cout << "Press enter when done:";
    std::cin.get();

    //End game clear screen
    clearScreen(detectOSType());

}

//Function implimentaitons
//Assign board state information
std::vector<int> initBoardState(void){
    int numberOfBoardPositions = 9;
    std::vector<int> boardRestingPosition;
    boardRestingPosition.resize(9);
    for(int clearIterator = 0;clearIterator < numberOfBoardPositions ;clearIterator++){
        boardRestingPosition.at(clearIterator) = 0;
    }
    return boardRestingPosition;
};

std::vector<int> getPlayerBoardChoice(Player inputPlayer, std::vector<int> inputBoardState){
    bool validPlayerChoice = false;
    int boardPosition = -1;
    std::string boardRepresentation = "1|2|3\n-----\n4|5|6\n-----\n7|8|9";

    const int maxNumberOfIterationsForLoop = 10;
    int loopCounter = 0;
    do{
        std::cout << "Board positions\n" << boardRepresentation << std::endl;
        std::cout << inputPlayer.getPlayerName() << " " << "please enter which board region you would like to choose from: ";
        std::cin >> boardPosition;
        std::cin.get();

        if(boardPosition-1 < 9 and boardPosition-1 >= 0 and inputBoardState.at(boardPosition-1) == 0){  //Order of this conditional is deliberate.
                                                                                                    //The indcies must be valid before going into the vector
            std::cout << inputPlayer.getPlayerName() << " " << "Chose position: " << boardPosition << std::endl;
            std::cout << "Press enter to continue";
            std::cin.get();
            inputBoardState.at(boardPosition-1) = inputPlayer.getPlayerNumber();
            validPlayerChoice = true;
        }else{
            clearScreen(detectOSType());
            std::cout << "Input: " << boardPosition << "\nPlease enter a possible board position!\n" << std::endl;
            drawBoard(inputBoardState);
        }

    //Check loop stable else assertfailure
    assert(loopCounter++ < maxNumberOfIterationsForLoop);
    }while(validPlayerChoice == false);

    return inputBoardState;
};

//Draw the board out on the screen
void drawBoard(std::vector<int> boardState){
    //Draw the board

    const int individualSquareSize = 9;

    //Iterate through board and draw characters
    int boardSize = (individualSquareSize * 3) + 2;
    for(int drawDepthIterator = 0; drawDepthIterator < boardSize; drawDepthIterator++){
        for(int drawWidthIterator = 0; drawWidthIterator < boardSize; drawWidthIterator++){
            std::cout << drawCharacter(drawWidthIterator, drawDepthIterator, boardSize, boardState);
        }
        std::cout << std::endl;
    }

};

char drawCharacter(int drawWidthIterator, int drawDepthIterator, int boardSize, std::vector<int> boardState){
    char tempCharacter = 'A';
    const char verticalLine = '|';
    const char horizontalLine = '-';
    const char blankSpace = ' ';
    const int boardPositionCheckValue = ((boardSize-2)/3);

    //Check row and column number
    int checkRowNumber = (drawDepthIterator < boardPositionCheckValue) ? 1 : ((drawDepthIterator < boardPositionCheckValue*2+1) ? 2 : 3);
    int checkColumnNumber = (drawWidthIterator < boardPositionCheckValue) ? 1 : ((drawWidthIterator < boardPositionCheckValue*2+1) ? 2 : 3);

    //Logic for character to draw
    if(drawDepthIterator == boardPositionCheckValue or drawDepthIterator == boardPositionCheckValue*2 + 1){
        if(drawWidthIterator == boardPositionCheckValue or drawWidthIterator == boardPositionCheckValue*2 + 1){
            tempCharacter = verticalLine;
        }else{
            tempCharacter = horizontalLine;
        }
    }else{
        if(drawWidthIterator == boardPositionCheckValue or drawWidthIterator == boardPositionCheckValue*2 + 1){
            tempCharacter = verticalLine;
        }else{
            tempCharacter = blankSpace;
        }
    }

    //Now check to substitute in the player token
    if(tempCharacter == blankSpace){
        int boardIndex = -1;
        if(checkRowNumber == 1 and checkColumnNumber == 1){
            boardIndex = 0;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 1 and checkColumnNumber == 2){
            boardIndex = 1;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 1 and checkColumnNumber == 3){
            boardIndex = 2;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 2 and checkColumnNumber == 1){
            boardIndex = 3;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 2 and checkColumnNumber == 2){
            boardIndex = 4;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 2 and checkColumnNumber == 3){
            boardIndex = 5;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 3 and checkColumnNumber == 1){
            boardIndex = 6;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else if(checkRowNumber == 3 and checkColumnNumber == 2){
            boardIndex = 7;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }else{
            boardIndex = 8;
            tempCharacter = boardState.at(boardIndex) == 0 ? ' ' : (boardState.at(boardIndex) == 1 ? 'X' : 'O');
        }
    }

    return tempCharacter;
};

void printBoardStateToConsole(std::vector<int> inputBoardState){
    for(int printIterator = 0; printIterator < inputBoardState.size(); printIterator++){
        std::cout << inputBoardState.at(printIterator);
    }
    std::cout << std::endl;
};

//Check for end states
bool isInDrawState(std::vector<int> inputBoardState){ //outputs true if in drawstate and false if not
    bool remainingUnusedBoardPositions = true;
    for(int searchIterator = 0; searchIterator < inputBoardState.size(); searchIterator++){
        if(inputBoardState.at(searchIterator) == 0){
            remainingUnusedBoardPositions = false;
            break;
        }
    }
    return remainingUnusedBoardPositions;
};

int checkWinner(std::vector<int> boardState){
    int winningPlayer = 0;

    //Find winning board states
    if(boardState.at(0)==boardState.at(1) and boardState.at(0)==boardState.at(2)){ //First look at the three horizontal lines

        winningPlayer = boardState.at(0);

    }else if(boardState.at(3)==boardState.at(4) and boardState.at(3)==boardState.at(5)){

        winningPlayer = boardState.at(3);

    }else if(boardState.at(6)==boardState.at(7) and boardState.at(6)==boardState.at(8)){

        winningPlayer = boardState.at(6);

    }else if(boardState.at(0)==boardState.at(3) and boardState.at(0)==boardState.at(6)){ //Next look at the three vertical lines

        winningPlayer = boardState.at(0);

    }else if(boardState.at(1)==boardState.at(4) and boardState.at(1)==boardState.at(7)){

        winningPlayer = boardState.at(1);

    }else if(boardState.at(2)==boardState.at(5) and boardState.at(2)==boardState.at(8)){

        winningPlayer = boardState.at(2);

    }else if(boardState.at(0)==boardState.at(4) and boardState.at(0)==boardState.at(8)){ //Last look at the two diagonal lines

        winningPlayer = boardState.at(0);

    }else if(boardState.at(6)==boardState.at(4) and boardState.at(6)==boardState.at(2)){

        winningPlayer = boardState.at(6);

    }
    return winningPlayer;
};

//Detect os type and clear the board
int detectOSType(void){
    if(getenv("windir")!=nullptr){
        return 0; //Is windows
    }else if(getenv("HOME")!=nullptr){
        return 1; //Is Posix compliant os (Well assume its a linux)
    }else{
        return 2; //Something I dont know how to deal with atm
    }
};

void clearScreen(const int OSType){
    if(OSType == 0){
        std::system("cls");
    }else if(OSType == 1){
        std::system("clear");
    }else{
        assert(1==0); //I dont know how to deal with this atm
    }
};






