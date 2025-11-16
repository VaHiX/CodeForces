// Problem: CF 2059 A - Milya and Two Arrays
// https://codeforces.com/contest/2059/problem/A

/*
Problem: A. Milya and Two Arrays

Algorithm/Technique: Set-based approach to determine if we can create at least 3 distinct sums by rearranging array a.

Time Complexity: O(n log n) per test case due to set insertion operations.
Space Complexity: O(n) for storing elements in sets.

The problem asks whether we can rearrange array 'a' such that the sum array 'c = a + b' contains at least 3 distinct elements.

Key idea:
- For each test case, we store unique elements of both arrays in sets.
- If the product of sizes of these two sets is at least 3, then it's possible to get at least 3 distinct values in c.
- This works because:
  - Each element from set a can be added to each element from set b.
  - If both sets have at least one element, we will have at least one distinct sum.
  - If either set has 2+ elements, we might get more than 1 distinct sum if the sets are different.

This greedy logic ensures that by carefully choosing a valid combination of elements from a and b,
we can generate enough distinct values in c to satisfy the requirement.

*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> a, b; // Store unique elements of arrays a and b
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a.insert(x); // Insert elements of array a into set
    }
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      b.insert(x); // Insert elements of array b into set
    }
    // If product of sizes >= 3, we can potentially form at least 3 distinct sums in c
    puts(a.size() * b.size() >= 3 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/