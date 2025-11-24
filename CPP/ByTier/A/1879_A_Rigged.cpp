// Problem: CF 1879 A - Rigged!
// https://codeforces.com/contest/1879/problem/A

/*
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per test case, where n is the number of athletes
Space Complexity: O(1), only using a constant amount of extra space

The problem is about choosing a weight 'w' such that the first athlete (Polycarp) 
wins the competition. For each athlete, if their strength 's' is less than 'w', 
they cannot lift the barbell at all. Otherwise, they can lift it exactly 'e' times.
We need to find a value of 'w' such that the first athlete lifts more times than any other.

Approach:
1. Start with the first athlete's endurance 'rep' as the base for comparison.
2. For each of the remaining athletes, if their strength is at least 'w', 
   then their endurance must be less than 'rep', otherwise 'w' isn't valid.
3. If any such conflict is found, return -1.
4. Otherwise, return the initial value of 'w' as it satisfies the necessary condition.
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    long w, rep;
    scanf("%ld %ld", &w, &rep);
    bool possible(true);
    for (long p = 1; p < n; p++) {
      long s, e;
      scanf("%ld %ld", &s, &e);
      if (s < w) {
        // This athlete cannot lift the barbell, so we ignore them
        continue;
      } else if (e >= rep) {
        // This athlete can lift the barbell and has equal or more repetitions,
        // so choosing w would not make Polycarp win
        possible = false;
      }
    }
    if (possible) {
      // If no conflict was found, w is a valid choice
      printf("%ld\n", w);
    } else {
      // If there's a conflict, no valid w exists
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/CodeForces/