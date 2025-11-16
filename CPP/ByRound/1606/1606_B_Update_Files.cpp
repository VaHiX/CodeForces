// Problem: CF 1606 B - Update Files
// https://codeforces.com/contest/1606/problem/B

/*
B. Update Files
Algorithms/Techniques: Greedy approach with geometric growth simulation
Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem involves distributing an update file from one computer to all n computers using k patch cables.
At each hour, we can copy the update from existing computers to others, with a maximum of k simultaneous copies.
The strategy is to first exponentially grow the number of computers with updates (doubling each hour if possible),
then distribute the remaining computers using at most k copies per hour.

Key steps:
1. First, simulate exponential growth: double the number of updated computers each hour,
   up to the point where we have enough cables or reach n computers.
2. Then, calculate how many additional hours are needed for the remaining computers.
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll cur(1), cnt(0); // cur: current number of computers with update; cnt: hours used
    while (cur < n && cur <= k) { // while we can still double and haven't reached n or k limits
      cur *= 2; // double the number of updated computers
      ++cnt; // increment hour count
    }
    if (cur < n) { // if not all computers are updated yet
      // calculate remaining computers and distribute them using at most k per hour
      cnt += (n - cur + k - 1) / k;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/