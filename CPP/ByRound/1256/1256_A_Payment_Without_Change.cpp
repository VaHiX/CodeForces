// Problem: CF 1256 A - Payment Without Change
// https://codeforces.com/contest/1256/problem/A

/*
Problem: Payment Without Change
Task: Determine if we can form a sum S using at most 'a' coins of value 'n' and at most 'b' coins of value '1'.

Algorithm:
- For a given total sum S, try to use as many coins of value n as possible (up to a),
  then check if the remaining amount can be covered by coins of value 1 (up to b).
- The conditions to check are:
  1. Total available value (a * n + b) >= S (can we afford it at all?)
  2. Remaining after using max possible n-coins must be <= b (can remaining amount be paid with 1-coins?)

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input Format:
- q: number of test cases
- For each test case: a, b, n, S

Output Format:
- YES if possible to make sum S, NO otherwise
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll a, b, n, s;
    scanf("%lld %lld %lld %lld", &a, &b, &n, &s);
    // Check if total value is sufficient and remaining after using max n-coins can be covered by 1-coins
    bool ans = (n * a + b >= s) && (b >= s % n);
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/