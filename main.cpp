
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "HangManLib.h"
using namespace std;

int main()
{ 
	//variables
	Player p_array[PLAYER_SIZE]; //player array
	string keyword_array[KEYWORD_SIZE]; //keyword array
	string recent_player; //name of recent player
	int size_p, size_k; // actual size of player array and keywords array
	size_p = size_k = 0;
	
	//implement the hang man game
	PlayHangMan(keyword_array, size_k, p_array, size_p, recent_player);
	
	//export newest changes to files
	ExportPlayerScore(p_array, size_p, recent_player);
	ExportKeyWord(keyword_array, size_k);

	return 0;
}