// Problem: CF 734 B - Anton and Digits
// https://codeforces.com/contest/734/problem/B

/*
 * Problem: Anton and Digits
 * Purpose: To maximize the sum of numbers 32 and 256 that can be formed from given digits.
 * Algorithm: 
 *   - First, form as many 256s as possible using available 2, 5, and 6 digits.
 *   - Then, use remaining 2s and 3s to form 32s.
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only using a fixed number of variables.
 */

#include <iostream>

typedef long long int ll;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll k2, k5, k3, k6;
  cin >> k2 >> k3 >> k5 >> k6;
  
  // Form as many 256s as possible using min(k2, k5, k6) 
  ll m = min3(k2, k5, k6);
  ll count = (256) * m; // Add contribution of 256s to total sum
  k2 -= m;  // Reduce count of available 2s
  k5 -= m;  // Reduce count of available 5s
  k6 -= m;  // Reduce count of available 6s

  // Form as many 32s as possible using remaining 2s and 3s
  m = min2(k2, k3);
  count += (32) * m;  // Add contribution of 32s to total sum

  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/