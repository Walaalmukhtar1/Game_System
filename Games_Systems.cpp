#include <iostream> 
#include <fstream> 
#include <string> 
#include <limits> 
#include <set>

using namespace std; 
 
struct Player { 
    string name; 
    int id; 
    int age; 
    int NumofGames; 
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
        } 
        else { 
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
        } 
        else { 
            break; 
        } 
    } 
} 
 
void getIdInput(int& input, const string& prompt, set<int>& existingIds) { 
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
        } 
        else { 
            input = stoi(idInput); 
            if (existingIds.find(input) != existingIds.end()) {
                cout << "Invalid entry, the ID already exists." << endl;
            } else {
                existingIds.insert(input);
                break;
            }
        } 
    } 
} 
 
int main() { 
    int n; 
    set<int> existingIds;
 
    cout << "Enter the number of players: "; 
    cin >> n; 
    cin.ignore();  // Clear the newline character from the input buffer
 
    Player* players = new Player[n]; 
 
    for (int i = 0; i < n; ++i) { 
        cout << "Enter the details for player " << i + 1 << ":\n"; 
        getStringInput(players[i].name, "Name: "); 
        getIdInput(players[i].id, "ID: ", existingIds); 
        getAgeInput(players[i].age, "Age: "); 
        getInput(players[i].NumofGames, "Number of Games: "); 
        cout << endl; 
    } 

    Game* games = new Game[n]; 

    for (int i = 0; i < n; ++i) { 
        cout << "For player " << i + 1 << " (ID: " << players[i].id << "):" << endl;
        for (int j = 0; j < players[i].NumofGames; ++j) {
            cout << "Enter the name for game " << j + 1 << ": "; 
            getline(cin, games[j].gameName); 
        }
    } 
 
    Score* scores = new Score[n]; 
 
    for (int i = 0; i < n; ++i) { 
        cout << "For player " << i + 1 << " (ID: " << players[i].id << "):" << endl;
        for (int j = 0; j < players[i].NumofGames; ++j) {
            cout << "Game Name: " << games[j].gameName << endl;
            getInput(scores[i].score, "Score: "); 
            cout << endl; 
        }
    } 
 
    ofstream PlayersFile("players.txt"); 
    if (PlayersFile.is_open()) { 
        for (int i = 0; i < n; ++i) { 
            PlayersFile << players[i].name << " " << players[i].id << " " 
                << players[i].age << " " << players[i].NumofGames << "\n"; 
        } 
        PlayersFile.close(); 
    } 
    else { 
        cout << "Unable to open file for writing player details.\n"; 
    } 
 
    ofstream gameFile("games.txt"); 
    if (gameFile.is_open()) { 
        for (int i = 0; i < n; ++i) { 
            gameFile << games[i].gameName << "\n"; 
        } 
        gameFile.close(); 
    } 
    else { 
        cout << "Unable to open file for writing game details.\n"; 
    } 
 
    ofstream ScoresFile("scores.txt"); 
    if (ScoresFile.is_open()) { 
        for (int i = 0; i < n; ++i) { 
            ScoresFile << scores[i].gameName << " " << scores[i].score << "\n"; 
        } 
        ScoresFile.close(); 
    } 
    else { 
        cout << "Unable to open file for writing score details.\n"; 
    } 
 
    delete[] players; 
    delete[] games; 
    delete[] scores; 
 
    return 0; 
}
