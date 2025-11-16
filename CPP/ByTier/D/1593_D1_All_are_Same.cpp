// Problem: CF 1593 D1 - All are Same
// https://codeforces.com/contest/1593/problem/D1

/*
Problem: Find the maximum possible value of k such that all elements in the array can be made equal 
by repeatedly subtracting k from any element. 

Approach:
- For each test case, find the minimum element in the array.
- Compute the GCD of all differences (a[i] - mn) where mn is the minimum element.
- The answer is this GCD if it's positive; otherwise, return -1.

Time Complexity: O(n * log(max_value)) per test case due to GCD calculations.
Space Complexity: O(n) for storing the array.

Algorithms/Techniques:
- GCD computation using Euclidean algorithm
- Vector usage for input storage
*/

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    long mn(1e7); // Initialize minimum to a large value
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      mn = (mn < a[p]) ? mn : a[p]; // Update minimum element
    }
    long g(0); // Initialize GCD result to 0
    for (long p = 0; p < n; p++) {
      g = gcd(g, a[p] - mn); // Compute GCD of all differences
    }
    printf("%ld\n", g ? g : -1L); // Print result or -1 if no valid k
  }
}


// https://github.com/VaHiX/codeForces/