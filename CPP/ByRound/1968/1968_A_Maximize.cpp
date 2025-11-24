// Problem: CF 1968 A - Maximize?
// https://codeforces.com/contest/1968/problem/A

/*
Code Purpose:
This code solves the problem of finding an integer y (1 ≤ y < x) such that gcd(x,y) + y is maximized.
The approach is to observe that for any x > 1, choosing y = x - 1 will yield the maximum value of gcd(x,y) + y.
This is because gcd(x, x-1) = 1 (consecutive integers are coprime), so we get 1 + (x-1) = x.
Time Complexity: O(t) where t is the number of test cases
Space Complexity: O(1)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    printf("%ld\n", x - 1); // Output x-1 as the optimal y value
  }
}


// https://github.com/VaHiX/CodeForces/