// Problem: CF 1823 B - Sort with Step
// https://codeforces.com/contest/1823/problem/B

/*
B. Sort with Step
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques: 
- Grouping elements based on their index modulo k
- Checking if a permutation can be sorted using swaps of elements at positions differing by k
- Preprocessing to count mismatches in each group
- Using one preliminary swap to potentially fix the configuration

Time Complexity: O(n) per test case, where n is the length of the permutation.
Space Complexity: O(1), as we use only a constant amount of extra space.

The problem involves sorting a permutation using swaps of elements that are exactly k positions apart.
We check if the current arrangement can be sorted directly or with one swap.
We do this by grouping indices by (index % k) and counting how many mismatches there are in each group.
If total mismatches are 0, it's already sorted.
If 2, we can fix it with one swap.
Otherwise, impossible even with one swap.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long bad(0); // Count of mismatches across all groups
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      --x; // Convert to 0-based indexing
      // Check if the current element is in correct position within its group
      bad += (x % k != p % k); 
    }
    // If no mismatches, permutation is already sorted
    if (bad == 0) {
      puts("0");
    } 
    // If exactly two mismatches, one swap could fix it
    else if (bad == 2) {
      puts("1");
    } 
    // More than two mismatches cannot be fixed with one swap
    else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/