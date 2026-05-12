#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

    return 0;
}
