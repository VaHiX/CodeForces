// Problem: CF 854 B - Maxim Buys an Apartment
// https://codeforces.com/contest/854/problem/B

/*
Algorithm: Maxim Buys an Apartment
Purpose: To determine the minimum and maximum number of good apartments that can exist
         given n total apartments and k already inhabited apartments.

Approach:
- A good apartment is one that is for sale and has at least one inhabited neighbor.
- To minimize the number of good apartments, we try to place the k inhabited apartments
  such that they cover as few possible good apartments as possible.
- To maximize, we place the k apartments to cover as many good apartments as possible.

Time Complexity: O(1)
Space Complexity: O(1)

Techniques:
- Greedy placement of inhabited apartments to achieve min/max.
- Mathematical analysis for optimal placement.
*/

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  // Calculate minimum number of good apartments
  // If k is 0 or n, there are no good apartments (since no inhabited ones or all are inhabited)
  // Otherwise, we can always arrange k such that at least one good apartment exists
  long m = (0 < k && k < n) ? 1 : 0;
  // Calculate maximum number of good apartments
  // If k <= n/3, we can arrange them to maximize good apartments (each occupied covers 2 others)
  // Otherwise, we run out of space to cover all with 2 per occupied
  long M = (k <= n / 3) ? (2 * k) : (n - k);
  printf("%ld %ld\n", m, M);
  return 0;
}


// https://github.com/VaHiX/CodeForces/