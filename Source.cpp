#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Class to represent a bowler
class Bowler {
    //private member variable to store bowlers info
private:
    string name;
    string team;
    int gamesPlayed;
    int strikes; // knocking down all pins in the first attempt
    int spares;  // knocking down all pins in the second attempt
    int totalPins; // total pins knocked down
    int age;

public:
    // Constructor to create a bowler object using provided info
    Bowler(string n, string t, int gp, int s, int sp, int tp, int a)
    {

        name = n;
        team = t;
        gamesPlayed = gp;
        strikes = s;
        spares = sp;
        totalPins = tp;
        age = a;

    }

    // Function to print bowler statistics
    void printStats() const {
        cout << left << setw(15) << name
            << setw(15) << team
            << setw(15) << gamesPlayed
            << setw(15) << strikes
            << setw(15) << spares
            << setw(15) << totalPins
            << setw(10) << age << endl;
    }

    // Function to get the bowler's name
    string getName() const {
        return name;
    }

    // Function to get the bowler's team
    string getTeam() const { 
        return team; 
    }

    // Function to update bowler statistics
    void updateStats(int a, int gp, int s, int sp, int tp) {
        gamesPlayed = gp;
        strikes = s;
        spares = sp;
        totalPins = tp;
        age = a;
    }

    // Function to export bowler data
    string exportData() const {
        ostringstream outputStringStream;

        outputStringStream << left << setw(15) << name
            << setw(15) << team
            << setw(8) << age
            << setw(15) << gamesPlayed
            << setw(8) << strikes
            << setw(8) << spares
            << setw(8) << totalPins << "\n";
        return outputStringStream.str();
    }
};

// Class to manage bowlers stats
class BowlingStats {
private:
    vector<Bowler> bowlers;

public:
    void readBowlersFromFile(const string& filename);//function to real all bowlers info
    void printAllBowlers() const;//functions to print stats for all bowlers
    void printBowlerStats() const;//function to print a single bowlers stat
    void printTeamStats() const;//function to print stats for a single team
    void updateBowlerStats();//function to update a bowlers stats
    void insertNewBowler();//function to add a new bowler
    void exportDataToFile(const string& filename) const;//data to export bowler data to file
};

//reading bowlers info from file
void BowlingStats::readBowlersFromFile(const string& filename) {
    ifstream file(filename);
    string name, team;
    int number, gamesPlayed, strikes, spares, totalPins, age;

    while (file >> number>> name >> team >> age >> gamesPlayed >> strikes >> spares >> totalPins) {
        bowlers.emplace_back(name, team, gamesPlayed, strikes, spares, totalPins, age);
    }
    file.close();
}

void BowlingStats::printAllBowlers() const {
    cout << left<<setw(6)<<"Number"
        << setw(15) << "Name"
        << setw(15) << "Team"
        << setw(15) << "Games"
        << setw(15) << "Strikes"
        << setw(15) << "Spares"
        << setw(15) << "Total Pins"
        << setw(10) << "Age" << endl;

    for (size_t i = 0; i < bowlers.size(); i++) {
        cout << setw(5) << (i + 1);
        bowlers[i].printStats();//prints the bowlers stats based on the bowlers number
    }
}

void BowlingStats::printBowlerStats() const {
    int bowlerNumber;
    printAllBowlers();
    cout << "Enter the number of the bowler you want to select: ";
    cin >> bowlerNumber;

    if (bowlerNumber > 0 && bowlerNumber <= bowlers.size()) {

        cout << left << setw(15) << "Name"
            << setw(15) << "Team"
            << setw(15) << "Games"
            << setw(15) << "Strikes"
            << setw(15) << "Spares"
            << setw(15) << "Total Pins"
            << setw(10) << "Age" << endl;

        bowlers[bowlerNumber - 1].printStats();// accesses bowlers number from index
    }
    else {
        cout << "The bowler number that chose was not found.\n";
    }
}

void BowlingStats::printTeamStats() const {
    string team;
    cout << "Enter team name: ";
    cin >> team;

    cout << left << setw(15) << "Name"
        << setw(15) << "Team"
        << setw(15) << "Games"
        << setw(15) << "Strikes"
        << setw(15) << "Spares"
        << setw(15) << "Total Pins"
        << setw(10) << "Age" << endl;

    for (const auto& bowler : bowlers) {
        if (bowler.getTeam() == team) {
            bowler.printStats();
        }
    }
}

