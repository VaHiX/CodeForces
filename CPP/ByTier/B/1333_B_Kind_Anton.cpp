// Problem: CF 1333 B - Kind Anton
// https://codeforces.com/contest/1333/problem/B

/*
B. Kind Anton
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
There are two arrays of integers a and b of length n. It turned out that array a contains only elements from the set {-1, 0, 1}.
Anton can perform the following sequence of operations any number of times:
Choose any pair of indexes (i, j) such that 1 <= i < j <= n.
Add a[i] to a[j]. In other words, j-th element of the array becomes equal to a[i] + a[j].
For example, if you are given array [1, -1, 0], you can transform it only to [1, -1, -1], [1, 0, 0] and [1, -1, 1] by one operation.
Anton wants to predict if it is possible to apply some number (zero or more) of these operations to the array a so that it becomes equal to array b. Can you help him?

Algorithms/Techniques:
Greedy approach with tracking constraints based on values in array a.

Time Complexity: O(n) per test case
Space Complexity: O(1) 
*/

#include <stdio.h>
int t, n, a[100000], b[100000];
bool solve() {
  bool c[3]{}; // Tracks whether we can decrease (0), keep same (1), or increase (2)
  for (int i = 0; i < n; i++) {
    if (a[i] > b[i]) { // If a[i] is larger than b[i], we need to decrease it
      if (!c[0]) // If we are not allowed to decrease, return false
        return 0;
    } else if (a[i] < b[i]) { // If a[i] is smaller than b[i], we need to increase it
      if (!c[2]) // If we are not allowed to increase, return false
        return 0;
    }
    c[a[i] + 1] = 1; // Mark the type of operation that can be made (0 -> decrease, 1 -> same, 2 -> increase)
  }
  return 1;
}
int main() {
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
      scanf("%d", b + i);
    }
    if (solve()) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/