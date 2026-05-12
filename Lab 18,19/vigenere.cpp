#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

    printVigenereTable();

    cout << "1 - Encrypt\n2 - Decrypt\nChoice: ";
    cin >> choice;

    if (choice == 1)
        cout << "Encrypted: " << vigenereEncrypt(text, key) << "\n";
    else
        cout << "Decrypted: " << vigenereDecrypt(text, key) << "\n";

    return 0;
}
