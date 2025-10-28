// Problem: CF 1977 A - Little Nikita
// https://codeforces.com/contest/1977/problem/A

/*
A. Little Nikita
Problem Description:
Nikita starts with an empty tower and performs exactly n moves, each move either adding or removing one cube.
We need to determine if it's possible to end up with exactly m cubes after n moves.

Algorithm:
- The key insight is that the number of cubes can only change by ±1 per move.
- To reach exactly m cubes from 0 cubes in n moves, the net change must be m,
  and the number of additions minus subtractions must equal m.
- Let a = number of additions, b = number of subtractions.
  Then: a + b = n and a - b = m
  Solving gives: a = (n + m) / 2, b = (n - m) / 2
  Both a and b must be non-negative integers, implying:
    - n + m must be even (so that a is integer)
    - n >= m (since a must be non-negative)
    - n >= 0, m >= 0 (given)

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    // Check conditions:
    // 1. n >= m (can't have more cubes than moves)
    // 2. n and m have same parity (both odd or both even)
    puts((n >= m) && (n % 2 == m % 2) ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/