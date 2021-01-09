#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "HangManLib.h"
#include <conio.h>
#include <Windows.h>
using namespace std;



//this functions output the starting interface of hangman game
//and asks the users to choose what to do by input 1 of 3 options: 1-New player, 2-Continue, 3-Top scores, 4-Exit
//Return: int value as one of the options 1, 2, 3, 4 above and -1 as for programmer.
int outputMenu()
{
	//variables
	string s; // store option value
	int c;
	//output the menu
	cout << "\n ==============================================================================================================";
	cout << "\n||                                                                                                            ||";
	cout << "\n||  ||     ||       //##\\\\       ||\\\\      || ||#####||     ||\\\\     //||       //##\\\\       ||\\\\      ||     ||";
	cout << "\n||  ||     ||      //    \\\\      || \\\\     || ||     ||     || \\\\   // ||      //    \\\\      || \\\\     ||     ||";
	cout << "\n||  ||     ||     //      \\\\     ||  \\\\    || ||            ||  \\\\_//  ||     //      \\\\     ||  \\\\    ||     ||";
	cout << "\n||  ||=====||    //========\\\\    ||   \\\\   || ||            ||         ||    //========\\\\    ||   \\\\   ||     ||";
	cout << "\n||  ||     ||   //          \\\\   ||    \\\\  || ||   ======   ||         ||   //          \\\\   ||    \\\\  ||     ||";
	cout << "\n||  ||     ||  //            \\\\  ||     \\\\ || ||     ||     ||         ||  //            \\\\  ||     \\\\ ||     ||";
	cout << "\n||  ||     || //              \\\\ ||      \\\\|| ||#####||     ||         || //              \\\\ ||      \\\\||     ||";
	cout << "\n||                                                                                                            ||";
	cout << "\n||                                                                                                            ||";
	cout << "\n||                                                  1. NEW PLAYER                                             ||";
	cout << "\n||                                                  2. CONTINUE                                               ||";
	cout << "\n||                                                  3. TOP SCORES                                             ||";
	cout << "\n||                                                  4. QUIT                                                   ||";
	cout << "\n ==============================================================================================================";

	//Asks for option from player
	cout << "\nType your choice (1, 2, 3, 4): ";
	cin >> s;
	if (s[0] == '1' || s[0] == '2' || s[0] == '3' || s[0] == '4')
	{
		return s[0] - '0';
	}
	else if (s[0] == '-' && s[1] == '1')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


//This function open keywords.txt and scores.txt to retrieve data used for the game
//Parameters: -p_array is the array of player
//			  -p_size is the size of player array
//			  -rec_p is the name of recent player
//			  -key is the array of keywords
//			  -k_size is the size of keyword array
void preProcessForHangMan(Player* p_array, int& p_size, string& rec_p, string* key, int& k_size)
{
	//variables
	fstream file; // variable to open the file
	string line; //temporary variable to store line got from file
	int i = 0; // index used for while loop

	//Open file scores to retrieve top player data
	file.open(SCORES, ios::in);

	if (file.is_open()) // if open file successfully
	{
		getline(file, line); // read number of players
		p_size = stoi(line); // convert to int and save it to player array size

		getline(file, line); //read name of recent player
		rec_p = line;

		while (i < p_size) // go through every line from scores file then convert the line into player type and store it in array of players
		{
			getline(file, line);
			p_array[i] = convertStringToPlayer(line);
			i++;
		}

		//close file after using
		file.close();
	}
	else // if fail to open the file
	{
		cout << "\nError: Can not open scores.txt";
	}

	//open keywords file
	file.open(KEYWORDS, ios::in);

	i = 0; //initialize index
	if (file.is_open()) // if open file successfully
	{
		getline(file, line);
		k_size = stoi(line); // get number of keywords

		while (!file.eof()) // go through every line from keywords file and retrieve data
		{
			getline(file, line);
			key[i] = line.substr(0, line.find(","));
			i++;
		}

		//close file after using
		file.close();
	}
	else // if fail to open the file
	{
		cout << "\nError: Can not open keywords.txt";
	}
}

//This functions convert a line of type string to Player type
//Parameter: -line is the line that is needed to convert to Player type
//Returns converted player
Player convertStringToPlayer(string line)
{
	//Variables
	Player p; // Temporary store player
	string separator = "----"; // separator between player's name and player's score
	string sc; //score as string

	//get player name from the string line
	p.name = line.substr(0, line.find(separator));

	//get player score from the string line
	sc = line.substr(p.name.length() + separator.length());
	p.highest_score = stoi(sc);

	return p;
}

//This functions display the state of hangman depending on how many times the player guess the wrong letter
// There are 5 states (1-5) for the hangman which means player has 5 turns to guess the wrong letter
//Parameter: -state is the state from 1-5 which shows the status of the hangman. The state 5 is when the game is over.
void displayHangMan(int state)
{
	//depends on state to print out the status of hang man
	switch (state)
	{
	case 1:
	{
		cout << "\n ============";
		cout << "\n||          |";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n===";

		break;
	}
	case 2:
	{
		cout << "\n ============";
		cout << "\n||          |";
		cout << "\n||         (^)";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n||           ";
		cout << "\n===";

		break;
	}
	case 3:
	{
		cout << "\n ============";
		cout << "\n||          |";
		cout << "\n||         (^)";
		cout << "\n||          |";
		cout << "\n||          |";
		cout << "\n||          |";
		cout << "\n||           ";
		cout << "\n||";
		cout << "\n===";

		break;
	}
	case 4:
	{
		cout << "\n ============";
		cout << "\n||          |";
		cout << "\n||         (^)";
		cout << "\n||          |";
		cout << "\n||         /|\\";
		cout << "\n||          |";
		cout << "\n||           ";
		cout << "\n||";
		cout << "\n===";

		break;
	}
	case 5:
	{
		cout << "\n ============";
		cout << "\n||          |";
		cout << "\n||         (^)";
		cout << "\n||          |";
		cout << "\n||         /|\\";
		cout << "\n||          |";
		cout << "\n||         / \\ ";
		cout << "\n||";
		cout << "\n===";

		break;
	}
	default:
		break;
	}

}

//this function exports player information to file Scores.txt
//Parameters: -p_array is the array that stores multiple of players' data
//			  -size is the recent size of the player array
//            -recent_p is the name of recent played player
void ExportPlayerScore(Player* p_array, int size, string recent_p)
{
	//variables
	fstream file;//temporary variable to open file

	//open the file
	file.open(SCORES, ios::out);

	//if file open successfully
	if (file.is_open())
	{
		file << size << endl; // write number of players to file
		file << recent_p << endl; //write recent player to file
		for (auto i = 0; i < size; i++) // write player name and scores as format : <name>----<score>
		{
			file << p_array[i].name << "----" << p_array[i].highest_score << endl;
		}

		//close file after using
		file.close();
	}
	else
	{
		cout << "\nError: Can not open the file Scores.txt to output players' data." << endl;
	}

}

//This function helps developer in case want to manually add new keyword to keyword library
//Parameters: -key is the array that stores keywords
//			  -size is the recent size of the array
void AddNewKeyWord(string* key, int& size)
{
	//variables
	int num = 0; // number of keywords want to add
	string new_key; // temporary store keyword
	char c; //Stores option yes or no

	//check if the size of recent keyword array reaches its maximum
	if (size == KEYWORD_SIZE)
	{
		cout << "\nWarning: Keywords storage has reached its maximum capacity and some words will be replaced.\nDo you want to continue(Y/N)? ";
		cin >> c;
		cout << endl;
		if (c == 'N') // if the answer is no then the function stops
		{
			return;
		}
		else if (c != 'Y' && c != 'N') //if input wrong charecter the function stops
		{
			cout << "\nError: Unknown letter." << endl;
			return;
		}
	}

	//Asks for number of keywords want to add
	while (1)
	{
		cout << "\nHow many keywords you want to add? ";
		cin >> num;

		if (size + num > KEYWORD_SIZE) //if the size + number of new keywords > keyword capacity then input new number of keywords
		{
			cout << "\nError: Because of keyword capacity. Can not add that much keywords.";
		}
		else
		{
			break;
		}
	}
	cout << endl;


	//Asks for what keywords to add
	for (int i = 0; i < num; i++)
	{
		cout << "\nKeyword [" << i + 1 << "]: ";
		cin >> new_key;

		//add keyword to the keyword array
		key[size + i] = new_key;
	}

	//update size of keyword array
	size += num;
}

//This function exports keywords from keyword array to keywords.txt
//Parameters: -key is the keyword array
//			  -size is the size of recent array
void ExportKeyWord(string* key, int size)
{
	//varibles
	fstream file; // temporary variable to open file

	//open Keywords.txt file to write new data
	file.open(KEYWORDS, ios::out);

	//if open successfully
	if (file.is_open())
	{
		file << size << endl; //write the number of keywords
		for (int i = 0; i < size; i++) //write the keyword on each row as format: <keyword>,
		{
			file << key[i] << "," << endl;
		}

		//close the file after using
		file.close();
	}
	else
	{
		cout << "\nError: Can not open Keywords.txt to write data." << endl;
	}
}

//This function proceed the hangman game
//Parameters: -key is the keyword array
//			  -k_size is the keyword array size
//			  -p_array is the top player array
//			  -p_size is the size of player array
//			  -recent_p is the name of recent played player
void PlayHangMan(string* key, int &k_size, Player* p_array, int &p_size, string &recent_p)
{
	//variables
	int option = 0;//store option from output menu
	string new_player; // name of new player
	string c; //store option yes or no
	bool isloser = false;
	Player p; // player data
	int win_times = 0; // store number of times that a specific player wins
	char temp; //store character player input to exit score board

	fflush(stdin); // delete data from buffer for sure

	//load data from saved file before game display
	preProcessForHangMan(p_array, p_size, recent_p, key, k_size);

	//the game start
	do
	{
		system("cls");
		//display the interface of the game
		fflush(stdin);
		option = outputMenu();

		if (option == 1) // play game as new player
		{
			system("cls");
			win_times = 0;
			do
			{
				cout << "\nType your name: "; // input new player's name
				cin.ignore(2, '\n');
				getline(cin, new_player);

				//the maximun length of the name is 16 characters
				if (new_player.length() > 10)
				{
					cout << "\nError: The maximun length for name is 10." << endl;
				}
				else // valid name then get out of while loop
				{
					break;
				}
			} while (true);
			
			p.name = new_player; // store name of player
			recent_p = new_player; // get name of recent player
			do
			{
				GamePlay(key, k_size, isloser); // proceed the game

				//add loser data to player array when a player loses
				if (isloser)
				{
					isloser = false;
					p.highest_score = win_times; //store scores of player
					addPlayerToArray(p_array, p_size, p); // add player to player array
					break; // out of the (1) while loop
				}
				else //when player wins
				{
					win_times++;

					while (1) //(2) loop
					{
						cout << "\nDo you want to continue (Y/N)? "; // ask player if player wants to continue
						cin >> c;

						if (c[0] == 'N' || c[0] == 'n')
						{
							p.highest_score = win_times;
							addPlayerToArray(p_array, p_size, p);
							break; // get out of (2) while loop
						}
						else if (c[0] == 'Y' || c[0] == 'y')
						{
							break; // get out of (2) while loop
						}
						else // when player type unknow character
						{
							cout << "\nUnknow character" << endl; // error raise and ask player to input the right character
						}
					}
					if (c[0] == 'N' || c[0] == 'n')
					{
						break; // get out of (1) loop
					}
				}
			} while (1);//(1) loop
		}
		else if (option == 2) //play as previous player
		{
			system("cls");
			win_times = 0;
			//store name to temporary player
			p.name = recent_p;
			p.highest_score = 0; //reset player score
			//notify player who is playing
			cout << "\n" << recent_p << " is playing." << endl;
			Sleep(1500);
			do
			{
				GamePlay(key, k_size, isloser); // proceed the game

				//add loser data to player array when a player loses
				if (isloser)
				{
					isloser = false;
					p.highest_score = win_times; //store scores of player
					addPlayerToArray(p_array, p_size, p); // add player to player array
					break; // out of the (1) while loop
				}
				else //when player wins
				{
					win_times++;

					while (1) //(2) loop
					{
						cout << "\nDo you want to continue (Y/N)? "; // ask player if player wants to continue
						cin >> c;

						if (c[0] == 'N' || c[0] == 'n')
						{
							p.highest_score = win_times;
							addPlayerToArray(p_array, p_size, p);
							break; // get out of (2) while loop
						}
						else if (c[0] == 'Y' || c[0] == 'y')
						{
							break; // get out of (2) while loop
						}
						else // when player type unknow character
						{
							cout << "\nUnknow character" << endl; // error raise and ask player to input the right character
						}
					}

					if (c[0] == 'N' || c[0] == 'n')
					{
						break; // get out of (1) loop
					}
				}
			} while (1); //(1) loop
		}
		else if (option == 3) //print out top scores
		{
			system("cls");
			//cout top scores
			displayTopScores(p_array, p_size);
			cout << "\nPress any key to exit." << endl;
			_getch();
		}
		else if (option == 4) // exit the game
		{
			return; // exit play hangman function and have new data to export
		}
		else if (option == -1)
		{
			system("cls");
			cout << "\n _____  ________      ________ _      ____  _____  ______ _____    __  __  ____  _____  ______ ";
			cout << "\n|  __ \\|  ____\\ \\    / |  ____| |    / __ \\|  __ \\|  ____|  __ \\  |  \\/  |/ __ \\|  __ \\|  ____|";
			cout << "\n| |  | | |__   \\ \\  / /| |__  | |   | |  | | |__) | |__  | |__) | | \\  / | |  | | |  | | |__   ";
			cout << "\n| |  | |  __|   \\ \\/ / |  __| | |   | |  | |  ___/|  __| |  _  /  | |\\/| | |  | | |  | |  __|  ";
			cout << "\n| |__| | |____   \\  /  | |____| |___| |__| | |    | |____| | \\ \\  | |  | | |__| | |__| | |____ ";
			cout << "\n|_____/|______|   \\/   |______|______\\____/|_|    |______|_|  \\_\\ |_|  |_|\\____/|_____/|______|";
			cout << endl;
			AddNewKeyWord(key, k_size);
		}
		else
		{
			cout << "\nError: Invalid input." << endl;
			Sleep(1500);
		}
	}
	while (true);
}

//This function proceeds the detail of the hangman game play
//Parameters: -key is the keyword array
//			  -k_size is the size of keyword array
//            -isloser is the flag that marks player lose this game or win this game
void GamePlay(string* key, int k_size, bool& isloser)
{
	//variables
	int rand_index = 0; // random index
	string displayed_word, // string that display on the screen
		keyword; // string that stores keyword
	bool is_correct_c = false; // flag to know if player guess right word or not
	string typed_char; // this string will take the input from player
	char typed_char_arr[150]; // array that stores typed char from the player
	int k = 0; //index for typed_char_arr[] can be used as typed_char_arr[] size
	int wrong_times = 0; // store number of times that player type wrong letter
	int win_times = 0; // store number of times that a specific player wins
	bool is_previous_char = false; //flag to check if the letter is pretyped

	//generate random index
	srand(time(NULL));
	rand_index = rand() % (k_size - 1 - 0 + 1) + 0; //generate random index from 0 to k_size

	keyword = key[rand_index]; // store keyword from keyword array to keyword variable

	for (int i = 0; i < keyword.length(); i++)
	{
		displayed_word.push_back('_'); // create a string of _____ depends on the length of keyword length
	}

	
	do
	{
		system("cls");
		is_correct_c = false; // flag to know if player guess right word or not
		cout << "\nKeyword: " << displayed_word;
		displayHangMan(wrong_times);
		cout << "\nGuess a letter: ";
		cin >> typed_char; // input the character from player


		for (int i = 0; i < k; i++) // go through every char in typed char array. If k == 0 then no typed char added => skip
		{
			if (typed_char[0] == typed_char_arr[i])
			{
				cout << "\nError: Letter is used. Please type another letter." << endl;
				Sleep(1500);
				is_previous_char = true;
				break;
			}
		}

		if (is_previous_char) // if the typed char flag is true => tell player to input another character
		{
			is_previous_char = false;
			continue;
		}
		else // else include the letter in typed char array
		{
			typed_char_arr[k] = typed_char[0]; // push typed letter to the typed letter string
			k++;
		}

		for (int i = 0; i < keyword.length(); i++)
		{
			if (typed_char[0] == keyword[i]) // if player guess correct letter
			{
				displayed_word.replace(i, 1, 1, typed_char[0]); // replace _ with the correct letter

				is_correct_c = true; // turn the correct flag to true
			}
		}

		//if the correct flag is true => the player type correct letter => display
		//if the correct flag is false => the player is wrong this time => display hangman
		if (!is_correct_c)
		{
			wrong_times++; // wrong times increase as player typed wrong letter => wrong_times = 5 => game over
			if (wrong_times == 5)
			{
				system("cls");
				isloser = true; //set the loser flag to true
				cout << "\nThe answer is: " << keyword << endl;
				displayHangMan(wrong_times);
				cout << "\nSORRY! YOU DID NOT MAKE IT!" << endl;
				Sleep(2000);
				break; //out of (1) loop
			}
		}
		else if (displayed_word.compare(keyword) == 0) //if the player has got all the letter for keyword then he wins
		{
			cout << "\nKeyword: " << displayed_word;
			cout << "\nCONGRATS! YOU WIN!" << endl;
			break;
		}
	} while (1); //(1)

}

//This function app player to top player array
//Parameters: -p_array is the array of top score player
//			  -p_size is the size of the top score player array
//			  -p is the player that is needed to add
void addPlayerToArray(Player* p_array, int& p_size, const Player& p)
{
	bool issamename = false; 

	
	//if p_array size reaches its maximum capacity then replace the last player data by this new one
	if (p_size >= PLAYER_SIZE)
	{
		for ( int i = 0; i < p_size; i++) // find if have the same name
		{
			if (p.name.compare(p_array[i].name) == 0) // if found the same name, only replace if have higher score
			{
				issamename = true;
				if (p.highest_score > p_array[i].highest_score)
					p_array[i] = p; 
				break;
			}
		}

		if (!issamename)
		{
			for (int i = 0; i < p_size; i++)
			{
				if (p.highest_score >= p_array[i].highest_score)
				{
					p_array[i] = p;
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < p_size; i++) // find if have the same name
		{
			if (p.name.compare(p_array[i].name) == 0) // if found the same name, only replace if have higher score
			{
				issamename = true;
				if (p.highest_score > p_array[i].highest_score)
				{
					p_array[i] = p;;
				}
				break;
			}
		}

		if (!issamename)
		{
			p_array[p_size] = p;
			p_size++; //update size
			
		}
	}
	selectionSort(p_array, p_size);
}

//This function displays the players with highest scores and their score
//Parameters: -p_array is the array that contains data of these players
//			  -p_size is the size of the array
void displayTopScores(Player* p_array, int p_size)
{   //display the titile
	cout << "\n ============================================";
	cout << "\n||   _____             _    _               ||    ";
	cout << "\n||  |  __ \\           | |  (_)              ||    ";
	cout << "\n||  | |__) |__ _ _ __ | | ___ _ __   __ _   ||    ";
	cout << "\n||  |  _  // _` | '_ \\| |/ / | '_ \\ / _` |  ||    ";
	cout << "\n||  | | \\ \\ (_| | | | |   <| | | | | (_| |  ||    ";
	cout << "\n||  |_|  \\_\\__,_|_| |_|_|\\_\\_|_| |_|\\__, |  ||    ";
	cout << "\n||                                   __/ |  ||    ";
	cout << "\n||                                  |___/   ||     ";
	cout << "\n||                                          ||";
	cout << "\n||            NAME         SCORE            ||";
	cout << "\n||                                          ||";

	selectionSort(p_array, p_size);
	for (int i = 0; i < p_size; i++) // display player ranking
	{
		cout << "\n||            " << p_array[i].name << generateSpace(p_array[i].name, 13) << p_array[i].highest_score << generateSpace(to_string(p_array[i].highest_score),17) << "||";
	}
	cout << "\n||                                          ||"; // display the close box
	cout << "\n ============================================";
}


//This function generates space from the first letter of a string to another string: <string length>"       "<another string>
//Parameters: s is the string whose length will be used
//max_length is the total of string length and space needed to generate in the above format
//Return: a string as a space generated: "      "
string generateSpace(string s, int max_length)
{
	string temp; //temporary string
	int l; //temporary length

	l = max_length - s.length(); // calculate length
	for (int i = 0; i < l; i++) // generate space
	{
		temp.push_back(' ');
	}

	return temp;
}

//This function implements selection sorting algorithm in decending order
//Parameters: -p_array is the player array
//			  -p_size is the size of player array
void selectionSort(Player* p_array, int p_size)
{
	int i = 0; // index 1
	int j = 0; // index 2
	Player temp; //temporary player

	for ( i = 0; i < p_size - 1; i++)
	{
		for (j = i + 1; j < p_size; j++)
		{
			if (p_array[i].highest_score < p_array[j].highest_score) // sort decending depends on score
			{
				temp = p_array[i];
				p_array[i] = p_array[j];
				p_array[j] = temp;
			}
		}
	}
}