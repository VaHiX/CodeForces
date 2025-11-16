// Problem: CF 1409 A - Yet Another Two Integers Problem
// https://codeforces.com/contest/1409/problem/A

#include <cstdio>
int main() {
  const long N = 10; // Maximum value of k allowed in one move
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long diff = a - b; // Calculate difference between a and b
    if (diff < 0) {
      diff = -diff; // Take absolute value of difference
    }
    long ans = (diff + N - 1) / N; // Ceiling division to find minimum moves
    printf("%ld\n", ans);
  }
  return 0;
}
/*
Problem: Yet Another Two Integers Problem
Algorithm: Greedy approach using ceiling division
Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem asks for the minimum number of moves to transform integer 'a' into integer 'b',
where each move allows adding or subtracting an integer k from 1 to 10.
The optimal strategy is to compute the absolute difference and divide by 10 (rounding up),
as we can make steps of at most 10 in each move.
*/

// https://github.com/VaHiX/codeForces/