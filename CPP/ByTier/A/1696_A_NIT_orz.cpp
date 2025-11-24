// Problem: CF 1696 A - NIT orz!
// https://codeforces.com/contest/1696/problem/A

/*
 * Purpose: This code solves a problem where we are given an array of integers
 * and a value z. We can perform operations to update elements of the array and z
 * using bitwise OR and AND operations. The goal is to find the maximum possible
 * value in the array after any number of operations.
 *
 * Algorithm:
 * - For each element in the array, we compute x | z (bitwise OR), which is the
 *   value that would result from applying the operation on that element.
 * - The maximum among all such computed values is our answer, since we can
 *   always choose the best element to maximize the result.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, z;
    scanf("%lld %lld", &n, &z);
    ll mx(0); // Initialize maximum value to 0
    while (n--) {
      ll x;
      scanf("%lld", &x);
      ll y = x | z; // Compute bitwise OR of current element and z
      mx = (mx > y) ? mx : y; // Keep track of the maximum value encountered
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/CodeForces/