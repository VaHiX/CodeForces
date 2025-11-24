// Problem: CF 1097 C - Yuhao and a Parenthesis
// https://codeforces.com/contest/1097/problem/C

/*
C. Yuhao and a Parenthesis
Purpose: This program solves the problem of pairing bracket sequences such that each pair forms a valid bracket sequence.
Algorithm: 
  - For each input bracket sequence:
    * Compute a "balance" value by counting opening and closing brackets (with +1 for '(' and -1 for ')')
    * Track the minimum prefix balance during traversal
    * Store statistics about how many sequences have certain prefix minima and final balances
  - Then for each valid pair of sequences:
    * A sequence with minimum prefix balance `min1` and final balance `final1`
    * Another with min prefix balance `min2` and final balance `final2`
    * Valid pairing: final1 == 0, final2 == 0, and (min1 + final1) >= 0 and (min2 + final2) >= 0.
    * However, here we store counts in an array indexed by a computed value based on prefix minima
    * The algorithm effectively counts matching pairs of bracket sequences using the key insight:
      A sequence with prefix min `m` and total balance `c` can be paired with another if:
        1. Their total balances sum to 0 (c1 + c2 = 0)
        2. The minimum prefix of each combined sequence is >= 0
    * This is achieved via clever indexing: index = 2 * (max(0, -min) + (min < 0))
Time Complexity: O(S) where S is the sum of all input string lengths.
Space Complexity: O(N): N = 5e5 + 1 (fixed size array for statistics).
*/

#include <stdio.h>
int const N = 5e5 + 1;
int n, m, c, r, i, d[2 * N]; // d[] is a frequency counter array
char s[N], *p;
int main() {
  scanf("%d", &n);
  while (n--) { // For each bracket sequence input
    m = c = 0;   // m = minimum prefix balance, c = current balance
    scanf("%s", s); // read one bracket string
    for (p = s; *p; p++) { // traverse through the string
      c += 81 - *p * 2;  // convert char to +1 or -1 (since '(' is 40 and ')' is 41)
      m = m < c ? m : c; // update minimum prefix balance
    }
    d[2 * (m < 0 ? -m : c) + (m < 0)] += m == (c < 0 ? c : 0); // store counts based on prefix min and final balance
  }
  for (; i < 2 * N; i += 2) // iterate through pairs in the counter array
    r += d[i] < d[i + 1] ? d[i] : d[i + 1]; // sum min counts from each pair (matching left to right)
  printf("%d", r + d[0] / 2); // final result: total pairs plus half of those that are perfectly self-paired
}


// https://github.com/VaHiX/codeForces/