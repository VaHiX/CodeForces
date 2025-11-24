// Problem: CF 1176 B - Merge it!
// https://codeforces.com/contest/1176/problem/B

/*
B. Merge it!
Time Complexity: O(n) per query, where n is the size of the array.
Space Complexity: O(1), since we use a fixed-size vector of size 3.

Algorithm:
The key insight is to count elements based on their remainder when divided by 3.
We classify numbers into three categories:
- a[0]: numbers divisible by 3
- a[1]: numbers with remainder 1
- a[2]: numbers with remainder 2

To maximize the number of elements divisible by 3, we can:
1. Use all elements divisible by 3 (they contribute directly).
2. Combine pairs of elements from remainder 1 and remainder 2 to form elements divisible by 3.
3. For remaining elements of same remainder type (either 1 or 2), we can combine groups of three to make one element divisible by 3.

The algorithm:
- Count all elements by their modulo 3 value
- All elements with Mod 0 are already good
- For elements with Mod 1 and Mod 2:
  - Take min of these two (to pair them)
  - Add remaining elements from the larger group, grouped in threes (since 3*1 = 3 or 3*2 = 6, which both add one more divisible-by-3 element)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(3, 0); // a[0] counts elements % 3 == 0, a[1] for % 3 == 1, a[2] for % 3 == 2
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++a[x % 3]; // increment counter based on remainder
    }
    long cnt = a[0]; // start with count of already divisible by 3 elements
    if (a[1] < a[2]) {
      cnt += a[1] + (a[2] - a[1]) / 3; // pair smaller group with excess from larger, then take triplets from remaining
    } else {
      cnt += a[2] + (a[1] - a[2]) / 3; // same logic for opposite case
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/