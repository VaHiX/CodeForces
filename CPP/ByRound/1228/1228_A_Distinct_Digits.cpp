// Problem: CF 1228 A - Distinct Digits
// https://codeforces.com/contest/1228/problem/A

/*
A. Distinct Digits
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

You have two integers l and r. Find an integer x which satisfies the conditions below:
 
 l <= x <= r. 
 All digits of x are different. 
If there are multiple answers, print any of them.

Algorithms/Techniques: Brute Force
Time Complexity: O((r - l) * log(r)) where log(r) is the number of digits in r
Space Complexity: O(1) - only using a fixed size array of 10 integers for digit counting

*/
#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010101
#define inf 1e18
#define mod 100000007
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
  int n, m, r, l;
  bool f;
  sff(l, r); // Read the range [l, r]
  for (i = l; i <= r; i++) { // Iterate through each number in range
    k = i;
    int a[10] = {0}; // Array to count occurrences of each digit (0-9)
    f = true; // Flag to indicate if current number has all distinct digits
    while (k) { // Extract each digit of current number
      m = k % 10; // Get last digit
      a[m]++; // Increment count for that digit
      k /= 10; // Remove last digit
      if (a[m] > 1) { // If any digit appears more than once
        f = false; // Mark as invalid
        break; // Exit loop early
      }
    }
    if (f) { // If all digits are distinct
      pf(i); // Print the number
      return 0; // Exit program
    }
  }
  pf(-1); // No valid number found
  return 0;
}


// https://github.com/VaHiX/codeForces/