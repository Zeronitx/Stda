#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

int main() {
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

    return 0;
}
