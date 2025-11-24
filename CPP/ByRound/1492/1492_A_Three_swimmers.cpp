// Problem: CF 1492 A - Three swimmers
// https://codeforces.com/contest/1492/problem/A

/*
 * Problem: Three swimmers
 * Purpose: Given a time p when you arrive at the pool, and the times a, b, c it takes for each swimmer to complete a round,
 *          determine the minimum wait time until one of the swimmers returns to the left side.
 *
 * Algorithm:
 *   For each swimmer, compute the next time they will be at the left side after time p.
 *   This is done by finding the smallest multiple of their period (a, b, or c) that is >= p.
 *   If p is already divisible by the period, then wait time is 0.
 *   Otherwise, it's (period - (p % period)) % period.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll m, a, b, c;
    scanf("%lld %lld %lld %lld", &m, &a, &b, &c);
    
    // Calculate the time until next arrival for each swimmer
    ll ta = (a - (m % a)) % a;  // Time for swimmer 1 to reach left side again after m minutes
    ll tb = (b - (m % b)) % b;  // Time for swimmer 2 to reach left side again after m minutes  
    ll tc = (c - (m % c)) % c;  // Time for swimmer 3 to reach left side again after m minutes
    
    // Find minimum wait time among the three swimmers
    ll res = (ta < tb) ? ta : tb;
    res = (res < tc) ? res : tc;
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/