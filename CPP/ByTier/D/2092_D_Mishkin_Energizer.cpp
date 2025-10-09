// Problem: CF 2092 D - Mishkin Energizer
// https://codeforces.com/contest/2092/problem/D

/*
 * Problem: D. Mishkin Energizer
 * Algorithm: Greedy simulation with string manipulation
 * Time Complexity: O(n^2) in worst case due to string insertions and operations
 * Space Complexity: O(n) for storing the result array and string
 *
 * Key Idea:
 * - To balance the string (equal counts of L, I, T), the approach is to repeatedly
 *   find adjacent differing characters, insert a third character between them,
 *   and repeat until all three characters are equally represented.
 * - If at any point it's impossible (e.g., only one character in original string),
 *   output -1.
 *
 * Approach:
 * - Identify transitions (where s[i] != s[i+1])
 * - For each such transition, insert a character that is different from both s[i] and s[i+1]
 * - Continue until all three characters appear with equal frequency
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    string s;
    cin >> n >> s;
    int prev = -1;
    vector<int> ans;
    for (int i = 0; i < n - 1; i++) {
      // If adjacent characters are different, process the transition
      if (s[i] != s[i + 1]) {
        int c = ans.size(); // current size of answer array
        // Insert 2*(distance from last processed transition) positions into answer
        for (int j = 0; j < 2 * (i - prev); j++)
          ans.push_back(i + 1 + c);
        prev = i;
      }
    }
    if (prev == -1) {
      // No transitions were found => all characters identical
      cout << -1 << "\n";
      continue;
    }
    // Handle remaining part of string after last transition
    int len = n - 1 - prev;
    for (int i = 0; i < 2 * len; i++)
      ans.push_back(n + ans.size() - len);
    cout << 2 * n << "\n";
    for (auto x : ans)
      cout << x << "\n";
  }
}


// https://github.com/VaHiX/codeForces/