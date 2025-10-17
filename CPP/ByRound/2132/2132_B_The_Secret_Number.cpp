// Problem: CF 2132 B - The Secret Number
// https://codeforces.com/contest/2132/problem/B

/*
B. The Secret Number

Problem Description:
Given a number n = x + y, where y is formed by appending one or more zeros to x,
find all possible values of x such that this equation holds.

Key Insight:
If x has d digits, and we append k zeros to it (making it x * 10^k), then:
n = x + x * 10^k = x * (1 + 10^k)
So x = n / (1 + 10^k) must be an integer.

Algorithm:
- Loop through all possible k from 1 to log10(n)
- For each k, check if (1 + 10^k) divides n evenly
- If so, compute potential x = n / (1 + 10^k)
- Store valid x values in ascending order

Time Complexity:
O(log(n) * t), where t is number of test cases and log(n) is the number of digits in n.

Space Complexity:
O(1) extra space excluding output array, which is bounded by a constant (max 10000).
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
int m, k, l, r, t, anc;
long long n, ans[10010];

void solve() {
  anc = 0; // Reset counter for valid x values
  scanf("%lld", &n); // Read number n
  for (long long i = 10; i < n; i *= 10) // Iterate through powers of 10 starting from 10
    if (!(n % (i + 1))) // Check if n is divisible by (i + 1)
      ans[anc++] = n / (i + 1); // Store the valid x value
  printf("%d\n", anc); // Print count of valid x values
  while (anc--) // Print all valid x in reverse order (so they're printed ascending)
    printf("%lld%c", ans[anc], " \n"[!anc]); // Conditional newline based on index
}

int main() {
  scanf("%d", &t); // Read number of test cases
  while (t--) // Process each test case
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/