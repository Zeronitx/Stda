#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, end, index;
};

int main() {
    int n;
    cout << "Number of activities: ";
    cin >> n;

    vector<Activity> a(n);
    for (int i = 0; i < n; i++) {
        a[i].index = i + 1;
        cout << "Activity " << i+1 << " (start end): ";
        cin >> a[i].start >> a[i].end;
    }

    sort(a.begin(), a.end(), [](Activity x, Activity y) {
        return x.end < y.end;
    });

    vector<Activity> result;
    int lastEnd = -1;

    for (int i = 0; i < n; i++) {
        if (a[i].start >= lastEnd) {
            result.push_back(a[i]);
            lastEnd = a[i].end;
        }
    }

    cout << "\nTotal activities: " << result.size() << endl;
    cout << "#\tStart\tEnd" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].index << "\t" << result[i].start << "\t" << result[i].end << endl;
    }

    return 0;
}

