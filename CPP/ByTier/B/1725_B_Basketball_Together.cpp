// Problem: CF 1725 B - Basketball Together
// https://codeforces.com/contest/1725/problem/B

/*
B. Basketball Together
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
A basketball competition is held where the number of players in a team does not have a maximum or minimum limit (not necessarily 5 players in one team for each match). There are N candidate players in the competition that will be trained by Pak Chanek, the best basketball coach on earth. The i-th candidate player has a power of P_i.
Pak Chanek will form zero or more teams from the N candidate players on the condition that each candidate player may only join in at most one team. Each of Pak Chanek's teams will be sent to compete once with an enemy team that has a power of D. In each match, the team sent is said to defeat the enemy team if the sum of powers from the formed players is strictly greater than D.
One of Pak Chanek's skills is that when a team that has been formed plays in a match, he can change the power of each player in the team to be equal to the biggest player power from the team.
Determine the maximum number of wins that can be achieved by Pak Chanek.

Algorithms/Techniques: Greedy algorithm
Time complexity: O(N * log(N))
Space complexity: O(N)

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, d;
  scanf("%ld %ld", &n, &d);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.rbegin(), a.rend()); // Sort in descending order to use greedy approach
  long rem(n), ans(0);
  for (long p = 0; p < n; p++) {
    long x = a[p]; // Current largest player power
    long num = 1 + d / x; // Minimum number of players needed to exceed D (since max power is x, we need at least ceil(D/x) players, but since integer division, we add 1)
    if (num <= rem) { // If we have enough remaining players
      rem -= num;
      ++ans;
    } else {
      break; // Not enough players to form another team
    }
  }
  printf("%ld\n", ans);
}


// https://github.com/VaHiX/codeForces/