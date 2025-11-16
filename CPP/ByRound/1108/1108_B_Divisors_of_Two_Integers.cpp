// Problem: CF 1108 B - Divisors of Two Integers
// https://codeforces.com/contest/1108/problem/B

/*
 * Problem: B. Divisors of Two Integers
 * 
 * Algorithm/Technique:
 * - The idea is to identify the largest number in the list, which must be one of the integers x or y.
 * - Then, we iterate through the sorted list and for each element that divides x, we include it in the set of divisors of x.
 * - Elements that do not divide x must be divisors of y.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of divisors.
 * Space Complexity: O(n) for storing the vector and set.
 */

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the divisors in ascending order
  std::set<long> s; // Set to store divisors of x
  long x(a[a.size() - 1]), y(0); // x is initialized to the largest element
  for (long p = 0; p < n; p++) {
    // If a[p] divides x and is not already in s, it's a divisor of x
    if ((x % a[p] == 0) && (s.count(a[p]) == 0)) {
      s.insert(a[p]); // Add to set of divisors of x
    } else {
      y = a[p]; // Otherwise, it must be a divisor of y
    }
  }
  printf("%ld %ld\n", x, y);
  return 0;
}


// https://github.com/VaHiX/CodeForces/