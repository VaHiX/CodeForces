// Problem: CF 2126 A - Only One Digit
// https://codeforces.com/contest/2126/problem/A

/*
Problem: A. Only One Digit
Algorithms/Techniques: Digit manipulation, brute force
Time Complexity: O(log n) per test case, where n is the value of x
Space Complexity: O(1)

You are given an integer x. You need to find the smallest non-negative integer y 
such that the numbers x and y share at least one common digit.

The approach:
- For each number x, we want to find the smallest y such that x and y have a common digit.
- Since y must be non-negative and we want the minimum, we can iterate through possible digits 0 to 9.
- For each digit d from 0 to 9, if d is present in x's decimal representation, then choosing y = d will satisfy the condition.
- Among all such valid digits, we choose the smallest one.

This works because:
- If we can find a digit 'd' that appears in x, then setting y = d gives us minimum possible y (as it's a single digit).
- We simply check which digits from 0 to 9 exist in x and pick the smallest such digit.
*/

#include <stdint.h>
#include <iostream>

using namespace std;
#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
void solve() {
  int n, r(10); // r stores the minimum digit found so far; initialized to 10 (invalid digit)
  cin >> n;
  while (n > 0) {
    if ((n % 10) < r) // check if current last digit is smaller than previously found minimum
      r = n % 10;     // update the minimum digit
    n /= 10;          // remove last digit from n
  }
  cout << r << "\n";
}
int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/