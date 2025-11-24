// Problem: CF 1714 D - Color with Occurrences
// https://codeforces.com/contest/1714/problem/D

/*
Algorithm: Greedy + String Matching
Approach:
- For each position in the string t, find the best possible match from the given set of strings s_i.
- At each step, greedily select the string that covers the furthest position.
- If no valid string can extend the coverage, it's impossible to color the entire string.

Time Complexity: O(n * len^3)
Space Complexity: O(len + n * len)

Where:
- n: number of strings in the set
- len: length of the text t
*/

#include <string.h>
#include <iostream>

using namespace std;
int _, i, tot, now, p, q, f, l, j, k, len, n, u[200], v[200], w[20];
char s[200], t[20][20];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> _;
  while (_--) {
    cin >> (s + 1) >> n;
    len = strlen(s + 1);
    for (i = 1; i <= n; i++)
      cin >> (t[i] + 1), w[i] = strlen(t[i] + 1);
    for (tot = now = p = q = 0; now < len;) {
      for (j = 0; j <= now; j++) // Check all positions up to current coverage
        for (k = 1; k <= n; k++) // For each string
          if (j + w[k] <= len) { // Check if string fits
            f = 1;
            for (l = 1; l <= w[k]; l++) // Match characters
              if (s[j + l] != t[k][l])
                f = 0;
            if (f && j + w[k] > p + w[q]) // If match and extends furthest
              p = j, q = k;
          }
      if (p + w[q] <= now) { // If no progress made
        cout << "-1" << "\n";
        goto br; // Impossible to cover
      }
      u[++tot] = p + 1; // Record start position (1-indexed)
      v[tot] = q;       // Record string index
      now = p + w[q];   // Extend coverage
    }
    cout << tot << "\n";
    for (i = 1; i <= tot; i++)
      cout << v[i] << " " << u[i] << "\n";
  br:;
  }
}


// https://github.com/VaHiX/CodeForces/