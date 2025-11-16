// Problem: CF 961 B - Lecture Sleep
// https://codeforces.com/contest/961/problem/B

/*
 * Problem: Lecture Sleep
 * Purpose: To determine the maximum number of theorems Mishka can write down
 *          by using a secret technique to keep him awake for k consecutive minutes,
 *          starting at any possible beginning minute.
 *
 * Algorithm:
 *   - Use a sliding window technique to compute the best interval of k minutes
 *     to apply the wake-up technique.
 *   - Precompute a prefix sum array 's' where s[i] represents the sum of theorems
 *     Mishka misses (i.e., when he is asleep) in the first i minutes.
 *   - For each possible starting position of the k-minute window, calculate
 *     how many theorems would be gained by using the technique there.
 *   - Add the best gain to the total theorems he would've written without the technique.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n + 1, 0);  // Array to store the number of theorems per minute
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> w(n + 1, 0);  // Array to store Mishka's behavior (0 = asleep, 1 = awake)
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &w[p]);
  }
  std::vector<long> s(n + 1, 0);  // Prefix sum array for missed theorems
  long total(0), ms(0);  // total: theorems written without using technique, ms: max gain from using it
  for (long p = 1; p <= n; p++) {
    s[p] = s[p - 1];  // Accumulate prefix sum
    if (w[p]) {
      total += a[p];  // If awake, add to total theorems written
    } else {
      s[p] += a[p];   // If asleep, add to prefix sum (missed theorems)
    }
    // Compute the maximum missed theorems in any k-length window
    long cand = s[p] - (p >= k ? s[p - k] : 0);
    ms = (ms > cand) ? ms : cand;
  }
  total += ms;  // Add the best possible gain from the technique
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/