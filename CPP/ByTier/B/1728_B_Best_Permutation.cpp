// Problem: CF 1728 B - Best Permutation
// https://codeforces.com/contest/1728/problem/B

/*
Purpose: This code finds a permutation of numbers from 1 to n that maximizes a specific value calculation process.
         The process starts with x = 0, and for each element in the permutation:
         - If x < current element, then add the element to x
         - Otherwise, reset x to 0
         The goal is to maximize the final value of x.

Algorithms/Techniques: 
- Greedy approach with carefully constructed permutation
- The strategy is to arrange numbers such that we increment x as much as possible,
  but reset it only when necessary.

Time Complexity: O(n) - Single pass to construct the vector and one loop to rearrange elements.
Space Complexity: O(n) - Vector storage for the permutation.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      v[p] = p + 1;
    }
    // Swap adjacent pairs starting from index n%2 to maximize value
    for (long p = n % 2; p < n - 2; p += 2) {
      long tmp = v[p];
      v[p] = v[p + 1];
      v[p + 1] = tmp;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/