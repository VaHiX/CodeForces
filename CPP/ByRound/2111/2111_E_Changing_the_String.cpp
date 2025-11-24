// Problem: CF 2111 E - Changing the String
// https://codeforces.com/contest/2111/problem/E

/*
E. Changing the String
Algorithm: Greedy with precomputation and tracking of transformations.
Time Complexity: O(n + q) per test case, where n is the length of string s and q is number of operations.
Space Complexity: O(1) additional space (excluding input storage).

Approach:
- Use counters to track how many 'b' and 'c' can be changed to 'a' based on future operations.
- Process each operation to update transformation counters.
- Then go through the original string and apply greedy transformations to make it lexicographically minimal.
*/

#include <iostream>
#include <string>

using namespace std;
string s;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, q;
  cin >> t;
  while (t--) {
    // Counters for tracking required changes in a forward manner
    int b = 0, c = 0, bc = 0, cb = 0, crb = 0, crc = 0;
    cin >> n >> q;
    cin >> s;
    char x, y;
    
    // Process each operation
    for (int i = 1; i <= q; ++i) {
      cin >> x >> y;
      if (x == 'b' && y == 'c')
        bc++;  // Count b->c transform that can be used later to make b cheaper
      if (x == 'c' && y == 'b')
        cb++;  // Count c->b transform that can be used later to make c cheaper

      if (y == 'a') {
        // If the target letter is 'a', check if we can convert x to 'a'
        if (x == 'b') {
          // b -> a
          if (cb) {
            // We have pending c->b transforms; use one to avoid creating more b's
            cb--, crc++;  // Transfer from cb to crc, meaning we consumed a c->b and created a c->a effect
          } else {
            // No c->b pending, so this is a direct b -> a transform
            b++;
          }
        } else if (x == 'c') {
          // c -> a
          if (bc) {
            // We have pending b->c transforms; use one to avoid creating more c's
            bc--, crb++;  // Transfer from bc to crb, meaning we consumed a b->c and created a b->a effect
          } else {
            // No b->c pending, so this is a direct c -> a transform
            c++;
          }
        }
      }
    }

    // Apply transformations greedily to make string lexicographically minimal
    for (char &ch : s) {
      if (ch == 'b') {
        // Try to change b to a if possible without increasing the count unnecessarily
        if (b) {
          b--, ch = 'a';  // Use pending b->a change
        } else if (crc) {
          crc--, cb++, ch = 'a';  // Use pending c->a effect (we already had some c->b)
        } else if (crb) {
          crb--, ch = 'a';  // Use pending b->a effect (we already had some b->c)
        }
      }
      if (ch == 'c') {
        // Try to change c to a if possible
        if (c) {
          c--, ch = 'a';
        } else if (crb) {
          crb--, bc++, ch = 'a';
        } else if (crc) {
          crc--, ch = 'a';
        } else if (cb) {
          cb--, ch = 'b';  // If we can't change c to a, maybe changing it to b makes sense
        }
      }
    }
    
    cout << s << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/