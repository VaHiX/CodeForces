// Problem: CF 1490 C - Sum of Cubes
// https://codeforces.com/contest/1490/problem/C

/*
C. Sum of Cubes
Purpose: Determine if a given positive integer x can be expressed as the sum of cubes of two positive integers.
Algorithm:
- For each test case, iterate through all possible values of 'a' such that a^3 <= x.
- For each 'a', compute b^3 = x - a^3 and check if b^3 is a perfect cube using binary search.
- Binary search is used in isCube() function to efficiently determine if a number is a perfect cube.
Time Complexity: O(t * c * log(max_cube)), where t is number of test cases, c is the cube root of x, and max_cube is up to 10^4.
Space Complexity: O(1)
*/
#include <cstdio>
typedef long long ll;

// Function to check if a number is a perfect cube using binary search
bool isCube(ll num) {
  ll left(1), right(10007); // Search range for cube root; sufficient for numbers up to 10^12
  while (left <= right) {
    ll mid = (left + right) / 2;
    ll cube = mid * mid * mid; // Compute mid^3
    if (cube == num) {
      return true; // Found exact match
    } else if (cube < num) {
      left = mid + 1; // Search higher values
    } else if (cube > num) {
      right = mid - 1; // Search lower values
    }
  }
  return false; // No perfect cube found
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x;
    scanf("%lld", &x);
    bool ans(false);
    for (ll p = 1; p * p * p <= x; p++) { // Iterate up to cube root of x
      ll y = x - p * p * p; // Compute remaining part for second cube
      if (isCube(y)) { // Check if remainder is a perfect cube
        ans = true;
        break;
      }
    }
    puts(ans ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/