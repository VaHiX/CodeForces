// Problem: CF 1665 B - Array Cloning Technique
// https://codeforces.com/contest/1665/problem/B

/*
B. Array Cloning Technique
Algorithm: Greedy approach with map to count frequencies
Time Complexity: O(n log n) per test case due to map operations
Space Complexity: O(n) for storing the map and input array

The problem involves finding the minimum number of operations to make all elements in one copy of an array equal.
Each operation allows cloning a copy or swapping two elements from any two copies.
We use a frequency map to find the maximum count of any element.
Then we simulate the process of merging copies until we have enough elements of one type,
counting the number of operations needed.

Key logic:
- For each element, we find its maximum frequency
- We then simulate how many clones and swaps are required to collect all instances of that element
- The number of operations increases in steps based on doubling the count of the most frequent element
*/
#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store frequency of each element
    long cnt(0);            // Maximum frequency of any element
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x];              // Increment frequency count
      cnt = (cnt > m[x]) ? cnt : m[x]; // Update maximum frequency
    }
    long res(0);           // Result counter for operations
    while (cnt < n) {      // While we haven't collected all elements of one type
      long diff = cnt < (n - cnt) ? cnt : (n - cnt); // Minimum of current count and remaining
      res += 1 + diff;     // One clone operation + swaps needed
      cnt *= 2;            // Double the count after cloning
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/