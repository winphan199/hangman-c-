#pragma once

//This is the structure of a player
struct Player
{
	std::string name;
	int highest_score;
};

const std::string SCORES = "Scores.txt"; // name of the Score file
const std::string KEYWORDS = "Keywords.txt"; // name of the keyword file
const int PLAYER_SIZE = 10; // max size of player array
const int KEYWORD_SIZE = 500; // max size of keyword array

//Process for player
Player convertStringToPlayer(std::string line);
void addPlayerToArray(Player* p_array, int& p_size, const Player& p);
void ExportPlayerScore(Player* p_array, int size, std::string recent_p);
void selectionSort(Player* p_array, int p_size);

//Process for keywords
void AddNewKeyWord(std::string* key, int& size);
void ExportKeyWord(std::string* key, int size);

//Process for the game
void preProcessForHangMan(Player* p_array, int& p_size, std::string& rec_p, std::string* key, int& k_size);
int outputMenu();
void GamePlay(std::string* key, int k_size, bool& isloser);
void displayHangMan(int state);
void PlayHangMan(std::string* key, int& k_size, Player* p_array, int& p_size, std::string& recent_p);
std::string generateSpace(std::string s, int max_length);
void displayTopScores(Player* p_array, int p_size);