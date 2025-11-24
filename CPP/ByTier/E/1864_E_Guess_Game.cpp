// Problem: CF 1864 E - Guess Game
// https://codeforces.com/contest/1864/problem/E

/*
E. Guess Game

Algorithms/Techniques:
- Bit manipulation and prefix computation using binary representation
- Sorting with bit operations
- Modular arithmetic and fast exponentiation for inverse modulo
- Combinatorial counting with careful inclusion of game logic for turn decisions

Time Complexity: O(n * log n + n * 30) where n is the number of elements in the array.
Space Complexity: O(n)

Description:
This code calculates the expected number of turns in a guess game involving Alice and Bob,
based on bitwise OR operations (a | b) of two randomly selected numbers from sequence s.
It processes pairs (i_a, i_b) where the game outcome determines how many turns are needed
based on players' reasoning capabilities. The solution computes the total number of turns
across all cases and divides by the total number of possible pairs to get expected value.

The approach uses bit manipulation for identifying when a player can or cannot deduce
the relative values of a and b, considering the constraints imposed by their given values
and the OR result.
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int mod = 998244353;
int T, n, a[200005];

// Fast exponentiation for modular inverse
int qpow(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1)
      res = 1ll * res * x % mod;
    x = 1ll * x * x % mod;
    y /= 2;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1); // Sort to enable binary search on prefix

    int ans = 0;

    // Process each element as 'a' in pair (a, b)
    for (int i = 1; i <= n; i++) {
      int lst = 1, num = 0;
      // Iterate over bits from MSB to LSB
      for (int j = 29; j >= 0; j--) {
        if (!(a[i] & (1 << j)))
          continue;

        int l = lst, r = i - 1, pos = -1, lim = (a[i] >> j) << j;
        num++;

        // Binary search for the rightmost element satisfying condition
        while (l <= r) {
          int mid = (l + r) >> 1;
          if (a[mid] < lim)
            l = mid + 1, pos = mid;
          else
            r = mid - 1;
        }

        // If applicable range exists update the answer
        if (lst <= pos) {
          ans = (ans + 1ll * (pos - lst + 1) * (2 * num + 1) % mod) % mod;
          lst = pos + 1;
        }
      }
    }

    // Handle same elements — they yield 1 turn if a == b, otherwise more turns
    for (int l = 1, r = 1; l <= n; l = r + 1) {
      while (r < n && a[r + 1] == a[l])
        r++;
      ans = (ans + 1ll * (r - l + 1) * (r - l + 1) % mod *
                       (__builtin_popcount(a[l]) + 1) % mod) %
            mod;
    }

    // Final answer is modular division of total turns by total pairs
    cout << 1ll * ans * qpow(1ll * n * n % mod, mod - 2) % mod << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/