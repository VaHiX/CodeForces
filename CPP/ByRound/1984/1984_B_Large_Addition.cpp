// Problem: CF 1984 B - Large Addition
// https://codeforces.com/contest/1984/problem/B

/*
B. Large Addition
Purpose: Determine if a given number x can be expressed as the sum of two large positive integers with the same number of digits.
A digit is considered "large" if it is between 5 and 9 inclusive.
An integer is large if all of its digits are large.

Algorithm:
1. For each test case, we process the input number x.
2. If the last digit of x is 9, return "NO" because it's impossible to form such a sum with two large numbers (since each digit must be >= 5).
3. Then, check if the rest of the digits after removing the last digit can form valid sums:
   - If any intermediate digit is zero, it's invalid.
   - The final number (after all divisions) should be equal to 1 for a valid sum.

Time Complexity: O(log x) per test case, where log x is the number of digits in x
Space Complexity: O(1), constant space usage

Sample Input:
11
1337
200
1393938
1434
98765432123456789
11111111111111111
420
1984
10
69
119

Sample Output:
YES
NO
YES
YES
NO
YES
NO
YES
YES
NO
NO
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x;
    scanf("%lld", &x);
    bool possible(true);
    
    // If last digit is 9, it's impossible to represent as sum of two large digits
    if (x % 10 == 9) {
      possible = false;
    }
    
    x /= 10; // Remove the last digit
    
    // Check intermediate digits for validity (zero digits invalidate the number)
    while (possible && x > 9) {
      if (x % 10 == 0) {
        possible = false;
        break;
      }
      x /= 10;
    }
    
    // The remaining value must be exactly 1 to make a valid decomposition
    possible = possible && (x == 1);
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/