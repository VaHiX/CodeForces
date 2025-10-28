// Problem: CF 2060 B - Farmer John's Card Game
// https://codeforces.com/contest/2060/problem/B

/*
B. Farmer John's Card Game
Algorithms/Techniques: Sorting, Greedy, Validation of permutation
Time Complexity: O(n * m * log(m)) per test case due to sorting each row
Space Complexity: O(n * m) for storing the card decks

The problem involves finding a valid order (permutation) of cows such that
each cow plays all their cards in increasing order and the game is consistent.
Each cow's deck is sorted, then we check if consecutive elements in each
deck differ by exactly n, which ensures they can be played in sequence by
some valid turn order. We also track mapping from first element to cow index.

Input:
- t: number of test cases
- For each case:
  - n: number of cows, m: cards per cow
  - n lines with m integers (cards for each cow)
Output:
- A valid permutation p if possible, else -1

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> v(n, std::vector<long>(m, 0));
    for (long p = 0; p < n; p++) {
      for (long q = 0; q < m; q++) {
        scanf("%ld", &v[p][q]);
      }
    }
    bool res(true);
    std::vector<long> w(n, 0);
    for (long p = 0; res && p < n; p++) {
      sort(v[p].begin(), v[p].end()); // Sort each cow's deck
      w[v[p][0]] = p; // Map the smallest card to this cow's index
      for (long q = 1; res && q < m; q++) {
        if (v[p][q - 1] + n != v[p][q]) { // Check if cards are spaced by n
          res = false;
        }
      }
    }
    if (res) {
      for (long p = 0; p < n; p++) {
        printf("%ld ", 1 + w[p]); // Output the permutation (1-indexed)
      }
      puts("");
    } else {
      puts("-1"); // No valid permutation exists
    }
  }
}


// https://github.com/VaHiX/codeForces/