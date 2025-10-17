// Problem: CF 1921 C - Sending Messages
// https://codeforces.com/contest/1921/problem/C

/*
C. Sending Messages

Algorithm:
- For each message, calculate the time difference from the previous message (dur).
- At each step, decide whether it's cheaper to:
  1. Keep the phone on and consume `a * dur` charge, or
  2. Turn off and on (costing `b` charge) to minimize total charge consumption.
- If at any point the remaining charge becomes zero or negative, output "NO".
- Total time complexity: O(n) per test case.
- Space complexity: O(1).

Input:
- t: number of test cases
- n, f, a, b: messages count, initial charge, cost per unit time, cost to turn off/on
- m1, m2, ..., mn: moments to send messages

Output:
- "YES" if all messages can be sent under charge constraints, else "NO".
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, c, a, b;
    scanf("%lld %lld %lld %lld", &n, &c, &a, &b);
    ll prev(0), used(0);
    for (ll p = 0; p < n; p++) {
      ll m;
      scanf("%lld", &m);
      ll dur = m - prev; // Duration since last message
      prev = m;
      // Choose minimum between turning off/on (b) or staying on (a * dur)
      used += (((a * dur) < b) ? (a * dur) : b);
    }
    puts(used < c ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/