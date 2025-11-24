// Problem: CF 1945 A - Setting up Camp
// https://codeforces.com/contest/1945/problem/A

/*
 * Problem: A. Setting up Camp
 *
 * Purpose:
 *   Given a number of introverts (a), extroverts (b), and universals (c),
 *   determine the minimum number of tents required to house all participants,
 *   where each tent can hold up to 3 people. Introverts must be alone in tents,
 *   extroverts must share a tent with exactly two others, and universals are flexible.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: Prioritize placing introverts first into single-person tents.
 *   - Then handle extroverts by grouping them optimally with others.
 *   - Use math to compute minimal tents required based on constraints.
 *
 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only using a fixed number of variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    
    // If there are introverts and not enough space for them to be alone,
    // we need to ensure that we can place remaining people in tents with extroverts.
    if ((b % 3) && ((b % 3) + c < 3)) {
      puts("-1");  // Impossible case: leftover extroverts and insufficient universals
      continue;
    }
    
    // Calculate minimal tents needed:
    // - 'a' tents for introverts (each one alone)
    // - 'b' extroverts require at least ceil(b / 3) tents, because each tent holds 3 people,
    //   but we want to avoid wasting space; so (b + 2) / 3 gives minimal tents needed.
    // - Add 'c' universals into these tent counts appropriately.
    printf("%ld\n", a + (b + c + 2) / 3);
  }
}


// https://github.com/VaHiX/codeForces/