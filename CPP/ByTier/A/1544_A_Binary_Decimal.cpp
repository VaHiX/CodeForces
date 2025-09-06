/*
 * Problem URL : https://codeforces.com/contest/1544/problem/A
 * Submit Date : 2025-09-01
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << *max_element(s.begin(), s.end()) - '0' << endl;
    }
}
