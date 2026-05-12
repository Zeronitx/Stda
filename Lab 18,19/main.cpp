#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const string TEXT = "Abandon hope all ye who enter here";

string caesarEncrypt(const string& text, int shift) {
    string result = text;
    shift = ((shift % 26) + 26) % 26;
    for (char& c : result) {
        if (isupper(c)) c = (c - 'A' + shift) % 26 + 'A';
        else if (islower(c)) c = (c - 'a' + shift) % 26 + 'a';
    }
    return result;
}

string caesarDecrypt(const string& text, int shift) {
    return caesarEncrypt(text, -shift);
}

int frequencyAnalysis(const string& text) {
    int freq[26] = {};
    for (char c : text)
        if (isalpha(c)) freq[tolower(c) - 'a']++;
    int maxIdx = 0;
    for (int i = 1; i < 26; i++)
        if (freq[i] > freq[maxIdx]) maxIdx = i;
    return (maxIdx - ('e' - 'a') + 26) % 26;
}

void task1() {
    cout << "\n--- Task 1: Caesar Cipher ---\n";
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
    int shift;
    cout << "Enter shift: ";
    cin >> shift;
    cout << "1 - Encrypt\n2 - Decrypt (reverse)\n3 - Decrypt (frequency)\nChoice: ";
    cin >> choice;
    string output;
    if (choice == 1) {
        output = caesarEncrypt(text, shift);
        cout << "Encrypted: " << output << "\n";
    } else if (choice == 2) {
        output = caesarDecrypt(text, shift);
        cout << "Decrypted: " << output << "\n";
    } else {
        int guessed = frequencyAnalysis(text);
        cout << "Guessed shift: " << guessed << "\n";
        output = caesarDecrypt(text, guessed);
        cout << "Decrypted: " << output << "\n";
        string keyword;
        cout << "Enter keyword to verify: ";
        cin >> keyword;
        if (output.find(keyword) != string::npos)
            cout << "Keyword found! Correct.\n";
        else
            cout << "Keyword not found.\n";
    }
}

string buildSubstAlphabet(const string& key) {
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string subst = "", used = "";
    for (char c : key) {
        c = toupper(c);
        if (isalpha(c) && used.find(c) == string::npos) {
            subst += c; used += c;
        }
    }
    for (char c : alpha)
        if (used.find(c) == string::npos) subst += c;
    return subst;
}

string substEncrypt(const string& text, const string& subst) {
    string result = text;
    for (char& c : result) {
        if (isupper(c)) c = subst[c - 'A'];
        else if (islower(c)) c = tolower(subst[c - 'a']);
    }
    return result;
}

string substDecrypt(const string& text, const string& subst) {
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = text;
    for (char& c : result) {
        if (isupper(c)) {
            int pos = subst.find(c);
            if (pos != (int)string::npos) c = alpha[pos];
        } else if (islower(c)) {
            int pos = subst.find(toupper(c));
            if (pos != (int)string::npos) c = tolower(alpha[pos]);
        }
    }
    return result;
}

void task2() {
    cout << "\n--- Task 2: Simple Substitution ---\n";
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
    string key;
    cout << "Enter key: ";
    cin >> key;
    string subst = buildSubstAlphabet(key);
    cout << "Substitution alphabet: " << subst << "\n";
    cout << "1 - Encrypt\n2 - Decrypt\nChoice: ";
    cin >> choice;
    if (choice == 1)
        cout << "Encrypted: " << substEncrypt(text, subst) << "\n";
    else
        cout << "Decrypted: " << substDecrypt(text, subst) << "\n";
}

void printVigenereTable() {
    cout << "\nVigenere Table (first 10 rows):\n   ";
    for (int i = 0; i < 10; i++) cout << (char)('A' + i) << " ";
    cout << "\n";
    for (int i = 0; i < 10; i++) {
        cout << (char)('A' + i) << ": ";
        for (int j = 0; j < 10; j++)
            cout << (char)(('A' + (i + j) % 26)) << " ";
        cout << "\n";
    }
}

string vigenereEncrypt(const string& text, const string& key) {
    string result = text;
    int ki = 0;
    for (char& c : result) {
        if (isalpha(c)) {
            int shift = toupper(key[ki % key.size()]) - 'A';
            if (isupper(c)) c = (c - 'A' + shift) % 26 + 'A';
            else c = (c - 'a' + shift) % 26 + 'a';
            ki++;
        }
    }
    return result;
}

string vigenereDecrypt(const string& text, const string& key) {
    string result = text;
    int ki = 0;
    for (char& c : result) {
        if (isalpha(c)) {
            int shift = toupper(key[ki % key.size()]) - 'A';
            if (isupper(c)) c = (c - 'A' - shift + 26) % 26 + 'A';
            else c = (c - 'a' - shift + 26) % 26 + 'a';
            ki++;
        }
    }
    return result;
}

void task3() {
    cout << "\n--- Task 3: Vigenere Cipher ---\n";
    string text, key;
    cin.ignore();
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter key: ";
    cin >> key;
    printVigenereTable();
    int choice;
    cout << "1 - Encrypt\n2 - Decrypt\nChoice: ";
    cin >> choice;
    if (choice == 1)
        cout << "Encrypted: " << vigenereEncrypt(text, key) << "\n";
    else
        cout << "Decrypted: " << vigenereDecrypt(text, key) << "\n";
}

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

void task4() {
    cout << "\n--- Task 4: Polybius Square ---\n";
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
}

