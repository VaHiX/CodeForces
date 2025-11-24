// Problem: CF 1698 B - Rising Sand
// https://codeforces.com/contest/1698/problem/B

/*
 * Problem: B. Rising Sand
 * 
 * Description:
 * Given n piles of sand and an integer k, we can perform operations where we add 1 sand unit
 * to each of k consecutive piles. A pile i (1 < i < n) is considered "too tall" if a[i] > a[i-1] + a[i+1].
 * Find the maximum number of piles that can be simultaneously too tall after some operations.
 *
 * Algorithm:
 * - For k <= 1, we can only perform operations that affect individual piles.
 *   In this case, for n >= 3, since each pile in the middle can become "too tall", 
 *   we can make at most (n - 1) / 2 piles too tall. This is because each operation allows
 *   us to increase a pile and its neighbors' values.
 * - For k > 1, we consider each possible window of size k that we can apply operations on.
 *   We use prefix sums or direct manipulation (but here just counting how many valid "too tall"
 *   conditions exist after applying optimal operations). However, for large k, it's not trivial
 *   to increase all middle piles to become "too tall" at once due to interaction constraints.
 * 
 * We simply iterate through each pile from index 1 to n-2 (as per condition),
 * and check if it satisfies "a[i] > a[i-1] + a[i+1]". Count such valid piles.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the vector of piles
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    if (k <= 1) {
      // If k <= 1, we can only operate on individual elements
      // so we compute max potential number of "too tall" piles.
      printf("%ld\n", (n - 1) / 2);
      continue;
    }
    long cnt(0);
    for (long p = 1; p + 1 < n; p++) {
      // Check if current pile is "too tall"
      cnt += (v[p] > v[p - 1] + v[p + 1]);
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/