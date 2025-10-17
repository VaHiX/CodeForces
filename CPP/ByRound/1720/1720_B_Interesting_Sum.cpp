// Problem: CF 1720 B - Interesting Sum
// https://codeforces.com/contest/1720/problem/B

/*
B. Interesting Sum
Algorithms/Techniques: Sorting, Greedy
Time Complexity: O(n * log(n)) per test case due to sorting
Space Complexity: O(n) for the vector storage

The problem asks to find the maximum "beauty" of a proper subsegment,
where beauty is defined as:
max(remaining elements) - min(remaining elements) + max(subsegment) - min(subsegment)
We can optimize this by noting that when we remove a subsegment [l, r],
the remaining elements are {a[0], ..., a[l-1], a[r+1], ..., a[n-1]}.
To maximize the beauty, we should try to select l and r such that:
- The max and min of the remaining elements are as far apart as possible.
- The max and min of the subsegment [l, r] are also as far apart as possible.

Since we sort the array first, the key insight is that:
- For maximum difference in remaining elements, we want to remove a segment
  containing extreme values (min or max).
- If we remove a segment from the middle, we preserve the global extrema.
- Therefore, the optimal strategy is to test removing one element or two elements and take the best.

Actually, by simple inspection, an optimal approach is:
1. Sort the array.
2. Try removing either:
   - Just the smallest element (a[0])
   - Just the largest element (a[n-1])
   - Both the smallest and largest (a[0] and a[n-1])

In all cases, we compute:
max(remaining) - min(remaining) + max(subsegment) - min(subsegment)

After sorting, if we remove elements at positions l to r, then:
- Remaining elements are a[0]...a[l-1] and a[r+1]...a[n-1]
- The max and min of remaining can be determined easily.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read all array elements
    }
    sort(a.begin(), a.end()); // Sort to simplify selection of max and min
    
    // Compute the answer by trying different removal options.
    // Since we want to remove a contiguous subsegment to maximize beauty,
    // we can consider removing segments from either ends or middle.
    // The key observation: after sorting, the maximum difference in remaining elements
    // comes only when we avoid removing one of the extreme values.
    
    long ans = a[n - 1] + a[n - 2] - a[0] - a[1]; // Best result for removing segment from middle (not including first/last)
    printf("%ld\n", ans); // Output computed maximum beauty
  }
}


// https://github.com/VaHiX/codeForces/