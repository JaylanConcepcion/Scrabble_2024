//
//  board.h
//  scrabble (combined)
//
//  Created by Jaylan Concepcion on 12/13/24.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include<fstream>
#include <map>
#ifndef board_h
#define board_h
#endif /* board_h */
#include "player.h"
#include "game.h"
#include "tiles.h"
using namespace std;

class Board {
private:
	string game_board[15][15];
public:
	Board() {
		for (int i = 0; i < 15; i++) //i is y coordinate, j is x
		{
			for (int j = 0; j < 15; j++)
			{
				//game_board[j][i] = to_string(j) + to_string(i);
				game_board[j][i] = "*";
			}
		}
	}
	void print_board();
	void place_tile(int, int, string);
	string get_tile(int, int);
	string horiz_word(int, int);
	string vert_word(int, int);
	bool bound_check(int, int);
};

void Board::print_board() {
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (i == 15) //print label for y axis on bottom
				cout << left << setw(3) << j;
			else if (j == 15) //print label for x axis on right
				cout << i << endl;
			else
				cout << get_tile(j, i) << "  ";
		}
	}
	cout << endl;
	return;
}

void Board::place_tile(int x, int y, string letter) {
	if (bound_check(x, y))
		cout << "Out of bounds input." << endl;
	else if (get_tile(x, y) == "*")
		game_board[y][x] = letter;
	else
		cout << "Space is already taken." << endl;
	return;
}

string Board::get_tile(int x, int y) {
	if (bound_check(x, y)) {
		cout << "Out of bounds input." << endl;
		return "";
	}
	else
		return game_board[y][x];
}

string Board::horiz_word(int x, int y) { //given (x, y) finds all letters from left to right until it hits a blank spot, adds the ltters to form the word, then returns it
	int leftmost = x;
	string word = "";
	if (bound_check(x, y)) {
		cout << "Out of bounds input." << endl;
	}
	else if (get_tile(x, y) == "*") {
		cout << "Empty space at given coordinate" << endl;
	}
	else {
		while (leftmost - 1 >= 0 && get_tile(leftmost - 1, y) != "*") //find the leftmost letter of the word
			leftmost--;
		while (leftmost < 15 && get_tile(leftmost, y) != "*") { //place the word into variable from left to right, letter by letter
			word += get_tile(leftmost, y);
			leftmost++;
		}
	}
	return word;
}


string Board::vert_word(int x, int y) { //given (x, y) finds all letters from top to bottom until it hits a blank spot, adds the ltters to form the word, then returns it
	int top = y;
	string word = "";
	if (bound_check(x, y)){
		cout << "Out of bounds input." << endl;
	}
	else if (get_tile(x, y) == "*") {
		cout << "Empty space at given coordinate" << endl;
	}
	else {
		while (top - 1 >= 0 && get_tile(x, top - 1) != "*") //find the topmost letter of the word
			top--;
		while (top < 15 && get_tile(x, top) != "*") { //place the word into variable from top to bottom, letter by letter
			word += get_tile(x, top);
			top++;
		}
	}
	return word;
}

bool Board::bound_check(int x, int y) { //returns true if coordinate is out of bounds, false if not
	return ((x < 0 || x >= 15) || (y < 0 || y >= 15));
}
