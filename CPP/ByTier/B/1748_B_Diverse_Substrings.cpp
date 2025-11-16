// Problem: CF 1748 B - Diverse Substrings
// https://codeforces.com/contest/1748/problem/B

/*
Purpose: This code counts the number of "diverse" substrings in a given string of digits.
         A substring is considered diverse if the maximum frequency of any character in it
         does not exceed the number of distinct characters in it.

Algorithm:
- For each starting index i in the string:
  - Iterate through substrings starting at i, extending up to 100 characters (optimization).
  - Maintain a map to count character frequencies.
  - Track the maximum frequency of any character seen so far.
  - If the maximum frequency is <= number of distinct characters, increment the result counter.

Time Complexity: O(n * min(n, 100)) = O(n^2) in worst case, but with an optimization that limits
                 inner loop to 100 iterations, effectively making it O(n * 100) = O(n).
Space Complexity: O(10) = O(1), since there are at most 10 distinct digits (0-9), 
                   so the map uses constant space.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void solve() {
  int ans = 0, n;
  cin >> n;
  string s;
  cin >> s;
  
  for (int i = 0; i < n; i++) {
    int ho = 0;  // Tracks the maximum frequency of any character in current substring
    map<char, int> m;  // Maps characters to their frequencies in current substring
    
    // Loop is limited to 100 characters for optimization (since max distinct chars = 10,
    // and max frequency cannot exceed 10 for a substring to be diverse)
    for (int j = i; j < n and j <= i + 99; j++) {
      m[s[j]]++;        // Increment frequency of current character
      ho = max(ho, m[s[j]]);  // Update maximum frequency
      
      // If max frequency <= number of distinct characters, substring is diverse
      if (ho <= m.size())
        ans++;
    }
  }
  
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/