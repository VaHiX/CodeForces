// Problem: CF 1675 B - Make It Increasing
// https://codeforces.com/contest/1675/problem/B

/*
B. Make It Increasing
Algorithm: Greedy approach with backward iteration
Time Complexity: O(n * log(max(a_i))) where n <= 30 and max(a_i) <= 2*10^9
Space Complexity: O(n) for the vector storage

Given a sequence of integers, we can only divide elements by 2 (floor division).
We need to find the minimum operations to make the sequence strictly increasing.
We process from right to left. For each element, if it is not smaller than the next,
we keep dividing it until it becomes smaller or we realize it's impossible.
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
      scanf("%ld", &a[p]); // Read each element
    }
    long cnt(0); // Count of operations
    for (long p = n - 2; p >= 0; p--) {
      if (a[p + 1] <= 0) { // If next element is non-positive, impossible to make increasing
        cnt = -1;
        break;
      }
      while (a[p] >= a[p + 1]) { // While current element is not smaller than next
        a[p] /= 2; // Divide current element by 2
        ++cnt; // Increment operation count
      }
    }
    printf("%ld\n", cnt); // Print result for this test case
  }
}


// https://github.com/VaHiX/codeForces/