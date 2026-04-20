#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Function declarations
void LoadData(map<string, int>& frequencyMap);
void SaveData(const map<string, int>& frequencyMap);
void SearchItem(const map<string, int>& frequencyMap);
void PrintAll(const map<string, int>& frequencyMap);
void PrintHistogram(const map<string, int>& frequencyMap);
string ToLower(string str);

// Convert string to lowercase for case insensitive comparison
string ToLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main() {
    map<string, int> frequencyMap;
    int choice;

    // Load and save data
    LoadData(frequencyMap);
    SaveData(frequencyMap);

    // Menu loop with full input validation
    while (true) {
        cout << "\n===== Corner Grocer Menu =====\n";
        cout << "1. Search for an item\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        // Handle non numeric input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number (1-4).\n";
            continue;
        }

        switch (choice) {
        case 1:
            SearchItem(frequencyMap);
            break;
        case 2:
            PrintAll(frequencyMap);
            break;
        case 3:
            PrintHistogram(frequencyMap);
            break;
        case 4:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice. Please select 1-4.\n";
        }
    }
}

// Load data from file into map
void LoadData(map<string, int>& frequencyMap) {
    ifstream inFile("CS210_Project_Three_Input_File.txt");
    string item;

    if (!inFile.is_open()) {
        cout << "Error opening input file.\n";
        return;
    }

    while (inFile >> item) {
        frequencyMap[item]++;
    }

    inFile.close();
}

// Save data to frequency.dat
void SaveData(const map<string, int>& frequencyMap) {
    ofstream outFile("frequency.dat");

    for (auto const& pair : frequencyMap) {
        outFile << pair.first << " " << pair.second << endl;
    }

    outFile.close();
}

// Option 1: Search case-insensitive
void SearchItem(const map<string, int>& frequencyMap) {
    string item;
    cout << "Enter item to search: ";
    cin >> item;

    string inputLower = ToLower(item);
    bool found = false;

    for (auto const& pair : frequencyMap) {
        if (ToLower(pair.first) == inputLower) {
            cout << pair.first << " was purchased "
                << pair.second << " times.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << item << " was purchased 0 times.\n";
    }
}

// Option 2: Print all sorted by frequency desc
void PrintAll(const map<string, int>& frequencyMap) {
    vector<pair<string, int>> items(frequencyMap.begin(), frequencyMap.end());

    sort(items.begin(), items.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return b.second < a.second; // descending
        });

    cout << "\nItem Frequencies:\n";
    for (auto const& pair : items) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// Option 3: Histogram sorted
void PrintHistogram(const map<string, int>& frequencyMap) {
    vector<pair<string, int>> items(frequencyMap.begin(), frequencyMap.end());

    sort(items.begin(), items.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return b.second < a.second;
        });

    cout << "\nHistogram:\n";
    for (auto const& pair : items) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}
