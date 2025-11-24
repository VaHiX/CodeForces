// Problem: CF 1972 A - Contest Proposal
// https://codeforces.com/contest/1972/problem/A

/*
 * Problem: A. Contest Proposal
 * Algorithm: Greedy approach with two pointers
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input arrays
 *
 * The task is to make sure that for all i, a[i] <= b[i], where both arrays are sorted.
 * We can insert new elements into array 'a' and remove the largest element each time,
 * effectively maintaining a fixed-size array of size n. We greedily determine how many
 * insertions are needed by comparing elements from 'a' and 'b'.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long cnt(0), idx(0);  // cnt counts new problems, idx tracks current position in 'a'
    for (long p = 0; p < n; p++) {
      if (b[p] < a[idx]) {
        ++cnt;  // Need to insert a new problem with difficulty b[p]
      } else {
        ++idx;  // Move to next element in 'a' as it's already suitable
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/