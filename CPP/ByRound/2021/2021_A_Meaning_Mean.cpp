// Problem: CF 2021 A - Meaning Mean
// https://codeforces.com/contest/2021/problem/A

/*
 * Problem: A. Meaning Mean
 * Purpose: Given an array of positive integers, repeatedly combine two elements
 *          by taking their floored average and replacing them with the result,
 *          until only one element remains. Find the maximum possible value of
 *          the final element.
 *
 * Algorithm:
 * - Use a multiset to maintain sorted order of elements.
 * - At each step, take the two smallest elements, compute their floored average,
 *   and insert back into the multiset.
 * - Repeat until only one element remains.
 *
 * Time Complexity: O(n^2 * log n)
 *   - Each operation takes O(log n) to find and update the multiset.
 *   - There are at most n operations, so total is O(n^2 * log n).
 *
 * Space Complexity: O(n)
 *   - The multiset stores up to n elements.
 */

#include <cstdio>
#include <set>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::multiset<long> ms; // Multiset maintains sorted order of elements
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ms.insert(x); // Insert all elements into multiset
    }
    while (ms.size() > 1) {
      long x = *ms.begin();         // Get the smallest element
      ms.erase(ms.begin());         // Remove it
      long y = *ms.begin();         // Get the new smallest element
      ms.erase(ms.begin());         // Remove it
      ms.insert((x + y) / 2);       // Insert floored average back
    }
    printf("%ld\n", *ms.begin());   // Output final remaining element
  }
}


// https://github.com/VaHiX/codeForces/