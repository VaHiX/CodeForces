// Problem: CF 2145 B - Deck of Cards
// https://codeforces.com/contest/2145/problem/B

/*
B. Deck of Cards
Algorithms/Techniques: Simulation with segment management and lazy evaluation.

Time Complexity: O(n + k) per test case, where n is the number of cards and k is the number of actions.
Space Complexity: O(n) for storing the result string and auxiliary variables.

The problem simulates a deck of cards being modified by removing either top or bottom cards based on operations.
We track the range of cards that might remain in the deck after all removals, considering that '2' (wildcard)
removals can be either top or bottom. For each card position, we determine whether it's definitely removed,
definitely remains, or could have been removed depending on how the wildcard operations are resolved.

Key idea:
- Track minL and maxL: the leftmost and rightmost possible positions of remaining cards.
- For each card at position i (1-indexed), check if it lies within [minL, maxL].
  - If it's completely outside both ranges, it's removed ('-')
  - If it's inside the minL to maxL range, it's definitely present ('+')
  - Otherwise (overlapping but not fully within), it depends on wildcard choices ('?')
*/

#include <iostream>
#include <string>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for (int test = 0; test < t; test++) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int num_zeros = 0, num_twos = 0;
    for (char c : s) {
      if (c == '0')
        num_zeros++;
      else if (c == '2')
        num_twos++;
    }
    int minL = num_zeros;          // Minimum possible index of last remaining card (from left)
    int maxL = minL + num_twos;    // Maximum possible index of last remaining card (from left)
    int m = n - k;                 // Number of cards left in the final deck
    string ans(n, ' ');            // Initialize result string with spaces
    for (int i = 1; i <= n; i++) {
      long long left = (long long)i - m;     // Start of possible range where card i can be removed
      long long right = i - 1;               // End of possible range...
      char ch;
      if (left > right) {
        ch = '-';                            // Card is definitely removed
      } else {
        bool def_remain = (left <= minL && maxL <= right);   // Card is definitely present
        bool def_remove = (minL > right || maxL < left);     // Card is definitely removed
        if (def_remain)
          ch = '+';
        else if (def_remove)
          ch = '-';
        else
          ch = '?';  // Unknown due to wildcard operations
      }
      ans[i - 1] = ch;
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/