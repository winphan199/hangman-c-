# hangman-cplusplus-
This is console hangman game.

1. What is Hang Man?
- Hang Man is a game on console platform.
- Hang Man is a word-guessing game, which requires player to type the right letters for
unknown word.
- When a player guesses the right word, he/she won. But, the player will lose if he/she
guesses wrong 5 times and the hang man will appear when he/she guesses wrong.
- If the player guesses multiple correct words in a row, his/her score will add up until he/she
guesses the wrong word or quit the game.
2. User interface
There are 5 options for a player to choose when the game starts:
- [1] New player if he/she wants to play as a new player.
- [2] Continue if he/she wants to play with previous player’s name.
- [3] Top scores if he/she wants to view to ranking table of top 10 players with highest scores.
- [4] Exit if he/she wants to stop playing Hang Man.
- [-1] This is a secret option, which is only known by developer. This option helps game master
to input new keywords without manipulating the keyword file.
3. How Hang Man implements
- Firstly, the function preProcessForHangMan() is called to load data of players and
keywords from saved file.
- Secondly, the function outputMenu() will be called to print out the menu and asks
players to type their choice.
o This function will loop until the player wants to exit the game.
- Thirdly, when a player type options [1] or [2] the function GamePlay() will be
called to proceed the game.
- Fourthly, when a player loses or stop playing, the function addPlayerToArray()
will be called add player’s data to player array.
- Fifthly, when a player type option [3], the function displayTopScores() will be
called to display the ranking table.
- Sixthly, when a player chooses [4], the game stops.
- Finally, when the game stops, the functions ExportPlayerScore() and
ExportKeyWord() will be called to export newest data to files.
o ExportKeyWord() is for in case the developer input new keywords.
- Especially, when a player type [-1] the player will be able to input new
keywords.
