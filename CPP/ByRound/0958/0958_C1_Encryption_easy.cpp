// Problem: CF 958 C1 - Encryption (easy)
// https://codeforces.com/contest/958/problem/C1

#include <cstdio>
#include <vector>
typedef long long ll;

/*
 * Problem: Maximize the sum of scores of two contiguous non-overlapping subarrays.
 * 
 * Algorithm:
 * - Precompute prefix sums to quickly calculate sum of any subarray.
 * - For each valid split point, compute the score of the first part and the second part.
 * - The score of a part is the sum of its elements modulo p.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 *
 * Techniques:
 * - Prefix sum optimization
 * - Single pass over the array to compute optimal split
 */

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  ll cs(0);  // cumulative sum of elements
  std::vector<ll> a(n), b(n);  // a is input array, b is prefix sum array
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
    cs += a[p];
    b[p] = cs;  // b[p] holds sum of elements from index 0 to p
  }
  ll mx(0);  // maximum score found so far
  for (long p = 0; p < n - 1; p++) {
    // Compute score of first part (0 to p) + score of second part (p+1 to n-1)
    ll test = b[p] % m + (cs - b[p]) % m;
    mx = (mx > test) ? mx : test;
  }
  printf("%lld\n", mx);
  return 0;
}

// https://github.com/VaHiX/CodeForces/