char playfairMatrix[5][5];

void buildPlayfairMatrix(const string& key) {
    bool used[26] = {};
    used['J' - 'A'] = true;
    string letters = "";
    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c) && !used[c - 'A']) {
            letters += c;
            used[c - 'A'] = true;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++)
        if (!used[c - 'A']) letters += c;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            playfairMatrix[i][j] = letters[i * 5 + j];
}

void printPlayfairMatrix() {
    cout << "\nPlayfair Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << playfairMatrix[i][j] << " ";
        cout << "\n";
    }
}

pair<int,int> findInMatrix(char c) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (playfairMatrix[i][j] == c) return {i, j};
    return {-1, -1};
}

string preparePlayfair(const string& text) {
    string t = "";
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c)) t += c;
    }
    string result = "";
    int i = 0;
    while (i < (int)t.size()) {
        result += t[i];
        if (i + 1 < (int)t.size()) {
            if (t[i] == t[i + 1]) { result += 'X'; i++; }
            else { result += t[i + 1]; i += 2; }
        } else { result += 'X'; i++; }
    }
    return result;
}

string playfairEncrypt(const string& text) {
    string prepared = preparePlayfair(text);
    string result = "";
    for (int i = 0; i < (int)prepared.size(); i += 2) {
        auto [r1, c1] = findInMatrix(prepared[i]);
        auto [r2, c2] = findInMatrix(prepared[i + 1]);
        if (r1 == r2) {
            result += playfairMatrix[r1][(c1 + 1) % 5];
            result += playfairMatrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            result += playfairMatrix[(r1 + 1) % 5][c1];
            result += playfairMatrix[(r2 + 1) % 5][c2];
        } else {
            result += playfairMatrix[r1][c2];
            result += playfairMatrix[r2][c1];
        }
    }
    return result;
}

string playfairDecrypt(const string& text) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i += 2) {
        auto [r1, c1] = findInMatrix(text[i]);
        auto [r2, c2] = findInMatrix(text[i + 1]);
        if (r1 == r2) {
            result += playfairMatrix[r1][(c1 + 4) % 5];
            result += playfairMatrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            result += playfairMatrix[(r1 + 4) % 5][c1];
            result += playfairMatrix[(r2 + 4) % 5][c2];
        } else {
            result += playfairMatrix[r1][c2];
            result += playfairMatrix[r2][c1];
        }
    }
    return result;
}

void task5() {
    cout << "\n--- Task 5: Playfair Cipher ---\n";
    string text, key;
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
    cout << "Enter key: ";
    cin >> key;
    buildPlayfairMatrix(key);
    printPlayfairMatrix();
    cout << "1 - Encrypt\n2 - Decrypt\nChoice: ";
    cin >> choice;
    if (choice == 1)
        cout << "Encrypted: " << playfairEncrypt(text) << "\n";
    else
        cout << "Decrypted: " << playfairDecrypt(text) << "\n";
}

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

void task6() {
    cout << "\n--- Task 6: Morse Code ---\n";
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
}

void runDemo() {
    cout << "\n========================================\n";
    cout << "DEMO: \"" << TEXT << "\"\n";
    cout << "========================================\n";

    cout << "\n[1] Caesar (shift=3):\n";
    string c1 = caesarEncrypt(TEXT, 3);
    cout << "  Encrypted: " << c1 << "\n";
    cout << "  Decrypted: " << caesarDecrypt(c1, 3) << "\n";

    cout << "\n[2] Substitution (key=DANTE):\n";
    string subst = buildSubstAlphabet("DANTE");
    string c2 = substEncrypt(TEXT, subst);
    cout << "  Alphabet:  " << subst << "\n";
    cout << "  Encrypted: " << c2 << "\n";
    cout << "  Decrypted: " << substDecrypt(c2, subst) << "\n";

    cout << "\n[3] Vigenere (key=HELL):\n";
    string c3 = vigenereEncrypt(TEXT, "HELL");
    cout << "  Encrypted: " << c3 << "\n";
    cout << "  Decrypted: " << vigenereDecrypt(c3, "HELL") << "\n";

    cout << "\n[4] Polybius Square:\n";
    printPolybiusSquare();
    string c4 = polybiusEncrypt(TEXT);
    cout << "  Encrypted: " << c4 << "\n";
    cout << "  Decrypted: " << polybiusDecrypt(c4) << "\n";

    cout << "\n[5] Playfair (key=DANTE):\n";
    buildPlayfairMatrix("DANTE");
    printPlayfairMatrix();
    string c5 = playfairEncrypt(TEXT);
    cout << "  Encrypted: " << c5 << "\n";
    cout << "  Decrypted: " << playfairDecrypt(c5) << "\n";

    cout << "\n[6] Morse Code:\n";
    buildReverseMorse();
    string c6 = textToMorse(TEXT);
    cout << "  Morse:   " << c6 << "\n";
    playMorse(c6);
    cout << "  Decoded: " << morseToText(c6) << "\n";
}

int main() {
    int choice;
    do {
        cout << "\n====== Lab 18-19: Cryptography ======\n";
        cout << "1. Caesar Cipher\n";
        cout << "2. Simple Substitution\n";
        cout << "3. Vigenere Cipher\n";
        cout << "4. Polybius Square\n";
        cout << "5. Playfair Cipher\n";
        cout << "6. Morse Code\n";
        cout << "7. Demo (all ciphers)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: runDemo(); break;
        }
    } while (choice != 0);

    return 0;
}
