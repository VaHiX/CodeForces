// Problem: CF 830 A - Office Keys
// https://codeforces.com/contest/830/problem/A

/*
Algorithm: Dynamic Programming with Sliding Window
Approach:
  - Sort people and keys by their positions.
  - Use a sliding window of size n over the keys to assign keys to people.
  - For each window, compute the maximum distance any person needs to travel (from person to key + key to office).
  - The answer is the minimum over all such maximum distances.

Time Complexity: O(k * n + n * log n + k * log k)
  - Sorting people: O(n * log n)
  - Sorting keys: O(k * log k)
  - Sliding window loop: O(k * n)
Space Complexity: O(n + k)
  - Storing positions of people and keys
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const long N = 1e9;
  long n, k, f;
  scanf("%ld %ld %ld", &n, &k, &f);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(k);
  for (long p = 0; p < k; p++) {
    scanf("%ld", &b[p]);
  }
  sort(a.begin(), a.end()); // Sort people by position
  sort(b.begin(), b.end()); // Sort keys by position
  long ans(2 * N);
  // Try all possible windows of k - n + 1 starting positions for keys
  for (long p = 0; p <= k - n; p++) {
    long maxDist(0);
    // For each person, assign them a key from the current window
    for (long q = 0; q < n; q++) {
      long dist1 = a[q] - b[p + q]; // Distance from person to key
      if (dist1 < 0) {
        dist1 = -dist1;
      }
      long dist2 = f - b[p + q]; // Distance from key to office
      if (dist2 < 0) {
        dist2 = -dist2;
      }
      long dist = dist1 + dist2; // Total distance for this person
      maxDist = (maxDist > dist) ? maxDist : dist; // Take maximum among all
    }
    ans = (maxDist < ans) ? maxDist : ans; // Update global minimum
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/