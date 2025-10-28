// Problem: CF 1354 A - Alarm Clock
// https://codeforces.com/contest/1354/problem/A

/*
 * Problem: Alarm Clock
 * Algorithms/Techniques: Mathematical simulation, case analysis
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Polycarp needs to sleep for at least 'a' minutes. He falls asleep after 'b'
 * minutes and then wakes up. Each time he wakes up, if he hasn't slept enough,
 * he resets the alarm for 'c' minutes and spends 'd' minutes falling back asleep.
 * The simulation continues until he gets out of bed or determines it's impossible.
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, c, d;
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
    ll ans(0);
    
    // If he already has enough sleep from the first alarm
    if (b >= a) {
      ans = b;
    } 
    // If he can never get enough sleep (cycle)
    else if (c <= d) {
      ans = -1;
    } 
    // Otherwise, calculate remaining time needed after initial wake-up
    else {
      a -= b;  // Remaining sleep needed after first alarm
      // Compute number of iterations required to meet the sleep goal
      ans = b + ((a + c - d - 1) / (c - d) * c);
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/