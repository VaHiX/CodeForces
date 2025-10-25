// Problem: CF 1445 B - Elimination
// https://codeforces.com/contest/1445/problem/B

/*
B. Elimination
Algorithm: Greedy approach to minimize the cutoff score.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks us to find the smallest possible total score of the 100th participant
in the final ranking, given constraints on the minimum scores of top 100 participants
in each contest.

We are given:
- a: score of 100th participant in first contest
- b: minimum score of 100 participants in second contest  
- c: score of 100th participant in second contest
- d: minimum score of 100 participants in first contest

To minimize the cutoff, we want to maximize the scores of participants who will make it to the final,
so we assign maximum possible scores based on constraints.

In the optimal case:
- Participants in first contest: all get at least 'd' points (constraint on first contest's top 100)
- Participants in second contest: all get at least 'b' points (constraint on second contest's top 100)

So the minimum possible cutoff score is simply the sum of the maximum values each participant 
can achieve under constraints:
max(first_contest_score, second_contest_score) = max(a, d) + max(b, c) = (a + b) or (c + d)
We want to minimize this total.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long u = a + b;     // Sum of max scores for first contest
    long v = c + d;     // Sum of max scores for second contest
    long ans = (u > v) ? u : v;  // Minimum possible cutoff
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/