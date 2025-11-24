// Problem: CF 1822 A - TubeTube Feed
// https://codeforces.com/contest/1822/problem/A

/*
Problem: TubeTube Feed
Purpose: Given a list of videos with durations and entertainment values, select the most entertaining video that can be watched within a given time limit.
Algorithms/Techniques:
  - Linear scan through the array to check valid videos
  - Greedy selection for maximum entertainment value among valid options

Time Complexity: O(n) per test case
Space Complexity: O(n) due to input vectors storing durations and entertainment values

Input Format:
  - q test cases
  - For each test case:
    - n (number of videos), t (time available)
    - Array a of size n (durations)
    - Array b of size n (entertainment values)

Output Format:
  - Index of the most entertaining video that fits within time limit, or -1 if none exists.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s;
    scanf("%ld %ld", &n, &s);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long idx(-1), mxb(0);
    for (long p = 0; p < n; p++) {
      if (s < a[p] + p) { // Check if can reach video p+1 (0-indexed) within time s
        continue;
      }
      if (b[p] > mxb) { // Update maximum entertainment value and index
        idx = p + 1;    // p+1 is the 1-indexed position
        mxb = b[p];
      }
    }
    printf("%ld\n", idx);
  }
}


// https://github.com/VaHiX/codeForces/