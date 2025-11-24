// Problem: CF 2064 B - Variety is Discouraged
// https://codeforces.com/contest/2064/problem/B

/*
B. Variety is Discouraged

Purpose:
This program finds the optimal contiguous subarray to remove from an array such that the resulting array has maximum score,
where score = length - number of distinct elements.
The solution involves identifying a "single" element (appears only once in the current state), and extending
the longest contiguous sequence of such elements. Additionally, if we do not have any such sequence, we try removing
a subarray to maximize the score.

Algorithms:
- Use two sets: 'singles' for elements that appear exactly once, 'dupes' for elements that appear more than once.
- Scan through the array to categorize elements into singles and dupes, adjusting as we add new elements.
- Then scan again to find the longest contiguous subarray of elements from 'singles'.
- If there is no such subarray (or all are duplicates), no removal needed.

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

*/
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    std::set<long> singles, dupes;
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      if (dupes.count(v[p])) {
        continue; // Already marked as duplicate, skip
      } else if (singles.count(v[p])) {
        // First time seeing this element again -> now it's a duplicate
        dupes.insert(v[p]);
        singles.erase(v[p]);  // Remove from singles
      } else {
        singles.insert(v[p]); // New unique element
      }
    }
    long crl(-1), mxlen(-1);
    long left(-1), right(-1);
    for (long p = 0; p < n; p++) {
      if (singles.count(v[p])) {
        // Start or extend a valid segment
        if (crl < 0) {
          crl = p;
        }
        if (p - crl + 1 > mxlen) {
          mxlen = p - crl + 1;
          left = crl + 1;
          right = p + 1;
        }
      } else {
        // Reset segment
        crl = -1;
      }
    }
    if (left < 0) {
      puts("0");
    } else {
      printf("%ld %ld\n", left, right);
    }
  }
}


// https://github.com/VaHiX/codeForces/