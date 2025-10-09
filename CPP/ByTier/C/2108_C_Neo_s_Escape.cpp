// Problem: CF 2108 C - Neo's Escape
// https://codeforces.com/contest/2108/problem/C

/*
C. Neo's Escape
Time Complexity: O(n) where n is the number of elements in the input array. Each element is processed a constant number of times.
Space Complexity: O(n) for storing the vector 'v' which can grow up to the size of input array plus 2 additional elements.

Algorithm:
- The problem asks to find the minimum number of clones needed to press all buttons in a non-increasing order.
- We model this as finding the number of peaks (local maxima) in a sequence where each clone can only follow one path.
- The key insight is that we must "break" at positions which form local maxima, because these are points where more than one clone is required to continue traversing the remaining elements.
- We use a vector 'v' to store unique consecutive elements from input (to simplify processing), then count how many times a local maximum occurs by checking v[i-1] < v[i] > v[i+1].
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v;
    v.push_back(-1); // Sentinel value at beginning
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (v.back() == x) {
        continue; // Skip duplicates to avoid false peaks
      }
      v.push_back(x);
    }
    v.push_back(-1); // Sentinel value at end
    long cnt(0);
    for (long p = 1; p + 1 < v.size(); p++) {
      // Check if current element is a peak (local maximum)
      cnt += (v[p - 1] < v[p] && v[p] > v[p + 1]);
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/