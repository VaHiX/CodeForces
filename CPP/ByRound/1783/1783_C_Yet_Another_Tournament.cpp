// Problem: CF 1783 C - Yet Another Tournament
// https://codeforces.com/contest/1783/problem/C

/*
C. Yet Another Tournament

Algorithm:
- For each test case, we are to determine the minimum possible place (rank) the player can achieve.
- The player wins against opponent i if they prepare for at least a[i] minutes.
- There are n+1 participants (player + n opponents).
- Each participant plays exactly once against every other one.
- The player loses against opponent i if the opponent i > player (i.e., i-th opponent has a higher rank in the tournament).
- However, when the player vs opponent i happens, the outcome is determined by the preparation time:
  - If time >= a[i], player wins
  - Else player loses
- Each match involves only one type of preparation.
- The final place is based on number of wins + 1 (i.e., if you have k wins, you get rank k+1 if others have more than k wins).
- Strategy:
  1. Sort opponents by their required preparation times.
  2. Greedily try to win against the easiest opponents (lowest a[i]) while not exceeding total time m.
  3. Count how many such wins we can make.
  4. To optimize further (since we can consider one more match if possible):
     - Check whether in case of partial success, adding an extra win (with highest opponent we've skipped) is beneficial.

Time Complexity: O(n log n + n) per test case due to sorting and single pass through array.
Space Complexity: O(n) for storing vectors a and b.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read preparation times
    }
    std::vector<long> b(a); // Copy of original array for sorting
    sort(b.begin(), b.end()); // Sort preparation times ascending
    long cnt(0);
    for (long p = 0; p < n; p++) {
      if (m >= b[p]) { // If we can afford to prepare for opponent p (by time)
        m -= b[p];     // Use up the preparation time
        ++cnt;         // Increment win count
      } else {
        break;         // We cannot afford more opponents
      }
    }
    // Possibly consider including one additional win (if allowed by the logic)
    cnt += (0 < cnt && cnt < n && (m + b[cnt - 1] >= a[cnt]));
    printf("%ld\n", n + 1 - cnt); // Output the rank based on number of wins
  }
}


// https://github.com/VaHiX/codeForces/