// Problem: CF 1920 A - Satisfying Constraints
// https://codeforces.com/contest/1920/problem/A

/*
Algorithm: Satisfying Constraints
Time Complexity: O(n), where n is the number of constraints per test case.
Space Complexity: O(n), for storing the list of forbidden values.

This solution tracks the minimum and maximum valid values of k based on
constraints of type 1 (>= x) and type 2 (<= x). Then, it subtracts the count
of forbidden values (type 3) that fall within this range.
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(0), mx(1e9 + 7); // Initialize bounds: mn is min valid, mx is max valid
    std::vector<long> v; // Store forbidden values (type 3 constraints)
    for (long p = 0; p < n; p++) {
      int a;
      long x;
      scanf("%d %ld", &a, &x);
      if (a == 1) {
        mn = (mn > x ? mn : x); // Update minimum valid value
      } else if (a == 2) {
        mx = (mx < x ? mx : x); // Update maximum valid value
      } else {
        v.push_back(x); // Store forbidden value
      }
    }
    long cnt(mx - mn + 1); // Total integers in range [mn, mx]
    for (long p = 0; p < v.size(); p++) {
      if (mn <= v[p] && v[p] <= mx) { // Check if forbidden value is in valid range
        --cnt; // Decrease count if forbidden value falls in valid range
      }
    }
    printf("%ld\n", (cnt > 0 ? cnt : 0)); // Output number of valid integers, or 0 if none
  }
}


// https://github.com/VaHiX/codeForces/