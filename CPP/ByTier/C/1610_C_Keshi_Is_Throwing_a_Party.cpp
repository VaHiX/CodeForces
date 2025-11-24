// Problem: CF 1610 C - Keshi Is Throwing a Party
// https://codeforces.com/contest/1610/problem/C

/*
Algorithm: Binary Search on Answer + Greedy Validation
Time Complexity: O(n * log(n)) per test case
Space Complexity: O(n)

The problem is to find the maximum number of friends Keshi can invite to a party such that each invited friend is happy.
Each friend has a specific constraint: at most 'a[i]' people in the party can be strictly richer than him,
and at most 'b[i]' people can be strictly poorer than him.

Approach:
1. Use binary search on the number of people we can invite (from 1 to n).
2. For each candidate number x, validate if it's possible to invite exactly x people:
   - Sort friends by their wealth (index i, so friend i has i dollars)
   - Greedily assign the first x friends to the party.
   - For each friend, check if they can be happy with the current setup:
     - Count how many people are already in the party and are poorer (k)
     - The current friend should not have more than a[i] richer people
     - And not have more than b[i] poorer people
3. The check function simulates this greedy assignment and returns true if it's possible to have x friends happy.
*/

#include <cstdio>
int _, n, i, a[200001], b[200001], ans, l, r, m;

// Check if we can invite exactly 'x' people
int check(int x) {
  int k = 0, i;
  for (i = 1; i <= n; i++)
    if (k <= b[i] && x - k - 1 <= a[i]) // Greedily add friend if constraints are met
      k++;
  return k >= x; // Return true if we could invite at least x people
}

int main() {
  scanf("%d", &_);
  while (_--) {
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
      scanf("%d%d", &a[i], &b[i]);
    l = 1;
    r = n;
    while (l <= r) {
      m = l + r >> 1; // Midpoint of binary search range
      if (check(m))
        ans = m, l = m + 1; // If valid, try to increase the number
      else
        r = m - 1; // If invalid, decrease the number
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/