// Problem: CF 1096 A - Find Divisible
// https://codeforces.com/contest/1096/problem/A

/*
Code Purpose:
This program solves the "Find Divisible" problem where, for a given range [l, r], 
we need to find two distinct integers x and y such that x divides y.
The approach is to iterate through the range and for each l, check if 2*l is within range.
If so, we can simply return (l, 2*l) as 2*l is always divisible by l.
This greedy approach is efficient and works because we are guaranteed a solution exists.

Algorithms/Techniques:
- Greedy approach
- Basic divisibility check

Time Complexity: O(1) per query
Space Complexity: O(1)

*/

#include <cstdio>

int main() {
  for (int a; scanf("%d%d", &a, &a) > 1; printf("%d %d\n", a, 2 * a))
    ; // Read l and r, then output l and 2*l (since 2*l is always divisible by l and within range)
}


// https://github.com/VaHiX/CodeForces/