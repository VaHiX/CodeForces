// Problem: CF 2094 B - Bobritto Bandito
// https://codeforces.com/contest/2094/problem/B

/*
B. Bobritto Bandito
Purpose: Given an infection segment [l, r] after n days, find a valid segment [l', r'] that could have been infected on the m-th day (m <= n).
Algorithm: The infection spreads from the center (house 0) outward, forming a continuous segment each day. On day d, the segment has length 2*d + 1, centered at 0.
Time Complexity: O(1) per test case
Space Complexity: O(1)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, l, r;
    scanf("%ld %ld %ld %ld", &n, &m, &l, &r);
    // Calculate the left boundary of the segment on day m
    long left = (l > -m ? l : -m);
    // Right boundary is left + m (since length of segment is 2*m + 1)
    long right = left + m;
    printf("%ld %ld\n", left, right);
  }
}


// https://github.com/VaHiX/codeForces/