// Problem: CF 861 A - k-rounding
// https://codeforces.com/contest/861/problem/A

/*
 * Problem: k-rounding
 * Purpose: Find the minimum positive integer x such that x ends with k or more zeros and is divisible by n.
 * Algorithm: 
 *   - The number x must be divisible by n and end with at least k zeros.
 *   - A number ending with k zeros is divisible by 10^k.
 *   - So x must be divisible by both n and 10^k.
 *   - The smallest such x is the LCM of n and 10^k.
 *   - LCM(a,b) = (a * b) / GCD(a,b)
 *   - Hence x = n * (10^k / GCD(10^k, n))
 * Time Complexity: O(log(min(n, 10^k))) due to GCD calculation.
 * Space Complexity: O(1) - only using a few variables.
 */
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;
int main() {
  long long int n, k;
  cin >> n >> k;
  k = pow(10, k);  // k is now 10^k
  cout << n * (k / __gcd(k, n)) << endl;  // Calculate LCM(n, 10^k) 
  return 0;
}


// https://github.com/VaHiX/CodeForces/