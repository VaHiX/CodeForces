// Problem: CF 1015 C - Songs Compression
// https://codeforces.com/contest/1015/problem/C

/*
C. Songs Compression
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task: Find the minimum number of songs to compress so that all songs fit on a flash drive of capacity m.
Algorithm: Greedy approach with sorting.
- First check if it's possible at all (even with full compression).
- Then use greedy strategy: sort by compression gain (a_i - b_i) in descending order,
  and keep compressing until the total fits.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing differences

Input:
- n songs, m flash drive capacity
- For each song: original size a_i, compressed size b_i

Output:
- Minimum number of songs to compress, or -1 if impossible
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  ll sa(0), td(0); // sa: sum of original sizes, td: sum of compression gains
  std::vector<ll> d(n);
  for (ll p = 0; p < n; p++) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    sa += a;         // accumulate total original size
    td += (a - b);   // accumulate total compression gain
    d[p] = a - b;    // store individual compression gains
  }
  if (sa <= m) {
    puts("0");       // no compression needed if already fits
    return 0;
  } else if (m < sa - td) {
    puts("-1");      // impossible even with full compression
    return 0;
  } else {
    sort(d.rbegin(), d.rend()); // sort compression gains in descending order
    ll cnt(0);
    for (ll p = 0; p < n; p++) {
      sa -= d[p];    // subtract the compression gain from total size
      if (sa <= m) { // if new total fits
        cnt = p + 1; // number of songs compressed
        break;
      }
    }
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/