// Problem: CF 1923 C - Find B
// https://codeforces.com/contest/1923/problem/C

/*
C. Find B
time limit per test3 seconds
memory limit per test256 megabytes

Algorithm: Prefix Sums with Optimization
- For each query, we determine if a subarray is "good" by checking:
  - The total sum of elements in the subarray.
  - The count of ones in the subarray.
  - A key condition for a subarray to be good is that there must exist another array of same sum,
    where no element is equal to its original counterpart, and all elements are positive.

  We use prefix sums:
    cs[p] = sum of elements from index 1 to p
    cz[p] = count of 1s from index 1 to p

  For a subarray [left, right]:
    len = right - left + 1 (length)
    total = cs[right] - cs[left-1] (sum of subarray)
    ones = cz[right] - cz[left-1] (count of 1s in subarray)

    A subarray is good if:
      len > 1 AND total >= ones + len

  Time Complexity: O(n + q) per test case
  Space Complexity: O(n)
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    std::vector<ll> cs(n + 1), cz(n + 1, 0); // prefix sums for values and count of ones
    for (ll p = 1; p <= n; p++) {
      ll x;
      scanf("%lld", &x);
      cs[p] = cs[p - 1] + x;        // cumulative sum
      cz[p] = cz[p - 1] + (x == 1);  // count of ones up to index p
    }
    while (q--) {
      ll left, right;
      scanf("%lld %lld", &left, &right);
      ll len = right - left + 1;
      ll total = cs[right] - cs[left - 1];
      ll ones = cz[right] - cz[left - 1];
      puts(((len > 1) && (total >= ones + len)) ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/