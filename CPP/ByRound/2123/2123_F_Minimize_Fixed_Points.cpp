// Problem: CF 2123 F - Minimize Fixed Points
// https://codeforces.com/contest/2123/problem/F

/*
F. Minimize Fixed Points
Algorithms/Techniques: This code constructs a specific permutation for each input n such that:
- For all i from 2 to n, gcd(p[i], i) > 1 (i.e., the permutation is "good").
- The number of fixed points (indices where p[i] == i) is minimized.
The approach uses a greedy reassignment technique based on factorization:
- Initially, the array a is filled with identity permutation: a[i] = i
- For each i from 2 to n, if i has a divisor j such that j * j <= i, we swap a[i] and a[i/j]
This ensures gcd(p[i], i) > 1 for all i >= 2.
Time Complexity: O(n sqrt(n)) due to nested loop checking divisors up to sqrt(i)
Space Complexity: O(n) for storing the permutation array
*/

#include <stdio.h>
#include <utility>

using namespace std;
int n, a[100010];
void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    a[i] = i;  // Initialize identity permutation
    for (int j = 2; j * j <= i; j++)  // Check divisors up to sqrt(i)
      if (i % j == 0) {
        swap(a[i], a[i / j]);  // Swap to ensure gcd(p[i], i) > 1
        break;
      }
  }
  for (int i = 1; i <= n; i++)
    printf("%d ", a[i]);
  putchar('\n');
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/