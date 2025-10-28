// Problem: CF 1914 C - Quests
// https://codeforces.com/contest/1914/problem/C

/*
C. Quests
Algorithm: Greedy with prefix sum and max tracking
Time Complexity: O(n) per test case
Space Complexity: O(n) for vectors a and b

Monocarp can complete at most k quests. For each quest, the first completion gives 'a[i]' experience,
subsequent completions give 'b[i]' experience. We want to maximize total experience.

The key idea is:
- Complete quest 1 first (since it's always available).
- For subsequent quests, we try to optimize by choosing which quests to complete multiple times
  in such a way that the gain from completing earlier quests more than compensates for the loss.

We iterate through all possible numbers of quests that can be completed (from 1 to min(k,n)),
and for each prefix, compute:
- Total experience from first 'p' quests (with only first completions)
- For the remaining (k - p - 1) slots, we choose the quest with highest b[i] value and do it multiple times
- This greedy approach works because b[i] is what we gain per subsequent completion.

This solution uses prefix sums for cumulative experience and keeps track of the maximum b[i]
value seen so far to determine optimal usage of remaining slots.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long csa(0), mb(0), ans(0); // csa = cumulative sum of a, mb = max b seen so far, ans = best answer
    for (long p = 0; p < n && p < k; p++) {
      csa += a[p];           // Add first completion of quest p
      mb = (mb > b[p]) ? mb : b[p]; // Keep track of maximum b value up to current quest
      long tst = csa + (k - p - 1) * mb; // Total experience: sum of first completions + (remaining slots)*max_b
      ans = (ans > tst ? ans : tst);   // Update best result
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/