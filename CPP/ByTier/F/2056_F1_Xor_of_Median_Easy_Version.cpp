// Problem: CF 2056 F1 - Xor of Median (Easy Version)
// https://codeforces.com/contest/2056/problem/F1

/*
Problem: F1. Xor of Median (Easy Version)
Algorithms/Techniques: Bit manipulation, enumeration, median calculation, XOR logic

Time Complexity: O(K * B * m * 2^B) where B is the count of '1's in first K bits of n.
Space Complexity: O(K)

This code computes the XOR of medians over all "good" sequences of length n (given in binary),
with elements from [0, m). A good sequence satisfies a specific condition on occurrence counts.
The approach uses bit enumeration for median values and checks constraints using bit operations.

*/

#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 100005;
int T, K, m;
char s[N];
int main() {
  int i, c, x;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &K, &m);
    scanf("%s", s + 1);
    int B = 0, Ans = 0;
    for (i = 1; i <= K; i++) {
      if (s[i] == '1')
        B++;   // Count number of 1s in first K bits
    }
    for (c = 0; c < B; c++) {   // Iterate through all possible median values up to B
      if (((B - (c + 1)) & (c >> 1)) == 0) {   // Check constraint using bit operations
        for (x = 0; x < m; x++) {   // For each candidate value x
          if ((x & c) == c) {   // Check if x satisfies the median condition
            Ans ^= x;   // XOR it to accumulate result
          }
        }
      }
    }
    printf("%d\n", Ans);
  }
}


// https://github.com/VaHiX/codeForces/