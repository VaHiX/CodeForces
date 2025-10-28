// Problem: CF 1898 E - Sofia and Strings
// https://codeforces.com/contest/1898/problem/E

/*
Algorithm/Technique: 
This solution uses a Binary Indexed Tree (Fenwick Tree) and greedy approach to determine if string t can be formed from string s using the specified operations.
The key idea is to process characters of t in order and for each character, find the earliest position in s where that character exists such that all characters to the right in s (after that position) are not greater than the current character.

Time Complexity: O(n log n + m log n) where n is the length of string s and m is the length of string t.
Space Complexity: O(n) for the BIT and auxiliary data structures.
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

using std::cin, std::cout, std::ios;
const int MAX_N = 255 + 10, MAX_M = 2e5 + 10;
std::deque<int> pos[MAX_N];
std::string s, t;
int T, n, m, BIT[MAX_M];

// Function to calculate maximum character in range [1, x] using BIT
int calc(int x) {
  int s = 'a' - 1;
  for (; x; x -= x & (-x))
    s = std::max(s, BIT[x]);
  return s;
}

// Function to update BIT at position x with character c
void update(int x, char c) {
  for (; x <= n; x += x & (-x))
    BIT[x] = std::max(BIT[x], (int)c);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  for (; T--;) {
    cin >> n >> m >> s >> t;
    s = " " + s; // prepend space to make indexing 1-based
    t = " " + t; // prepend space to make indexing 1-based
    bool ans = 1;
    
    // Clear position queues for each test case
    for (int i = 'a'; i <= 'z'; ++i)
      pos[i].clear();
    
    // Preprocess positions of each character in string s
    for (int i = 1; i <= n; ++i) {
      pos[s[i]].push_back(i), BIT[i] = 'a' - 1;
    }
    
    // Process each character in target string t
    for (int i = 1; i <= m; ++i) {
      char nw = t[i];
      bool ok = 0;
      
      // Try to find a valid position for character nw
      for (; !pos[nw].empty();) {
        int x = pos[nw].front();
        pos[nw].pop_front();
        
        // Calculate the effective rightmost character in s after position x
        // This uses BIT to check if all characters to the right are <= nw
        if (calc(n - x + 1) <= nw) {
          ok = 1;
          update(n - x + 1, nw); // Update BIT with this character
          break;
        }
      }
      
      // If no valid position found for character nw, return NO
      if (!ok) {
        ans = 0;
        break;
      }
    }
    
    // Output result
    if (ans)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/