// Problem: CF 1088 C - Ehab and a 2-operation task
// https://codeforces.com/contest/1088/problem/C

/*
Algorithm: Greedy approach with prefix manipulation
Techniques: Modular arithmetic, prefix sum, constructive algorithm

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by first adding enough to each prefix to make the elements
at each position congruent to 0 modulo n. Then, a single modulo operation on 
the entire array makes all elements strictly increasing.

This solution leverages the fact that:
1. We can add values to prefixes
2. We can take modulo with a fixed number on prefixes
3. By choosing a large enough modulus (n), we can ensure the result is strictly increasing
*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  long mx(0);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    mx = (mx > a[p]) ? mx : a[p];  // Find maximum element for potential overflow handling
  }
  printf("%ld\n", n + 1);  // Total operations needed: n additions + 1 modulo
  long sum(0);  // Tracks cumulative addition
  for (long p = n - 1; p >= 0; p--) {
    // Calculate how much to add such that (a[p] + sum) % n == 0
    long add = (p - (a[p] + sum) % n + n) % n;
    printf("1 %ld %ld\n", p + 1, add);  // Perform prefix addition
    sum += add;  // Update cumulative sum
  }
  printf("2 %ld %ld\n", n, n);  // Final modulo operation on entire array
  return 0;
}


// https://github.com/VaHiX/CodeForces/