//
//  game.h
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
#ifndef game_h
#define game_h
#endif
#include "player.h"
#include "board.h"
#include "tiles.h"
using namespace std;

class Game{
private:
	vector<player> players;
	Board board;
	tiles tileManager;
	int currentPlayerIndex; // current player

public:
	Game(const vector<player>& playerList){
		players = playerList; // Initialize players
		currentPlayerIndex = 0; // first player
	}

	void playGame(){
		cout << "Game started!\n";
		while (true) {
			player& currentPlayer = players[currentPlayerIndex];
			cout << currentPlayer.getName() << " 's turn.\n";

			int action; // player action
			cout << "Enter 1 to pass, 2 to play, 3 to exit: ";
			cin >> action;
			if (action == 1){ // pass
				cout << currentPlayer.getName() << "passed this turn.\n";
				currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // next player, if there is no next player, go back to the first player
				continue;
			}else if (action == 2){
				string word, direction;
				int x , y;
				cout << "enter word you want to play: " << endl;
				cin  >> word;
				
				cout << "Enter starting cordinated (x,y): " << endl;
				cin >> x >> y;
				
				cout << "enter direction (H for horizontal, V for vertical: " << endl;
				cin >> direction;
				if( currentPlayer.playWord(board, tileManager,x ,y, direction, word)){
					board.print_board();
					cout << "word played successfully! " << endl;
			
				}
				else{
					cout << "invalid move, try again " << endl;
					continue;
				}

				currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // next player, if there is no next player, go back to the first player
			}
			else if (action == 3){ // exit
				cout << "Game Over!\n";
				int maxScore = 0;
				string winner;
				for ( auto p : players){
					if ( p.getScore() > maxScore) {
						maxScore = p.getScore();
						winner = p.getName();
					}
				}
				cout << "The winner is " << winner << "with " << maxScore << "\n";
				break; // exit the game loop
			}else {
				cout << "Invalid action, please enter 1, 2, 3.\n";
				continue;
			}
		}
	}
};
