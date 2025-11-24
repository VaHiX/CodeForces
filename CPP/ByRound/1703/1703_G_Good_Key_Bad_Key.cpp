// Problem: CF 1703 G - Good Key, Bad Key
// https://codeforces.com/contest/1703/problem/G

#include <cstdio>
#include <vector>
typedef long long ll;

/*
G. Good Key, Bad Key

Algorithm:
This problem uses a greedy approach combined with precomputation to decide whether to use a good key or a bad key for each chest.
For each chest, we compute the benefit of using a bad key (by simulating its effect on up to 31 subsequent chests), and compare it to the cost of buying a good key.
The idea is to iterate through all possible positions where a bad key could be used and calculate the optimal balance after opening all chests.

Time Complexity: O(n * log n) - where n is the number of chests (log n due to halving operations up to 31 times).
Space Complexity: O(n) - for storing the input array and temporary variables.

*/

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> a(n, 0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll goodsum(0), maxsum(0);
    for (ll p = 0; p <= n; p++) {
      ll badsum(0);
      // For each possible position, simulate the effect of a bad key on up to 31 future chests
      for (ll u = 0; p + u < n && u < 31; u++) {
        badsum += (a[p + u] / (2 << u)); // Use bit shifting to represent power of 2: 2^u
      }
      ll total = goodsum + badsum;
      maxsum = (maxsum > total ? maxsum : total);
      if (p == n) {
        continue;
      }
      goodsum += (a[p] - k); // Add coins from current chest and subtract cost of key used to open it
    }
    printf("%lld\n", maxsum);
  }
}


// https://github.com/VaHiX/codeForces/