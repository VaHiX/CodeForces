// Problem: CF 1505 B - DMCA
// https://codeforces.com/contest/1505/problem/B

/*
B. DMCA
Digital Millennium Calculation Act problem: find the integer square root of a number.

Algorithm: Digital Millennium Calculation Act
- Repeatedly sum digits of the number until it becomes a single digit
- This is equivalent to finding the digital root of the number
- The digital root can be computed using formula: (n - 1) % 9 + 1 for n > 0

Time Complexity: O(log n) - where log n is the number of digits in n
Space Complexity: O(1) - only using constant extra space

Input: single integer a (1 <= a <= 1000000)
Output: integer result (the digital root)
*/
#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m, t;
  sf(n); // Read the input number
  while (n >= 10) { // While the number has more than one digit
    m = n; // Store current number
    n = 0; // Reset n to accumulate sum of digits
    while (m) { // Extract each digit and add to n
      n += m % 10; // Add last digit to n
      m /= 10; // Remove last digit from m
    }
  }
  pf(n); // Print the final single digit result
  return 0;
}


// https://github.com/VaHiX/codeForces/