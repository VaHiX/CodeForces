// Problem: CF 1192 C - Cubeword
// https://codeforces.com/contest/1192/problem/C

/*
C. Cubeword
time limit per test
1.7 seconds
memory limit per test
1024 megabytes
input
standard input
output
standard output

A cubeword is a special type of a crossword built from a cube with side length a.
The cube has 12 edges and the unit cubes that do not touch the edges are discarded.
Each edge must form a meaningful word, readable in either direction.
We are asked to compute how many distinct cubewords can be made from given words.

Algorithms/Techniques:
- Bitmask enumeration and precomputation with memoization
- String reversal matching for palindromic words
- Dynamic programming over character pairs
- Polya's enumeration theorem (orbit counting) applied by symmetry group considerations

Time Complexity: O(n * log(n) + m^4 * n) where m is the size of the alphabet (~62)
Space Complexity: O(m^3 + n * L) where L is max word length (≤ 10)

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#define LL long long
using namespace std;
const int kMaxN = 1e5 + 1, kMaxM = 62, kMaxL = 11, kMod = 998244353;
int n, m, r[256]; // r maps characters to indices
LL ans, f[kMaxM][kMaxM], g[kMaxM][kMaxM][kMaxM];
vector<string> l[kMaxL]; // l[i] stores all words of length i

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  
  // Map characters to indices for efficient indexing
  for (char c = 'a'; c <= 'z'; c++) {
    r[c] = m++;
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    r[c] = m++;
  }
  for (char c = '0'; c <= '9'; c++) {
    r[c] = m++;
  }

  cin >> n;
  
  // Group words by their lengths
  for (int i = 1; i <= n; i++) {
    static string s;
    cin >> s, l[s.size()].push_back(s);
  }

  // Process all word lengths from 3 to 10
  for (int i = 3; i < kMaxL; i++) {
    fill(&f[0][0], &f[kMaxM][0], 0);
    fill(&g[0][0][0], &g[kMaxM][0][0], 0);
    
    sort(l[i].begin(), l[i].end());
    
    // Count pairs of first and last characters for each word
    for (string s : l[i]) {
      string t = s;
      reverse(t.begin(), t.end());
      auto p = lower_bound(l[i].begin(), l[i].end(), t);
      
      // If the reversed version exists and is equal to current, then this is a palindrome word
      if (s <= t || p == l[i].end() || *p != t) {
        f[r[s.front()]][r[s.back()]]++;
        if (s != t) {
          f[r[s.back()]][r[s.front()]]++;
        }
      }
    }
    
    // Precompute counts for combinations of 4 character pairs
    for (int a = 0; a < m; a++) {
      for (int b = 0; b < m; b++) {
        for (int c = b; c < m; c++) {
          for (int d = c; d < m; d++) {
            LL w = f[a][b] * f[a][c] % kMod * f[a][d];
            g[b][c][d] = (g[b][c][d] + w) % kMod;
          }
        }
      }
    }

    // Combine into final answer based on symmetry considerations
    for (int a = 0; a < m; a++) {
      for (int b = a; b < m; b++) {
        for (int c = b; c < m; c++) {
          for (int d = c; d < m; d++) {
            LL w = g[a][b][c] * g[a][b][d] % kMod * g[a][c][d] % kMod *
                   g[b][c][d] % kMod;
            if (a == d) {
              ans = (ans + w) % kMod;
            } else if (a == c || b == d) {
              ans = (ans + w * 4) % kMod;
            } else if (a == b && c == d) {
              ans = (ans + w * 6) % kMod;
            } else if (a == b || b == c || c == d) {
              ans = (ans + w * 12) % kMod;
            } else {
              ans = (ans + w * 24) % kMod;
            }
          }
        }
      }
    }
  }

  cout << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/