// Problem: CF 1530 A - Binary Decimal
// https://codeforces.com/contest/1530/problem/A

/*
Purpose: To find the minimum number of binary decimal numbers that sum up to a given number n.
Binary decimal: A number consisting only of digits 0 and 1.
Algorithm:
    - For each iteration:
        * Try to subtract the largest possible binary decimal from n.
        * This is done by taking each digit of n:
            - If digit is 0 or 1, include it as is.
            - If digit is greater than 1, include 1 (to make it 1).
        * The process continues until n becomes 0.
Time Complexity: O(log n) per test case (since we process digits of n)
Space Complexity: O(1) - only using a few variables.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
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
  int p, r;
  sf(t); // Read number of test cases
  while (t--) {
    sf(n); // Read the number n for current test case
    int ans = 0; // Initialize the count of binary decimals
    while (true) {
      m = n; // Store original value of n
      k = 0; // Initialize k to build the binary decimal
      p = 1; // Position multiplier (1, 10, 100, ...)
      while (n) {
        r = n % 10; // Get last digit
        n /= 10; // Remove last digit
        if (r <= 1)
          k += p * r; // If digit is 0 or 1, use it as-is
        else
          k += p; // If digit > 1, use 1 (largest possible 0/1 digit)
        p *= 10; // Move to next decimal place
      }
      ans++; // Increment number of binary decimals used
      n = m - k; // Subtract the built binary decimal from m
      if (!n) // If n is now 0, we're done
        break;
    }
    pf(ans); // Print result
    nl; // Print newline
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/