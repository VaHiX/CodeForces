// Problem: CF 1934 D1 - XOR Break --- Solo Version
// https://codeforces.com/contest/1934/problem/D1

/*
 * Problem: D1. XOR Break — Solo Version
 * Purpose: Determine if it's possible to transform an integer x from initial value n to target value m
 *          in at most 63 break operations using the given rules. If possible, output the sequence.
 *
 * Algorithm:
 * - The problem is based on bitwise operations and transformation through XOR.
 * - Key idea is to analyze the binary representation of x and y and make decisions on how to reduce x
 *   to match y by choosing appropriate y values and applying XOR or direct assignment.
 * - The solution attempts to simulate the transformation step by step, considering bit positions.
 *
 * Time Complexity: O(log n) per test case, since we iterate through bits up to 60.
 * Space Complexity: O(1), only storing a small vector for the output path.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
#define _int64 long long
#define mo 998244353
int main() {
  int i, j, k, n, l, t, m, o, b1, h, ansn;
  vector<_int64> ans;
  _int64 x, y, tmp;
  scanf("%d", &t);
  for (l = 0; l < t; l++) {
    scanf("%lld%lld", &x, &y);
    // Find the highest bit position of x
    for (i = 60; i >= 0; i--)
      if (((1LL << i) & x) != 0)
        break;
    h = i;
    ansn = -1;
    ans.clear();
    // Iterate bit by bit from high to low
    for (; i >= 0; i--) {
      // If current bit of x and y differ
      if (((1LL << i) & x) != ((1LL << i) & y)) {
        // If this is not the highest differing bit
        if (i != h) {
          ansn = 1;
          ans.push_back(x);
          ans.push_back(y);
          break;
        }
        // Find the next set bit before the highest one
        for (j = i - 1; j >= 0; j--)
          if (((1LL << j) & x) != 0)
            break;
        if (j == -1)
          break;
        // Create a temporary value and check if we can reach target
        tmp = (1LL << j) * 2 - 1;
        if (y <= tmp) {
          ansn = 1;
          ans.push_back(x);
          ans.push_back(tmp);
          if (y != tmp) {
            ansn++;
            ans.push_back(y);
          }
        }
        break;
      }
    }
    printf("%d\n", ansn);
    for (i = 0; i < ans.size(); i++)
      printf("%lld ", ans[i]);
    printf("\n");
  }
}


// https://github.com/VaHiX/CodeForces/