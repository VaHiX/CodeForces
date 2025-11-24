// Problem: CF 630 B - Moore's Law
// https://codeforces.com/contest/630/problem/B

/*
 * Code purpose: Calculate the number of transistors after 't' seconds, 
 *               given an initial count 'n' and a growth factor of 1.000000011 per second.
 *               Uses exponential growth formula: n * (1.000000011 ^ t)
 *
 * Algorithms/Techniques: 
 *   - Exponential growth calculation using pow() function
 *   - Direct computation of transistors count using floating-point arithmetic
 *
 * Time Complexity: O(1) - The pow() function is treated as constant time for the given precision.
 * Space Complexity: O(1) - Only a few variables are used, no dynamic allocation.
 */

#include <math.h>
#include <stdio.h>
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("xxxx");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  double n, t, x;
  cin >> n >> t;                    // Read initial number of transistors and time in seconds
  printf("%f", n * pow(1.000000011, t));  // Compute and print result using exponential growth formula
  return 0;
}


// https://github.com/VaHiX/CodeForces/