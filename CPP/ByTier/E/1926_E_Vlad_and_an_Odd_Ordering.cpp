// Problem: CF 1926 E - Vlad and an Odd Ordering
// https://codeforces.com/contest/1926/problem/E

/*
Algorithm: 
The problem involves generating a specific ordering of cards from 1 to n. 
The ordering is done by groups, where each group consists of numbers that are k times an odd number, 
processed in increasing order of k (starting from 1). 

For each group k, we count how many valid cards are there (i.e., those that are multiples of k and are ≤ n, 
and the quotient is odd). 

The algorithm simulates this process:
- It iterates through powers of 2 (2^i) to determine which group the k-th card belongs to.
- For each group, it calculates how many elements are in that group.
- Once the group is identified, it computes the actual card number using a formula derived from the pattern.

Time Complexity: O(log n) per test case, since we are iterating over powers of 2 up to n.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>
#include <iostream>

using namespace std;
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 2;; i *= 2) {
    // Determine how many elements are in this group (i.e., numbers of the form i * odd)
    // (n + i / 2) / i gives the count of valid multiples of i that are <= n and have odd quotient
    if (k > (n + i / 2) / i) {
      k -= (n + i / 2) / i;
    } else {
      // If k is within current group, compute the actual card value
      // k * i - i / 2 derives the original card number from its position in group
      printf("%d\n", k * i - i / 2);
      return;
    }
  }
}
signed main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/