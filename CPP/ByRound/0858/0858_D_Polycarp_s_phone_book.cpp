// Problem: CF 858 D - Polycarp's phone book
// https://codeforces.com/contest/858/problem/D

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define endl "\n"
#define Max(x, y, z) max(x, max(y, z))
#define Min(x, y, z) min(x, min(y, z))
unordered_map<string, int> P; // Hash map to store substrings and their associated phone number index
string s[70001]; // Array to store the phone numbers
int n, i, j, k;
int main() {
  // Read the number of phone numbers and store them
  for (cin >> n, i = 1; i <= n; i++)
    for (cin >> s[i], j = 1; j <= 9; j++) // For each phone number, consider all substrings of length j
      for (k = 0; j + k <= 9; k++) {
        int &x = P[s[i].substr(k, j)]; // Get reference to the count of this substring
        // If this is the first time we see this substring or if it belongs to the same phone number
        x = x == 0 || x == i ? i : -1; // Mark it as belonging to multiple numbers if not
      }
  // After marking all substrings, find the shortest unique substring for each phone number
  for (auto &p : P) { // Iterate through all substrings
    i = p.second; // Get the phone number index that this substring belongs to
    if (i > 0 && s[i].size() > p.first.size()) // If it's a valid phone number and the current substring is shorter
      s[i] = p.first; // Update the phone number to the shorter unique substring
  }
  // Output the shortest unique substring for each phone number
  for (i = 1; i <= n; i++)
    cout << s[i] << "\n";
}


// https://github.com/VaHiX/CodeForces/