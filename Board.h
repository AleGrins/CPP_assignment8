#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include <string>
using namespace std;

#pragma once

struct Coordinate //used to receive 2D coordinates for the [] overload
{
	uint i, j;
};

//coordinates out of bounds, returns given coordinates
class IllegalCoordinateException : public std::exception {
	Coordinate ind;
    
    public:
    	IllegalCoordinateException(Coordinate ind_) : ind (ind_) {}

        Coordinate theCoordinate() const { return ind; }
};

//illegal character, returns given char
class IllegalCharException : public std::exception {
	char c;
    
    public:
    	IllegalCharException(char c_) : c (c_) {}

        char theChar() const { return c; }
};

//custom char class to accept only specific chars and throw exception otherwise
class gameChar {
	public:
		gameChar();
		gameChar(const char c_);
		
		gameChar& operator= (const gameChar& other);
		
		bool operator== (const gameChar& other) const;		
		bool operator== (char c_) const;
		bool operator!= (const gameChar& other) const;		
		bool operator!= (char c_) const;
		
		//Output operator
		friend ostream& operator<< (ostream& output, const gameChar& ch)
		{ 
    		output << ch.c;
    		return output;            
    	} 
    	
    	//Input operator
    	friend istream& operator>> (istream& input, gameChar& ch)
    	{
    		input >> ch.c;
    		return input;
    	}
	
	private:
		char c;
		bool validChar(char c); //check that given char is legal
};

class Board {
public:
	
	//constructors
    Board(const int N);
    Board();
	
	//assignment from other board
	Board& operator= (const Board& other);
	
	//assignment from a char, fills entire board with provided char
	Board& operator= (char c);

	//access board member indicated by 2D coordinate ind
	gameChar& operator[](const Coordinate ind);
	const gameChar& operator[](const Coordinate ind) const;
	
	int size() const;
	
	//display the board
	friend ostream& operator<< (ostream& output, const Board& b)
	{ 
		for(int i=0; i<b.boardSize; i++){
    		for(int j=0; j<b.boardSize; j++){
    			output << b.board[i][j];
    		}
    		output << endl;
    	}
    	return output;            
    }
    
    //Input a board
    friend istream& operator>> (istream& input, Board& b)
    {
    	for(int i=0; i<b.boardSize; i++){
    		for(int j=0; j<b.boardSize; j++){
    			input >> b.board[i][j];
    		}
    	}
    	input >> b.boardSize;
    	return output;
    }
    
    string draw(const int n);
	
private:
	vector<vector<gameChar> >board; 
	int boardSize;
	
	bool inBounds(Coordinate ind) const; //check that coordinates are not outside the board
};
