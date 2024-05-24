#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

struct Player {
    string name;
    int id;
    int age;
    int numOfGames;
};

struct Game {
    string gameName;
};

struct Score {
    int playerId;
    string gameName;
    int score;
};

void getInput(int& input, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void getAgeInput(int& input, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input < 1 || input > 99) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an age between 1 and 99." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void getStringInput(string& input, const string& prompt) {
    while (true) {
        bool valid = true;
        cout << prompt;
        getline(cin, input);
        for (char c : input) {
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid input. Please enter letters only." << endl;
        } else {
            break;
        }
    }
}

int getIdInput(const string& prompt, set<int>& existingIds) {
    int input;
    while (true) {
        string idInput;
        bool valid = true;
        cout << prompt;
        getline(cin, idInput);
        if (idInput.length() != 10) {
            cout << "Invalid input. Please enter a 10-digit number." << endl;
            continue;
        }
        for (char c : idInput) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid input. Please enter a 10-digit number." << endl;
        } else {
            input = stoi(idInput);
            if (existingIds.find(input) != existingIds.end()) {
                cout << "Invalid entry, the ID already exists." << endl;
            } else {
                existingIds.insert(input);
                break;
            }
        }
    }
    return input;
}

void addNewItem(Player*& players, int& numPlayers, Game*& games, int& numGames, Score*& scores, int& totalScores, set<int>& existingIds) {
    // Add a new player
    Player newPlayer;
    cout << "Enter the details for the new player:\n";
    getStringInput(newPlayer.name, "Name: ");
    newPlayer.id = getIdInput("ID: ", existingIds);
    getAgeInput(newPlayer.age, "Age: ");
    getInput(newPlayer.numOfGames, "Number of Games: ");

    // Update players array
    Player* newPlayers = new Player[numPlayers + 1];
    for (int i = 0; i < numPlayers; ++i) {
        newPlayers[i] = players[i];
    }
    newPlayers[numPlayers] = newPlayer;
    delete[] players;
    players = newPlayers;
    numPlayers++;

    // Add games and scores for the new player
    Game* newGames = new Game[numGames + newPlayer.numOfGames];
    for (int i = 0; i < numGames; ++i) {
        newGames[i] = games[i];
    }

    Score* newScores = new Score[totalScores + newPlayer.numOfGames];
    for (int i = 0; i < totalScores; ++i) {
        newScores[i] = scores[i];
    }

    for (int i = 0; i < newPlayer.numOfGames; ++i) {
        cout << "Enter the name for game " << i + 1 << ": ";
        getline(cin, newGames[numGames + i].gameName);

        newScores[totalScores + i].playerId = newPlayer.id;
        newScores[totalScores + i].gameName = newGames[numGames + i].gameName;
        getInput(newScores[totalScores + i].score, "Score: ");
    }

    delete[] games;
    delete[] scores;
    games = newGames;
    scores = newScores;
    numGames += newPlayer.numOfGames;
    totalScores += newPlayer.numOfGames;

    cout << "New player and their games/scores added successfully." << endl;
}

void searchItem(Game* games, int numGames) {
    string gameName;
    cout << "Enter the name of the game to search: ";
    getline(cin, gameName);
    for (int i = 0; i < numGames; i++) {
        if (games[i].gameName == gameName) {
            cout << "Game found: " << games[i].gameName << endl;
            return;
        }
    }
    cout << "Game not found." << endl;
}

void updateRecord(Game* games, int numGames) {
    string oldGameName, newGameName;
    cout << "Enter the name of the game to update: ";
    getline(cin, oldGameName);
    for (int i = 0; i < numGames; i++) {
        if (games[i].gameName == oldGameName) {
            cout << "Enter the new name of the game: ";
            getline(cin, newGameName);
            games[i].gameName = newGameName;
            cout << "Game updated successfully." << endl;
            return;
        }
    }
    cout << "Game not found." << endl;
}

void deleteItem(Game*& games, int& numGames) {
    string gameName;
    cout << "Enter the name of the game to delete: ";
    getline(cin, gameName);
    for (int i = 0; i < numGames; i++) {
        if (games[i].gameName == gameName) {
            for (int j = i; j < numGames - 1; j++) {
                games[j] = games[j + 1];
            }
            numGames--;
            Game* newGames = new Game[numGames];
            for (int j = 0; j < numGames; j++) {
                newGames[j] = games[j];
            }
            delete[] games;
            games = newGames;
            cout << "Game deleted successfully." << endl;
            return;
        }
    }
    cout << "Game not found." << endl;
}

