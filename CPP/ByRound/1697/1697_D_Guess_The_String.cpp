// Problem: CF 1697 D - Guess The String
// https://codeforces.com/contest/1697/problem/D

/*
 * Problem: Guess The String (Interactive)
 * 
 * Approach:
 * - Use a combination of two types of queries:
 *   1. Type 1: Get character at position i
 *   2. Type 2: Count distinct characters in range [l, r]
 * 
 * The solution uses binary search to identify repeated characters:
 * - For each position i, we try to find if s[i] has appeared before in earlier positions
 * - By querying the number of distinct characters in range [v[m], i], we determine if s[i] equals s[v[m]]
 * - If the count increases, then s[i] is new; otherwise, it's a repeat
 * 
 * Time Complexity: O(n^2 * log(n)) - For each of n positions, we may do binary search with log(n) queries
 * Space Complexity: O(n) - For storing the string and vector of indices
 * 
 * This code attempts to reconstruct a string using only up to 26 type-1 queries and 6000 type-2 queries.
 * It maintains a vector `v` which stores indices where characters were first seen.
 * 
 * Note: The actual implementation uses a complex logic to determine character repetitions,
 *       which might not be optimized, but works within given constraints.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int n, x;
char c;
string s;
vector<int> v;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int l = -1, r = v.size();
    r--; // Adjust r to point to last element in v
    while (l < r) {
      int m = (l + r + 1) / 2; // Binary search on v to find where repeated char might be
      cout << "? 2 " << v[m] + 1 << ' ' << i + 1 << endl; // Query count of distinct chars from v[m] to i
      cin >> x;
      if (x == v.size() - m + 1) { // If count matches number of elements from m to end of v + 1,
        r = m - 1; // No new distinct char - s[i] is equal to s[v[m]]  
      } else {
        l = m; // New distinct char found - move to right half
      }
    }
    if (l == -1) { // No previous character found - new character
      cout << "? 1 " << i + 1 << endl;
      cin >> c;
      s += c;
      v.push_back(i); // Mark this as first occurrence
    } else {
      s += s[v[l]]; // Character is repeated - copy from previous
      v[l] = i; // Update index in v to current position
      sort(v.begin(), v.end()); // Keep v sorted
    }
  }
  cout << "! " << s << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/