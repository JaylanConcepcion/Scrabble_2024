//
//  main.cpp
//  scrabble (combined)
//
//  Created by Jaylan Concepcion on 12/10/24.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include<fstream>
#include <map>
#include "player.h"
#include "game.h"
#include "board.h"
#include "tiles.h"
using namespace std;


int main() {
	cout << "Welcome to Scrabble!" << endl;
	Board board;
	
	cout << "Enter how many players(2-4): " << endl;
	string player_name;
	int player_count= 0;
	cin >> player_count;
	vector <player> players;
	for(int i = 1; i <= player_count; i ++ ){
		cout << "enter name of player " << i << endl;
		cin >> player_name;
		players.emplace_back(player_name);
	}
	
	vector<string> initial_tiles = {"A", "B", "C", "D", "E", "F", "G"};
		for (auto& p : players) {
			p.addTiles(initial_tiles);
		}
	
	Game game(players);
	game.playGame();
	cout << "Player List: " << endl;
	for( auto& p: players){
		cout << p.getName() <<" score: " <<p.getScore() << endl;
	}
	

	cout << "Thanks For Playing!" << endl;
	return 0;
};
