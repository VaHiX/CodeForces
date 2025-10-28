// Problem: CF 1674 D - A-B-C Sort
// https://codeforces.com/contest/1674/problem/D

/*
D. A-B-C Sort
Algorithms/Techniques: Simulation with specific step rules for moving elements between arrays.
Time Complexity: O(n) per test case, where n is the size of array a.
Space Complexity: O(n) due to the vector a storing input elements.

The code simulates a two-step process:
Step 1: Elements from array a are moved to array b in a specific way (middle insertion).
Step 2: Elements from array b are moved to array c by taking middle elements.
We attempt to simulate this and check whether final array c is sorted.
*/
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
      scanf("%ld", &a[p]);
    }
    // Simulate Step 1: moving elements to b (invariant: b remains sorted in some way due to insertion mechanism)
    for (long p = n - 2; p >= 0; p -= 2) {
      if (a[p + 1] < a[p]) {
        long x = a[p];
        a[p] = a[p + 1];
        a[p + 1] = x;
      }
    }
    // Check if resulting array a is sorted
    bool sorted(true);
    for (long p = 1; sorted && p < n; p++) {
      if (a[p - 1] > a[p]) {
        sorted = false;
      }
    }
    puts(sorted ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/