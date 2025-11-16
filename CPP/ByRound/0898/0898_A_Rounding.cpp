// Problem: CF 898 A - Rounding
// https://codeforces.com/contest/898/problem/A

/*
Algorithm: Rounding to nearest number ending in 0
Techniques: Modular arithmetic, conditional logic

Time Complexity: O(1) - The algorithm performs a constant number of operations regardless of input size.
Space Complexity: O(1) - Only a fixed amount of extra space is used.

The problem requires rounding a given number 'n' to the nearest integer that ends in 0.
If 'n' already ends in 0, it is already rounded.
Otherwise, we check the last digit:
- If last digit >= 5, we round up by adding 1 to the tens part and appending 0.
- If last digit < 5, we round down by simply truncating the last digit and appending 0.
Special case: if n is a single digit (0-9), we round to 0 if it's less than 5, otherwise to 10.
*/

#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200
#define inf 1000000000
#define pp pair<string, int>
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, t;
  scanf("%I64d", &n);  // Read input number
  m = n % 10;          // Get the last digit of n
  if (m == 0) {        // If number already ends in 0
    printf("%I64d", n);
    return 0;
  }
  if (m >= 5) {        // If last digit is 5 or more, round up
    t = n / 10;        // Get all digits except the last one
    printf("%I64d0", t + 1);  // Add 1 to tens part and append 0
  } else {             // If last digit is less than 5, round down
    t = n / 10;        // Get all digits except the last one
    if (n > 9)         // If n has more than one digit
      printf("%I64d0", t);    // Print tens part and append 0
    else
      printf("0");     // Special case for single digits less than 5
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/