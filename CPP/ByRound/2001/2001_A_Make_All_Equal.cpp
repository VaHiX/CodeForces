// Problem: CF 2001 A - Make All Equal
// https://codeforces.com/contest/2001/problem/A

/*
 * Problem: Make All Equal
 * Algorithm: Greedy approach with frequency counting
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to the vector f of size n+1
 *
 * The key idea is that we want to minimize the number of operations to make all elements equal.
 * The optimal strategy is to find the most frequent element in the array and delete all other elements.
 * This requires deleting (n - max_frequency) elements, which is the minimum number of operations.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> f(n + 1, 0); // Frequency array to count occurrences of each element
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++f[x]; // Increment frequency of element x
    }
    long mxf(0); // Variable to store maximum frequency
    for (long p = 0; p < f.size(); p++) {
      mxf = (mxf > f[p] ? mxf : f[p]); // Update maximum frequency
    }
    printf("%ld\n", n - mxf); // Minimum operations = total elements - max frequency
  }
}


// https://github.com/VaHiX/codeForces/