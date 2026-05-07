#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Student {
    string surname;
    int groupNumber;
    int grades[4];
    double averageScore;
};

void printStudents(const vector<Student>& arr) {
    for (const auto& s : arr) {
        cout << s.surname << "\t" << s.groupNumber << "\t";
        for (int i = 0; i < 4; i++) {
            cout << s.grades[i] << " ";
        }
        cout << "\t" << s.averageScore << "\n";
    }
    cout << "---------------------------------\n";
}

void bubbleSort(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].averageScore > arr[j + 1].averageScore) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].groupNumber < key.groupNumber) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void binarySearch(const vector<Student>& arr, double target) {
    int left = 0;
    int right = arr.size() - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (abs(arr[mid].averageScore - target) < 0.001) {
            cout << "Found: " << arr[mid].surname << " (Group: " << arr[mid].groupNumber << ")\n";
            found = true;
            break;
        }

        if (arr[mid].averageScore < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "Not found\n";
    }
}

int main() {
    vector<Student> students = {
        {"Ivanov", 101, {4, 5, 4, 3}, 0.0},
        {"Petrov", 103, {5, 5, 5, 5}, 0.0},
        {"Sidorov", 102, {3, 3, 4, 3}, 0.0},
        {"Kubrak", 101, {4, 4, 4, 4}, 0.0},
        {"Makoviy", 103, {5, 4, 5, 4}, 0.0}
    };

    for (auto& s : students) {
        double sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += s.grades[i];
        }
        s.averageScore = sum / 4.0;
    }

    printStudents(students);

    bubbleSort(students);
    printStudents(students);

    vector<Student> students_copy = students;

    insertionSort(students_copy);
    printStudents(students_copy);

    double search_score;
    cout << "Enter average score to search: ";
    cin >> search_score;

    binarySearch(students, search_score);

    return 0;
}