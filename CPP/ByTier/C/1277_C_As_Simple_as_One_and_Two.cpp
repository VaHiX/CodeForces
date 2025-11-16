// Problem: CF 1277 C - As Simple as One and Two
// https://codeforces.com/contest/1277/problem/C

/*
Algorithm: Greedy string matching
Approach:
- For each test case, we need to find and remove substrings "one" and "two" and "twone" 
  such that we minimize the number of characters removed.
- We scan the string for occurrences of "twone", "one", "two" and mark the middle character
  of each matched substring for removal.
- This greedy strategy ensures we remove minimal number of positions.

Time Complexity: O(n * m) where n is the length of the string and m is the number of patterns.
Space Complexity: O(n) for storing the vector of indices to be removed.

The find() method is used to locate all occurrences of each pattern, and we mark the middle
character of the matched substring as to be removed.

We process in order of "twone", "one", "two" to ensure optimal greedy matching.
*/

#include <stddef.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  string s;
  cin >> t;
  while (t--) {
    cin >> s;
    vector<int> v;
    for (string t : {"twone", "one", "two"}) {
      for (size_t p = 0; (p = s.find(t, p)) != string::npos;) {
        s[p + t.size() / 2] = ' '; // Mark the middle character to be removed
        v.push_back(p + t.size() / 2); // Store the index of the character to be removed
      }
    }
    cout << v.size() << '\n';
    for (auto i : v)
      cout << i + 1 << ' '; // Convert to 1-based indexing for output
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/