void sortItems(Game* games, int numGames) {
    sort(games, games + numGames, [](const Game& a, const Game& b) {
        return a.gameName < b.gameName;
    });
    cout << "Games sorted successfully." << endl;
}

void displayItems(const Game* games, int numGames) {
    if (numGames == 0) {
        cout << "No games to display." << endl;
    } else {
        cout << "List of games:" << endl;
        for (int i = 0; i < numGames; i++) {
            cout << games[i].gameName << endl;
        }
    }
}

void gameSystem(Player*& players, int& numPlayers, Game*& games, int& numGames, Score*& scores, int& totalScores, set<int>& existingIds) {
    int choice;
    bool exit = false;

    while (!exit) {
        cout << "Choose a service:\n";
        cout << "1. Add new item\n";
        cout << "2. Search for a specific item\n";
        cout << "3. Update existing record\n";
        cout << "4. Delete\n";
        cout << "5. Sort\n";
        cout << "6. Display\n";
        cout << "7. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore any leftover newline character in the buffer

        switch (choice) {
            case 1:
                addNewItem(players, numPlayers, games, numGames, scores, totalScores, existingIds);
                break;
            case 2:
                searchItem(games, numGames);
                break;
            case 3:
                updateRecord(games, numGames);
                break;
            case 4:
                deleteItem(games, numGames);
                break;
            case 5:
                sortItems(games, numGames);
                break;
            case 6:
                displayItems(games, numGames);
                break;
            case 7:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    int n;
    int totalScores=0;
    set<int> existingIds;

    cout << "Enter the number of players: ";
    cin >> n;
    cin.ignore();

    Player* players = new Player[n];

    for (int i = 0; i < n; ++i) {
        cout << "Enter the details for player " << i + 1 << ":\n";
        getStringInput(players[i].name, "Name: ");
        players[i].id = getIdInput("ID: ", existingIds);
        getAgeInput(players[i].age, "Age: ");
        getInput(players[i].numOfGames, "Number of Games: ");
        cout << endl;
    }

    int totalGames = 0;
    for (int i = 0; i < n; ++i) {
        totalGames += players[i].numOfGames;
    }

    Game* games = new Game[totalGames];
    int gameIndex = 0;
    for (int i = 0; i < n; ++i) {
        cout << "For player " << i + 1 << " (ID: " << players[i].id << "):" << endl;
        for (int j = 0; j < players[i].numOfGames; ++j) {
            cout << "Enter the name for game " << j + 1 << ": ";
            getline(cin, games[gameIndex].gameName);
            gameIndex++;
        }
    }

    Score* scores = new Score[totalGames];
    gameIndex = 0;
    for (int i = 0; i < n; ++i) {
        cout << "For player " << i + 1 << " (ID: " << players[i].id << "):" << endl;
        for (int j = 0; j < players[i].numOfGames; ++j) {
            scores[gameIndex].playerId = players[i].id;
            scores[gameIndex].gameName = games[gameIndex].gameName;
            getInput(scores[gameIndex].score, "Score: ");
            gameIndex++;
        }
    }

    ofstream playersFile("players.txt");
    if (playersFile.is_open()) {
        for (int i = 0; i < n; ++i) {
            playersFile << players[i].name << " " << players[i].id << " "
                        << players[i].age << " " << players[i].numOfGames << "\n";
        }
        playersFile.close();
    } else {
        cout << "Unable to open file for writing player details.\n";
    }

    ofstream gameFile("games.txt");
    if (gameFile.is_open()) {
        for (int i = 0; i < totalGames; ++i) {
            gameFile << games[i].gameName << "\n";
        }
        gameFile.close();
    } else {
        cout << "Unable to open file for writing game details.\n";
    }

    ofstream scoresFile("scores.txt");
    if (scoresFile.is_open()) {
        for (int i = 0; i < totalGames; ++i) {
            scoresFile << scores[i].playerId << " " << scores[i].gameName << " " << scores[i].score << "\n";
        }
        scoresFile.close();
    } else {
        cout << "Unable to open file for writing score details.\n";
    }

    gameSystem(players, n, games, totalGames, scores, totalScores, existingIds);

    delete[] players;
    delete[] games;
    delete[] scores;

    return 0;
}
