//
//  player2.0.hpp
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
#ifndef player2_0_h
#define player2_0_h
#include <stdio.h>
#endif
#include "game.h"
#include "board.h"
#include "tiles.h"
using namespace std;
class player{
private:
	string player_name="";
	int score=0;
	vector<string> hand;
public:
	player( const string& name): player_name(name), score(0){}
	
	string getName(){ return player_name;}
	int getScore(){return score;}
	void addScore(int points){score += points;}
	
	void addTiles(vector<string>& new_tile){
		hand.insert(hand.end(), new_tile.begin(), new_tile.end());
	}
	
	void displayHand(){
		cout << player_name << "'s Tiles: " << " ";
		for(const auto& tile:hand) cout << tile << " " << endl;
	}
	bool hasTilesForWord(const string& word){
		map<string, int> tile_count;
		for(const auto&tile:hand) tile_count[tile]++;
		for(char c: word){
			string letter(1,toupper(c));
			if (tile_count[letter] > 0) tile_count[letter]--;
			else
				return false;
			
		}
		return true;
	}
	void removeTilesForWord(const string& word){
		for(char c : word){
			string letter(1, toupper(c));
			auto it = find(hand.begin(), hand.end(), letter);
			if(it != hand.end())
				hand.erase(it);
		}
	}
	bool playWord(Board& board, tiles& tileManager, int x, int y, const string& direction, const string& word) {
		string used_tiles = "";
		int word_score = 0;

		for (size_t i = 0; i < word.size(); i++) {
			int new_x = x + (direction == "H" ? i : 0);
			int new_y = y + (direction == "V" ? i : 0);

			if (board.bound_check(new_x, new_y)) {
				cout << "Word placement out of bounds.\n";
				return false;
			}

			string letter(1, toupper(word[i]));
			string current_tile = board.get_tile(new_x, new_y);

			// Check for conflicts
			if (current_tile != "*" && current_tile != letter) {
				cout << "Conflict with existing tiles on the board at (" << new_x << ", " << new_y << ").\n";
				return false;
			}

			// Only add new tiles to used_tiles and calculate score
			if (current_tile == "*") {
				used_tiles += letter;
				word_score += tileManager.calculate_score(letter);
			}
		}

		
		if (!hasTilesForWord(used_tiles)) {
			cout << "You don't have the necessary tiles to play this word.\n";
			return false;
		}

		// Place the new tiles on the board
		for (size_t i = 0; i < word.size(); i++) {
			int new_x = x + (direction == "H" ? i : 0);
			int new_y = y + (direction == "V" ? i : 0);

			if (board.get_tile(new_x, new_y) == "*") {
				board.place_tile(new_x, new_y, string(1, toupper(word[i])));
			}
		}

		// Update score and hand
		removeTilesForWord(used_tiles);
		addScore(word_score);
		cout << getName() << " played " << word << "for" << word_score << "points" << endl;
		return true;
	}
	
};
