// Problem: CF 2014 B - Robin Hood and the Major Oak
// https://codeforces.com/contest/2014/problem/B

/*
B. Robin Hood and the Major Oak

Purpose:
This program determines whether the number of leaves on the Major Oak in year n is even or odd,
based on the given parameters n (year) and k (number of years leaves last).

Algorithm:
- For each test case, we compute how many leaves were added in years [n-k+1, n]
- Since leaves from year i last for k years, the number of leaves in year n comes from:
  - Leaves added in year n-k+1 through year n
  - Each leaf added in year i contributes to year n if i <= n and i+k-1 >= n => i >= n-k+1
  - So the total number of leaves is sum_{i=n-k+1}^{n} i = (k*(2*n-k+1))/2
- To determine if it's even or odd, we simplify parity calculation using modular arithmetic.

Time Complexity: O(1)
Space Complexity: O(1)

Techniques:
- Mathematical formula for sum of an arithmetic sequence
- Modular arithmetic to check parity
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // Calculate odd = 1 if total leaves is odd, 0 if even
    // Using formula derived from sum of arithmetic sequence:
    // Sum = k * (2*n - k + 1) / 2
    // Parity check via modular arithmetic
    long odd = ((k + (n % 2)) / 2) % 2;
    puts(odd ? "NO" : "YES");  // NO if odd, YES if even
  }
}


// https://github.com/VaHiX/codeForces/