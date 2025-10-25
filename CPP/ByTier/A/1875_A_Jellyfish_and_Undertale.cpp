// Problem: CF 1875 A - Jellyfish and Undertale
// https://codeforces.com/contest/1875/problem/A

/*
 * Problem: Jellyfish and Undertale
 * Algorithm/Technique: Greedy approach
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * We are given a bomb with an initial timer value 'b'. Each second, the timer decreases by 1.
 * We have 'n' tools that can be used at most once. Using tool i increases the timer by x[i],
 * but if the result exceeds 'a', it's capped to 'a'.
 *
 * Strategy:
 * To maximize the time until explosion, we should prioritize using tools that give us
 * the highest possible increase in timer value (up to 'a') at each step.
 * We iterate through all seconds and for each second, we can choose which unused tools
 * to use such that their combined effect maximizes the timer before decreasing it by 1.
 *
 * Key Insight:
 * At each second, we decide whether using a tool now gives us more than the current timer.
 * For simplicity and optimality, we can always sort or greedily pick tools to increase timer.
 * Since we process one second at a time, we want to add just enough to prevent the timer
 * from dropping below a certain point. However, it's sufficient to check if using the tool helps:
 * If x[i] < (a - current_timer), then current_timer += x[i], else current_timer = a.
 *
 * This is a greedy simulation where we compute the maximum delay possible by choosing
 * the most beneficial tool at each step for maximizing the final timer value.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n;
    scanf("%lld %lld %lld", &a, &b, &n);
    ll res(b); // Initialize result with current timer 'b'
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // Greedily choose how much to increase based on the cap 'a' and current state
      res += (x < (a - 1)) ? x : (a - 1); // Add tool effect, capped at (a - 1)
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/