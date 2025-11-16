// Problem: CF 1093 C - Mishka and the Last Exam
// https://codeforces.com/contest/1093/problem/C

/*
 * Problem: Mishka and the Last Exam
 * Purpose: Restore a non-decreasing sequence 'a' from a given sequence 'b' where b[i] = a[i] + a[n-i-1].
 * Algorithm: Greedy approach.
 *            - For each pair of elements (a[i], a[n-i-1]) in the sequence,
 *              we assign the smallest possible value to a[i] such that the sum equals b[i].
 *              Then, a[n-i-1] is determined.
 *            - Maintain left and right bounds to ensure non-decreasing property.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n, 0);
  // Initialize bounds for the next element to be assigned
  ll left(0), right(1e18);
  // Iterate over pairs of elements from both ends of the array
  for (ll p = 0; 2 * p < n; p++) {
    ll b;
    scanf("%lld", &b);
    // Assign a[p] to the minimum valid value that maintains non-decreasing order
    a[p] = (b - left <= right) ? left : (b - right);
    // Compute the corresponding element at the mirrored index
    a[n - 1 - p] = b - a[p];
    // Update bounds for the next iteration
    left = a[p];
    right = a[n - 1 - p];
  }
  // Output the reconstructed sequence
  for (ll p = 0; p < n; p++) {
    printf("%lld ", a[p]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/