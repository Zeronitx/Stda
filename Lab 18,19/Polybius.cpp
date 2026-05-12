#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const char POLYBIUS[5][5] = {
    {'A','B','C','D','E'},
    {'F','G','H','I','K'},
    {'L','M','N','O','P'},
    {'Q','R','S','T','U'},
    {'V','W','X','Y','Z'}
};

void printPolybiusSquare() {
    cout << "\nPolybius Square:\n  1 2 3 4 5\n";
    for (int i = 0; i < 5; i++) {
        cout << (i + 1) << " ";
        for (int j = 0; j < 5; j++) cout << POLYBIUS[i][j] << " ";
        cout << "\n";
    }
}

string polybiusEncrypt(const string& text) {
    string result = "";
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (POLYBIUS[i][j] == c)
                    result += to_string(i + 1) + to_string(j + 1) + " ";
    }
    return result;
}

string polybiusDecrypt(const string& text) {
    string result = "";
    vector<string> pairs;
    string token = "";
    for (char c : text) {
        if (c == ' ') {
            if (!token.empty()) { pairs.push_back(token); token = ""; }
        } else token += c;
    }
    if (!token.empty()) pairs.push_back(token);
    for (const string& p : pairs) {
        if (p.size() == 2) {
            int r = p[0] - '1', col = p[1] - '1';
            if (r >= 0 && r < 5 && col >= 0 && col < 5)
                result += POLYBIUS[r][col];
        }
    }
    return result;
}

int main() {
    printPolybiusSquare();

    string text;
    int choice;

    cout << "1 - Enter text\n2 - Read from file\nChoice: ";
    cin >> choice; cin.ignore();

    if (choice == 1) {
        cout << "Enter text: ";
        getline(cin, text);
    } else {
        string filename;
        cout << "Filename: ";
        cin >> filename;
        ifstream fin(filename);
        getline(fin, text);
    }

    cout << "1 - Encrypt\n2 - Decrypt\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        string enc = polybiusEncrypt(text);
        cout << "Original:  " << text << "\n";
        cout << "Encrypted: " << enc << "\n";
    } else {
        cout << "Decrypted: " << polybiusDecrypt(text) << "\n";
    }

    return 0;
}

