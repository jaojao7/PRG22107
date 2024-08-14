#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Player {
public:
    string nickname;
    int points;
    vector<string> cards;

    Player(string name) : nickname(name), points(0) {}
    
    void addPoints(int p) {
        points += p;
    }
    
    void resetPoints() {
        points = 0;
    }
};

class Game {
private:
    vector<string> suspects = {"Colonel Mustard", "Professor Plum", "Reverend Green", "Mrs. Peacock", "Miss Scarlett", "Mrs. White"};
    vector<string> weapons = {"Dagger", "Candlestick", "Revolver", "Rope", "Lead piping", "Spanner"};
    vector<string> rooms = {"Hall", "Lounge", "Library", "Kitchen", "Billiard Room", "Study"};
    map<string, Player> players;
    map<string, string> secretDeck;
    vector<string> playerOrder;
    int numPlayers;

public:
    Game(int numPlayers) : numPlayers(numPlayers) {
        srand(time(0));
    }
    
    void addPlayer(string name) {
        Player player(name);
        players[name] = player;
        playerOrder.push_back(name);
    }
    
    void shuffleAndDistributeCards() {
        vector<string> allCards;
        allCards.insert(allCards.end(), suspects.begin(), suspects.end());
        allCards.insert(allCards.end(), weapons.begin(), weapons.end());
        allCards.insert(allCards.end(), rooms.begin(), rooms.end());

        // Pick secret cards
        secretDeck["Killer"] = suspects[rand() % suspects.size()];
        secretDeck["Weapon"] = weapons[rand() % weapons.size()];
        secretDeck["Room"] = rooms[rand() % rooms.size()];

        allCards.erase(remove(allCards.begin(), allCards.end(), secretDeck["Killer"]), allCards.end());
        allCards.erase(remove(allCards.begin(), allCards.end(), secretDeck["Weapon"]), allCards.end());
        allCards.erase(remove(allCards.begin(), allCards.end(), secretDeck["Room"]), allCards.end());

        random_shuffle(allCards.begin(), allCards.end());

        int count = 0;
        for (auto &player : players) {
            while (player.second.cards.size() < allCards.size() / numPlayers) {
                player.second.cards.push_back(allCards[count++]);
            }
        }
    }

    void startGame() {
        int currentPlayerIndex = 0;
        bool gameWon = false;

        while (!gameWon) {
            string currentPlayer = playerOrder[currentPlayerIndex];
            gameWon = playerTurn(players[currentPlayer]);
            currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
        }

        cout << "Thanks for playing!" << endl;
    }

    bool playerTurn(Player &player) {
        cout << "---------------------------------------------------" << endl;
        cout << player.nickname << "'s turn. Roll the dice (press enter to roll)...";
        cin.ignore();
        int dice = rand() % 6 + 1;
        cout << "You rolled: " << dice << endl;
        player.addPoints(dice);
        if (player.points >= 8) {
            cout << "You have enough points to enter a room. Enter a room number: " << endl;
            for (int i = 0; i < rooms.size(); ++i) {
                cout << i + 1 << ") " << rooms[i] << endl;
            }
            int roomChoice;
            cin >> roomChoice;
            player.resetPoints();

            cout << "Choose suspect and weapon (separated by space):" << endl;
            for (int i = 0; i < suspects.size(); ++i) {
                cout << i + 1 << ") " << suspects[i] << endl;
            }
            for (int i = 0; i < weapons.size(); ++i) {
                cout << i + 1 << ") " << weapons[i] << endl;
            }
            int suspectChoice, weaponChoice;
            cin >> suspectChoice >> weaponChoice;

            string chosenSuspect = suspects[suspectChoice - 1];
            string chosenWeapon = weapons[weaponChoice - 1];
            string chosenRoom = rooms[roomChoice - 1];

            cout << "Suggestion: Killer: " << chosenSuspect << ", Weapon: " << chosenWeapon << ", Room: " << chosenRoom << endl;

            if (secretDeck["Killer"] == chosenSuspect && secretDeck["Weapon"] == chosenWeapon && secretDeck["Room"] == chosenRoom) {
                cout << player.nickname << " WON!" << endl;
                return true;
            } else {
                cout << "Wrong accusation. " << player.nickname << " will no longer make accusations." << endl;
                playerOrder.erase(remove(playerOrder.begin(), playerOrder.end(), player.nickname), playerOrder.end());
                --numPlayers;
            }
        }
        return false;
    }
};

int main() {
    int numPlayers;
    cout << "Enter the number of players (2-6): ";
    cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 6) {
        cout << "Invalid number of players." << endl;
        return 1;
    }

    Game game(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        cout << "Enter nickname for player " << i + 1 << ": ";
        cin >> playerName;
        game.addPlayer(playerName);
    }

    game.shuffleAndDistributeCards();
    game.startGame();

    return 0;
}
