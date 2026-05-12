#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

int main() {
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

    return 0;
}