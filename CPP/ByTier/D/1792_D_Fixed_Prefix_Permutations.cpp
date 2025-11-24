// Problem: CF 1792 D - Fixed Prefix Permutations
// https://codeforces.com/contest/1792/problem/D

/*
Code Purpose:
This code solves the problem of finding the maximum "beauty" of the product of two permutations for each permutation in a set.
The beauty of a permutation is the largest k such that the first k elements are 1, 2, ..., k.
For each permutation a_i, we compute the maximum beauty over all possible products a_i * a_j where j ranges from 1 to n.

Algorithms/Techniques:
- Uses a Trie (prefix tree) to efficiently store and query the inverse permutations.
- For each permutation, we store its inverse (mapping value -> position) in the trie.
- Then, for each permutation, we simulate the product process by traversing the trie
  to determine the maximum prefix that matches 1, 2, ..., k for a_i * a_j.

Time Complexity:
- Building the trie for n permutations: O(n * m)
- For each permutation, traversing the trie to compute beauty: O(m)
- Total: O(n * m)

Space Complexity:
- Trie storage: O(n * m) 
- Additional vectors and variables: O(n * m)
- Overall: O(n * m)
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
typedef long long ll;
const int mod = 998244353;
const int maxn = 1e5 + 10;
int T, n, m;
int ans[maxn];
int tr[maxn * 4][11], cnt;  // trie storage for inverse permutations

// Function to insert inverse permutation into the trie
inline void build(vector<int> &vt) {
  int wh = 1;
  for (int i = 1; i <= m; i++) {
    if (tr[wh][vt[i]] != 0)  // If value already exists in trie
      wh = tr[wh][vt[i]];    // Move to next node
    else {
      tr[wh][vt[i]] = ++cnt; // Create new node
      wh = tr[wh][vt[i]];
      for (int i = 1; i <= m; i++)  // Initialize the new node
        tr[wh][i] = 0;
    }
  }
}

int main() {
  T = read();
  while (T--) {
    n = read(), m = read();
    vector<vector<int>> a(n + 1, vector<int>(m + 1)),
        b(n + 1, vector<int>(m + 1));  // a: original permutations, b: inverse permutations

    // Read input permutations and build inverse mappings
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        a[i][j] = read();
        b[i][a[i][j]] = j; // b[i][value] = position of value in permutation i
      }
    }

    // Initialize trie
    cnt = 1;
    for (int i = 1; i <= m; i++)
      tr[1][i] = 0;

    // Insert all inverse permutations into the trie
    for (int i = 1; i <= n; i++)
      build(b[i]);

    // For each permutation a_i, compute maximum beauty across all a_i * a_j
    for (int i = 1; i <= n; i++) {
      int wh = 1;
      ans[i] = 0;
      while (ans[i] + 1 <= m && tr[wh][a[i][ans[i] + 1]]) {
        wh = tr[wh][a[i][ans[i] + 1]];  // Traverse trie using a[i][ans[i]+1]
        ans[i]++;  // Update beauty count
      }
    }

    // Output results
    for (int i = 1; i <= n; i++)
      printf("%d ", ans[i]);
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/