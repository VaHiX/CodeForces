// Problem: CF 1927 E - Klever Permutation
// https://codeforces.com/contest/1927/problem/E

/*
Code Purpose:
This code constructs a k-level permutation of length n for given integers n and k (where k is even).
A k-level permutation ensures that all contiguous segment sums of length k differ by at most 1.
The algorithm uses a cyclic assignment strategy to balance the sums.

Algorithms/Techniques:
- Cyclic assignment of numbers from 1 to n
- Alternating between increasing and decreasing sequences to balance sums
- Time and space complexity are determined by the loop structure and vector usage.

Time Complexity: O(n) - We iterate through the array once per k elements and then print the array.
Space Complexity: O(n) - For storing the permutation vector of size n.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(n, 0); // Initialize a vector of size n with all elements 0
    long a(1), b(n); // 'a' starts from 1, 'b' starts from n
    for (long p = 0; p < k; p++) { // For each group of k elements
      for (long q = p; q < n; q += k) { // For every k-th element starting from p
        if (p % 2) { // If p is odd, assign from b (decreasing)
          v[q] = b--;
        } else { // If p is even, assign from a (increasing)
          v[q] = a++;
        }
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p]); // Print the constructed permutation
    }
    puts(""); // Print a newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/