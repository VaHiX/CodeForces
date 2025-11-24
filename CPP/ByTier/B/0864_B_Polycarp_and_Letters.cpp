// Problem: CF 864 B - Polycarp and Letters
// https://codeforces.com/contest/864/problem/B

/*
Purpose: To find the maximum number of distinct lowercase letters in a "pretty" set of positions,
         where no uppercase letter appears between any two positions in the set.

Algorithm:
- Traverse the string from left to right.
- Maintain a set of distinct lowercase letters encountered so far.
- When an uppercase letter is encountered:
  - Update the maximum count of distinct lowercase letters seen so far.
  - Clear the set to start fresh.
- After loop, check one final time for the last group of lowercase letters.
- Return the maximum count found.

Time Complexity: O(n), where n is the length of the string. Each character is processed once.
Space Complexity: O(1), since the set size is bounded by 26 (number of lowercase letters).
*/
#include <algorithm>
#include <iostream>
#include <set>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string t;
  cin >> n >> t;
  set<char> s;  // Set to store distinct lowercase letters
  m = 0;        // Maximum count of distinct letters found
  for (i = 0; i < n; i++) {
    if (t[i] >= 'a' && t[i] <= 'z')  // If current character is lowercase
      s.insert(t[i]);                // Add it to the set
    else {                           // If current character is uppercase
      j = s.size();                  // Get current size of set
      m = max(m, j);                 // Update maximum
      s.clear();                     // Clear the set for next group
    }
  }
  j = s.size();     // Check final group of lowercase letters
  m = max(j, m);    // Update maximum if needed
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/