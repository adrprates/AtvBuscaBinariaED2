#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string toLowerCase(const string& str) {
    string result = str;
    for (char& ch : result) {
        ch = tolower(ch);
    }
    return result;
}

void binarySearchByPrefix(const vector<string>& names, const string& prefix) {
    string prefixLower = toLowerCase(prefix);
    int start = 0, end = names.size() - 1;
    vector<string> results;

    while (start <= end) {
        int mid = (start + end) / 2;
        string nameLower = toLowerCase(names[mid]);

        if (nameLower.compare(0, prefixLower.size(), prefixLower) == 0) {
            results.push_back(names[mid]);

            int left = mid - 1;
            while (left >= 0 && toLowerCase(names[left]).compare(0, prefixLower.size(), prefixLower) == 0) {
                results.push_back(names[left]);
                --left;
            }

            int right = mid + 1;
            while (right < names.size() && toLowerCase(names[right]).compare(0, prefixLower.size(), prefixLower) == 0) {
                results.push_back(names[right]);
                ++right;
            }
            break;
        } else if (nameLower > prefixLower) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    if (results.empty()) {
        cout << "No results found for prefix: " << prefix << "\n";
    } else {
        cout << "Search results:\n";
        for (const string& result : results) {
            cout << result << "\n";
        }
    }
}

int main() {
    ifstream inputFile("C:/Users/natsa/OneDrive/Documentos/nomes.txt");
    if (!inputFile) {
        cerr << "Error opening file 'nomes.txt'.\n";
        return 1;
    }

    vector<string> names;
    string name;

    while (getline(inputFile, name)) {
        names.push_back(name);
    }
    inputFile.close();

    sort(names.begin(), names.end());

    string prefix;
    cout << "Enter the prefix to search: ";
    cin >> prefix;

    binarySearchByPrefix(names, prefix);

    return 0;
}
