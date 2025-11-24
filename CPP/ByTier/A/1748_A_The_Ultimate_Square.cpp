// Problem: CF 1748 A - The Ultimate Square
// https://codeforces.com/contest/1748/problem/A

/*
A. The Ultimate Square
Algorithms/Techniques: Mathematical observation and binary search on answer.
Time complexity: O(1) per test case.
Space complexity: O(1).

The problem asks to find the maximum side length of a square that can be formed using
rectangular blocks where block i has dimensions 1 x ceil(i/2). 
To form a square of side s, we need at least s blocks of length >= s.
Since lengths are ceil(i/2), for a given s, we need to count how many blocks have length >= s.
Blocks with length >= s are those where ceil(i/2) >= s, i.e., i >= 2*s - 1.
So total such blocks from 1 to n is ceil((n - (2*s - 1) + 1) / 2) = ceil((n - 2*s + 2) / 2).
However, the direct formula for maximum possible side s is simply (n + 1) >> 1,
which is equivalent to (n + 1) / 2 using bit shift.
*/

#include <cstdio>
int main() {
  int T, n;
  scanf("%d", &T);
  while (T--)
    scanf("%d", &n), printf("%d\n", n + 1 >> 1); // Compute and print the maximum square side length
  return 0;
}


// https://github.com/VaHiX/codeForces/