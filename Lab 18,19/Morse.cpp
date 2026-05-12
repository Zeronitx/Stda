#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

map<char, string> morseCode = {
    {'A',".-"},  {'B',"-..."}, {'C',"-.-."}, {'D',"-.."}, {'E',"."},
    {'F',"..-."}, {'G',"--."}, {'H',"...."}, {'I',".."},  {'J',".---"},
    {'K',"-.-"},  {'L',".-.."}, {'M',"--"},  {'N',"-."},  {'O',"---"},
    {'P',".--."}, {'Q',"--.-"}, {'R',".-."}, {'S',"..."}, {'T',"-"},
    {'U',"..-"},  {'V',"...-"}, {'W',".--"}, {'X',"-..-"}, {'Y',"-.--"},
    {'Z',"--.."},
    {'0',"-----"},{'1',".----"},{'2',"..---"},{'3',"...--"},
    {'4',"....-"},{'5',"....."},{'6',"-...."},{'7',"--..."},
    {'8',"---.."},{'9',"----."}
};

map<string, char> reverseMorse;

void buildReverseMorse() {
    for (auto& p : morseCode) reverseMorse[p.second] = p.first;
}

string textToMorse(const string& text) {
    string result = "";
    for (char c : text) {
        c = toupper(c);
        if (morseCode.count(c)) result += morseCode[c] + " ";
        else if (c == ' ') result += "/ ";
    }
    return result;
}

string morseToText(const string& morse) {
    string result = "", token = "";
    for (int i = 0; i <= (int)morse.size(); i++) {
        if (i == (int)morse.size() || morse[i] == ' ') {
            if (token == "/") result += ' ';
            else if (reverseMorse.count(token)) result += reverseMorse[token];
            token = "";
        } else token += morse[i];
    }
    return result;
}

void playMorse(const string& morse) {
    cout << "Sound (. = TI, - = TA): ";
    for (char c : morse) {
        if (c == '.') cout << "TI ";
        else if (c == '-') cout << "TA ";
        else if (c == '/') cout << "| ";
        else cout << "  ";
    }
    cout << "\n";
}

int main() {
    buildReverseMorse();

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

    cout << "1 - Encode to Morse\n2 - Decode from Morse\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        string encoded = textToMorse(text);
        cout << "Morse: " << encoded << "\n";
        playMorse(encoded);
        ofstream fout("morse_output.txt");
        fout << encoded;
        cout << "Saved to morse_output.txt\n";
    } else {
        string decoded = morseToText(text);
        cout << "Decoded: " << decoded << "\n";
        ofstream fout("morse_decoded.txt");
        fout << decoded;
        cout << "Saved to morse_decoded.txt\n";
    }

    return 0;
}
