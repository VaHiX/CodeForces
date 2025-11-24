// Problem: CF 2064 D - Eating
// https://codeforces.com/contest/2064/problem/D

/*
D. Eating
Algorithms/Techniques: Bit manipulation with trie-like structure and prefix XOR preprocessing

Time Complexity: O(n * log W + q * log W) where W is the maximum weight (less than 2^30)
Space Complexity: O(n * log W)

This code simulates a process where a new slime of weight x is added to the end of a line
of slimes and eats slimes to its left according to certain rules. It uses prefix XOR and
bit-by-bit simulation with a precomputed table to efficiently calculate how many slimes
are eaten for each query.
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long ll;
int n, q, a[200002], s[200002], t[200002][32];

void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), s[i] = s[i - 1] ^ a[i]; // Compute prefix XOR
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= __lg(a[i]); j++)
      t[i][j] = i; // Initialize trie-like table with current index
    for (int j = __lg(a[i]) + 1; j <= 30; j++)
      t[i][j] = t[i - 1][j]; // Propagate from previous row if bit not set
  }
  while (q--) {
    int x, to = n;
    scanf("%d", &x);
    for (int j = 30; j >= 0; j--)
      if (x >= (1 << j)) { // If current bit of x is set
        int tmp = t[to][j]; // Find the farthest index with this bit set in path
        x ^= s[tmp] ^ s[to]; // Adjust x using prefix XOR
        to = tmp; // Move to that index
        if (!to || a[to] > x) // Stop condition: no more slimes or weight too high
          break;
        x ^= a[to--]; // Eat the slime at 'to' and move left
      }
    printf("%d ", n - to); // Output number of slimes eaten (from current position to end)
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
    putchar('\n');
  }
}


// https://github.com/VaHiX/codeForces/