#include "Board.h"

using namespace std;

int imageIndex = 1; //used by the draw function

//display 2D coordinates
std::ostream& operator<<(std::ostream& os, const Coordinate& ind)
{
    int a = int(ind.i);
    int b = int(ind.j);
    return os << a << "," << b;
}

gameChar::gameChar() { c = '.'; }

gameChar::gameChar(const char c_)
{
	if(!validChar(c_)) throw IllegalCharException(c_);
	c = c_;
}

gameChar& gameChar::operator= (const gameChar& other) 
{ 
    c=other.c; 
    return *this;
}

bool gameChar::operator== (const gameChar& other) const { return (c == other.c); }		
bool gameChar::operator== (char c_) const { return (c == c_); }
bool gameChar::operator!= (const gameChar& other) const { return (c != other.c); }		
bool gameChar::operator!= (char c_) const { return (c != c_); }
		
bool gameChar::validChar(char c) //check that given char is legal
{
	if(c == '.' || c == 'X' || c == 'O') return true;
	return false;
}

//constructor
Board::Board(const int N)   
{
    boardSize = N;
    for(int i=0; i<N; i++){
    	gameChar c = '.';
    	vector<gameChar> temp;
    	for(int j=0; j<N; j++){
    		temp.push_back(c);
    	}
    	temp.push_back(c);
    	board.push_back(temp);
    }
}

Board::Board()   
{
    boardSize = 3;
    for(int i=0; i<3; i++){
    	gameChar c = '.';
    	vector<gameChar> temp;
    	for(int j=0; j<3; j++){
    		temp.push_back(c);
    	}
    	temp.push_back(c);
    	board.push_back(temp);
    }
}
	
//assignment from other board
Board& Board::operator= (const Board& other)
{
	board = other.board;
    boardSize = other.boardSize;
    return *this;
}
	
//assignment from a char, fills entire board with provided char
Board& Board::operator= (char c)
{
	gameChar tmp(c);
    for(int i=0; i<boardSize; i++){
    	for(int j=0; j<boardSize; j++){
    		board[i][j] = tmp;
    	}
    }
    return *this;
}

//access board member indicated by 2D coordinate ind
gameChar& Board::operator[](const Coordinate ind) 
{ 
	if(!inBounds(ind)) throw IllegalCoordinateException(ind);
	return board[ind.i][ind.j]; 
}
const gameChar& Board::operator[](const Coordinate ind) const
{
    if(!inBounds(ind)) throw IllegalCoordinateException(ind);
    return board[ind.i][ind.j];
}

//creates an n*n ppm format image representing the board with squares of color
string Board::draw(const int n)
{
    int imgSegLen = n/boardSize; 
    //build file name with incrementing index to avoid overwriting
    string filename = "Game_Board";
	filename += std::to_string(imageIndex);
	filename += ".ppm";
	imageIndex += 1;
    
    ofstream boardFile (filename);
    boardFile << "P6" << endl; //ppm file type identifier
    boardFile << n << " " << n << endl; //image width and height
    boardFile << "1" << endl; //maximum color value
    
    if (boardFile.is_open()){
        //go over board array and draw image representation
        for(int i = 0; i < boardSize; i++){
            for(int j = 0; j < boardSize; j++){
                if(board[i][j] == '.'){ //an empty square is black
                    for(int x = (i * imgSegLen); x < ((i + 1) * imgSegLen); x++){
                        for(int y = (j * imgSegLen); y < ((j + 1) * imgSegLen); y++){
                            boardFile << 0 << " " << 0 << " " << 0 << endl; //R,G,B values
                        }
                    }
                }
                else if(board[i][j] == 'X'){ //a square with an X is red
                    for(int x = (i * imgSegLen); x < ((i + 1) * imgSegLen); x++){
                        for(int y = (j * imgSegLen); y < ((j + 1) * imgSegLen); y++){
                            boardFile << 1 << " " << 0 << " " << 0 << endl; //R,G,B values
                        }
                    }    
                }
                else{ //a square with an O is blue
                    for(int x = (i * imgSegLen); x < ((i + 1) * imgSegLen); x++){
                        for(int y = (j * imgSegLen); y < ((j + 1) * imgSegLen); y++){
                            boardFile << 0 << " " << 0 << " " << 1 << endl; //R,G,B values
                        }
                    }    
                }
            }
        }
        boardFile.close();
        return filename;
    }
    cout << "Unable to open file";
    return " ";
}

int Board::size() const
{
    return boardSize;
}
	
bool Board::inBounds(Coordinate ind) const //check that coordinates are not outside the board
{
	if(int (ind.i) < 0 || int (ind.j) < 0 || int (ind.i) >= boardSize || int (ind.j) >= boardSize) return false;
	return true;
}