void BowlingStats::updateBowlerStats() {
    

    // Getting the number chosen by the user
    int num;
    cout << "Enter the bowler's number to update stats: ";
    cin >> num;

    // Validate the number
    if (num < 1 || num > bowlers.size()) {
        cout << "Invalid number, select another one." << endl;
        return; // Exit early if the number is invalid
    }

    // Reference to the selected bowler
    auto& bowler = bowlers[num - 1];

    // Collecting new stats
    int gamesPlayed, strikes, spares, totalPins, age;

    cout << "Games played: ";
    cin >> gamesPlayed;
    cout << "Strikes: ";
    cin >> strikes;
    cout << "Spares: ";
    cin >> spares;
    cout << "Total pins: ";
    cin >> totalPins;
    cout << "Age: ";
    cin >> age;

    // Update the bowler's stats
    bowler.updateStats(age, gamesPlayed, strikes, spares, totalPins);
    cout << "Bowler stats updated.\n";
}


//adds a new bowler to the game
void BowlingStats::insertNewBowler() {
    string name, team;
    int gamesPlayed, strikes, spares, totalPins, age;

    cout << "Enter the new bowler's statistics " << endl;
    cout << "Enter bowler's name: ";
    cin >> name;
    cout << "Enter team name: ";
    cin >> team;
    cout << "Games played: ";
    cin >> gamesPlayed;
    cout << "Strikes: ";
    cin >> strikes;
    cout << "Spares: ";
    cin >> spares;
    cout << "Total pins: ";
    cin >> totalPins;

    while (true) {
        cout << "Age: ";
        cin >> age;

        if (cin.fail() || age < 0) {
            cout << "Invalid input for age, please try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            break;
        }
    }

    // Checking age is greater than 0
    if (age < 0 || gamesPlayed < 0 || strikes < 0 || spares < 0 || totalPins < 0) {
        cout << "Negative values are not accepted." << endl;
        return;
    }

    bowlers.emplace_back(name, team, gamesPlayed, strikes, spares, totalPins, age);
    cout << "A new bowler is added.\n";
}

void BowlingStats::exportDataToFile(const string& filename) const {
    ofstream file(filename);

    // Print the headers
    file << left << setw(15) << "Name"
        << setw(15) << "Team"
        << setw(8) << "Age"
        << setw(15) << "Games Played"
        << setw(8) << "Strikes"
        << setw(8) << "Spares"
        << setw(8) << "Total Pins" << endl;

    //using equal sign to make a table chart for bowlers
    file << string(75, '=') << endl;

    for (const auto& bowler : bowlers) {
        file << bowler.exportData();
        file << string(75, '-') << endl;
    }
    file.close();
    cout << "Data exported to " << filename << ".\n";
};

int main() {
    BowlingStats bowlingStats;
    // Load bowlers data from a file
    bowlingStats.readBowlersFromFile("Bowlers.txt");

    int choice;

    cout << "Welcome to the Bowlers information system! Please select from the following menu below:" << endl;

    do {
        //options from the menu
        cout << "\nMenu:\n";
        cout << "1. Print all bowlers and statistics\n";
        cout << "2. Print statistics for a specific bowler\n";
        cout << "3. Print all data for a specific team\n";
        cout << "4. Update data for a specific bowler\n";
        cout << "5. Insert a new bowler and their statistics\n";
        cout << "6. Export data to a file\n";
        cout << "7. Exit\n"; 
        cout << "Enter your choice: ";
        cin >> choice;


        
        switch (choice) {
        case 1:
            bowlingStats.printAllBowlers();//printing stats for all bowlers
            break;
        case 2:
            bowlingStats.printBowlerStats();//printing stats for a single bowler
            break;
        case 3:
            bowlingStats.printTeamStats();//prinitng stat for a team
            break;
        case 4:
            bowlingStats.updateBowlerStats();//updating bowlers stats
            break;
        case 5:
            bowlingStats.insertNewBowler();//adding a new bowler
            break;
        case 6: {
            string filename;
            cout << "Enter file name to export data: ";
            cin >> filename;
            bowlingStats.exportDataToFile(filename);//exports bowler data to a file
            break;
        }
        case 7:  
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);  //exits

    return 0;
}