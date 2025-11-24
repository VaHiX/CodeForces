// Problem: CF 1066 A - Vova and Train
// https://codeforces.com/contest/1066/problem/A

/*
Problem: A. Vova and Train
Algorithms/Techniques: Mathematical calculation using inclusion-exclusion principle

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem asks to count the number of lanterns visible to Vova on his journey.
Lanterns are placed at positions divisible by 'v'.
A standing train blocks visibility at positions from 'l' to 'r' inclusive.
We compute:
- Total lanterns from 1 to L: L / v
- Lanterns blocked by the train: r / v - (l - 1) / v
- Result = total - blocked
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll L, v, l, r;
    scanf("%lld %lld %lld %lld\n", &L, &v, &l, &r);
    // Total number of lanterns from 1 to L
    // Number of multiples of v in range [1, L]: L / v
    // Number of multiples of v in range [1, r]: r / v
    // Number of multiples of v in range [1, l-1]: (l - 1) / v
    // Subtract those blocked by the train: (r / v) - ((l - 1) / v)
    printf("%lld\n", (L / v) - (r / v) + (l - 1) / v);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/