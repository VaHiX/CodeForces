// Problem: CF 1413 A - Finding Sasuke
// https://codeforces.com/contest/1413/problem/A

/*
Code Purpose:
This program solves the problem of finding a set of seals (b_i) that can open a door described by another set of seals (a_i), such that the dot product of the two sequences equals zero. The algorithm works by pairing up elements from the input array and assigning alternating signs to construct a valid solution. Since n is even, we can always pair up all elements and assign appropriate values to satisfy the condition.

Algorithms/Techniques:
- Greedy pairing: For each pair of consecutive elements in the array, we use one element as the positive value and the other as the negative value to ensure their dot product contributes zero to the total.
- Time Complexity: O(n), where n is the number of seals in a door (since we iterate through half the array).
- Space Complexity: O(1), as we only use a constant amount of extra space.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int t;
int n;
int a[105];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n / 2; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      printf("%d %d ", -b, a);  // Pair up elements and assign alternating signs to satisfy dot product = 0
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/