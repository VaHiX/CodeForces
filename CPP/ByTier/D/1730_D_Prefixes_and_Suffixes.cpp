// Problem: CF 1730 D - Prefixes and Suffixes
// https://codeforces.com/contest/1730/problem/D

/*
Algorithm: 
The problem is about checking whether two strings can be made equal by swapping prefixes of s1 and suffixes of s2.
Key observation: 
- For each position i in s1, we can pair it with position (n-1-i) in s2.
- After any number of operations, if we are to make s1 == s2, then each character in s1 at position i must be matched to a character at position (n-1-i) in s2.
- We can only swap prefixes/suffixes of same length.

Approach:
- For each valid pair of indices (i, n-1-i), we consider s1[i] and s2[n-1-i].
- We map these two characters into a canonical form by ordering them (min_char * 256 + max_char).
- The idea is to form pairs of characters (c1, c2) such that one can be swapped to the other.
- After processing all pairs:
  * If there's a mismatch in pairing (where c1 != c2), i.e., in the pair {c1, c2} where c1 != c2), then we require even occurrences of such pairs to allow for balancing.
  * If there's a match (c1 == c2), then we can have this pair in an odd count (once in a valid swap), but at most 1 such "self-pair" is allowed.

Complexity:
  Time: O(n) for each test case
  Space: O(1) since we are using a map of size at most 26*26 = 676 for lowercase letters

This approach checks if we can create equal strings using prefix/suffix swaps, using frequency counting of paired characters.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

bool chk() {
  string s, t;
  int n;
  map<int, int> Q;  // Map to count frequency of character pairs
  cin >> n >> s >> t;
  
  // For each index i in s1, pair it with (n-1-i) in s2
  // Store the pair in sorted order to normalize it
  for (int i = 0; i < n; ++i)
    Q[min(s[i], t[n - 1 - i]) * 256 + max(s[i], t[n - 1 - i])]++;  // Unique id for pair
  
  int cnt = 0;  // Count of odd frequency pairs
  for (auto [i, j] : Q) {  // Iterate through all character pairs
    if (j % 2 == 1) {  // If count is odd
      cnt++;
      // If characters in the pair are different, we can't resolve it through swaps
      if (i / 256 != i % 256)
        return false;
    }
  }
  
  // If we have more than one odd count, we cannot resolve all mismatches
  return cnt < 2;
}

int main() {
  int q;
  cin >> q;
  while (q--)
    puts(chk() ? "YES" : "NO");
}


// https://github.com/VaHiX/CodeForces/