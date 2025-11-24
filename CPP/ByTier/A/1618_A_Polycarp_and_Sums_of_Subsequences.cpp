// Problem: CF 1618 A - Polycarp and Sums of Subsequences
// https://codeforces.com/contest/1618/problem/A

/*
 * Problem: Polycarp and Sums of Subsequences
 * 
 * Purpose: Given a sorted array of 7 integers representing all non-empty 
 *          subsequence sums of a 3-element array, reconstruct the original array.
 * 
 * Algorithm:
 *   - The smallest element in the sorted subsequence sums is the smallest element of the array.
 *   - The second smallest element is the second element of the array.
 *   - The largest element is the sum of all three elements.
 *   - The third element can be derived as: total_sum - a[0] - a[1].
 * 
 * Time Complexity: O(1) per test case, since we always process exactly 7 elements.
 * Space Complexity: O(1), only using a fixed-size vector.
 */

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const int N = 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<ll> a(N);
    for (int p = 0; p < N; p++) {
      scanf("%lld", &a[p]);
    }
    // a[0] is the smallest element
    // a[1] is the second smallest element  
    // a[6] is the sum of all three elements
    // a[2] = a[6] - a[0] - a[1]
    printf("%lld %lld %lld\n", a[0], a[1], a.back() - a[0] - a[1]);
  }
}


// https://github.com/VaHiX/CodeForces/