// Problem: CF 1491 A - K-th Largest Value
// https://codeforces.com/contest/1491/problem/A

/*
 * Problem: K-th Largest Value
 * 
 * Algorithm/Techniques: 
 *   - Maintain a count of 1s in the array to efficiently determine the k-th largest element.
 *   - For query type 1 (flip): update the count of 1s in O(1).
 *   - For query type 2 (k-th largest): 
 *     - If k <= count of 1s, the k-th largest is 1.
 *     - Otherwise, the k-th largest is 0.
 * 
 * Time Complexity: O(n + q) where n is the size of the array and q is the number of queries.
 * Space Complexity: O(n) for storing the array.
 */
#include <cstdio>
#include <vector>
int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  long cnt(0); // Count of 1s in the array
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    cnt += a[p]; // Initialize count of 1s
  }
  while (q--) {
    long w, s;
    scanf("%ld %ld", &w, &s);
    if (w == 1) {
      --s; // Convert to 0-based indexing
      a[s] = 1 - a[s]; // Flip the value
      cnt += (2 * a[s] - 1); // Update count: add 1 if a[s] is now 1, subtract 1 if it's now 0
    } else {
      printf("%d\n", s <= cnt); // If k <= cnt, k-th largest is 1, otherwise 0
    }
  }
}


// https://github.com/VaHiX/CodeForces/