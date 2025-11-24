// Problem: CF 1539 A - Contest Start
// https://codeforces.com/contest/1539/problem/A

/*
 * Problem: Contest Start
 * Algorithm: Mathematical summation optimization
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The dissatisfaction of a participant at time t is equal to:
 * number of participants who started but not yet finished.
 *
 * For n participants starting every x minutes, with each contest lasting t minutes:
 * - Participant i (0-indexed) starts at time i*x and finishes at time i*x + t
 * - At the finish time of participant i, we count how many participants have started
 *   but not yet finished.
 *
 * The key insight is that the number of participants still in contest at time t
 * equals: min(n, (t / x) + 1) when considering all those who started before or at time t.
 * However, for optimization:
 * - Let a = t / x (number of intervals completed before or during last contest)
 * - We compute how many participants are active from the start up to a
 * - Using arithmetic series sum formula for total dissatisfaction.
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n, x, t; // n participants, interval x, duration t
    scanf("%lld %lld %lld", &n, &x, &t);
    
    ll a = (t / x); // number of time intervals completed before or at finish
    a = (a < n) ? a : n; // limit to total number of participants
    
    // Compute the sum of dissatisfaction using arithmetic series:
    // Sum of first 'a' natural numbers multiplied by a factor and subtracted from n*a
    ll res = n * a - a * (a + 1) / 2;
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/