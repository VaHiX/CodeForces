// Problem: CF 1692 E - Binary Deque
// https://codeforces.com/contest/1692/problem/E

/*
E. Binary Deque
Algorithm: Two Pointers / Sliding Window
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing positions of 1s

The problem asks to find the minimum number of operations (removing elements from ends)
to reduce the sum of a binary array to exactly s.

Approach:
- First, we collect positions of all 1s in the array.
- We then try to find a window of size (s+2) that contains exactly s 1s from the array,
  such that the remaining elements are removed.
- For each valid window, compute how many elements need to be removed from both ends
  to get a subarray with sum s.
- The answer is the minimum number of operations across all possible windows.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s;
    scanf("%ld %ld", &n, &s);
    std::vector<long> v(1, -1); // Start with sentinel position -1
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x) {
        v.push_back(p); // Store positions of 1s
      }
    }
    v.push_back(n); // End with sentinel position n
    
    // Check if there are enough 1s to form a subarray with sum s
    if (v.size() < s + 2) {
      puts("-1");
      continue;
    }
    
    long mxlen(0);
    // Sliding window over possible positions of 1s
    for (long p = s; p + 1 < v.size(); p++) {
      // Compute length of subarray excluding the first and last elements in current window
      long len = (v[p + 1] - 1) - v[p - s];
      mxlen = (mxlen > len) ? mxlen : len;
    }
    
    // Minimum operations = total elements - maximum length of valid subarray with sum s
    printf("%ld\n", n - mxlen);
  }
}


// https://github.com/VaHiX/codeForces/