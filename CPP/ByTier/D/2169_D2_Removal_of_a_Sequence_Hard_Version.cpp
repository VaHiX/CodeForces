// Problem: CF 2169 D2 - Removal of a Sequence (Hard Version)
// https://codeforces.com/contest/2169/problem/D2

/*
Algorithm/Techniques: Binary search with mathematical optimization
Time Complexity: O(x * log(N)) where N = 1e12, due to the binary search and operations on x
Space Complexity: O(1), only using a few variables for computation

The problem involves repeatedly removing elements from a sequence at positions y, 2*y, 3*y, etc.
The key idea is to simulate or predict how many elements will be removed in each step,
and determine the k-th remaining element efficiently.
We use binary search and mathematical relations to fast-track the process.
*/

#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
const ll N = 1e12;
ll x, y, k;
int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    scanf("%lld%lld%lld", &x, &y, &k);
    ll l = 1, r = N + 1;
    if (y == 1) {
      puts("-1");
      continue;
    }
    if (k < y) {
      printf("%lld\n", k);
      continue;
    }
    double f = (double)(y) / (y - 1);
    while (x && k <= N) {
      ll q = k / y;
      if ((k + q) / y == q) {
        // When k is not affected by the next operation in a straightforward way
        ll t = (y - k % y - 1) / q;
        t = min(t, x);
        k += q * t;
        x -= t;
      } else {
        // Use approximation to compute new k efficiently
        ll _k = k * f;
        while (_k - _k / y < k)
          _k++;
        while (_k > 1 && (_k - 1) - (_k - 1) / y >= k)
          _k--;
        k = _k;
        x--;
      }
    }
    if (k > N)
      k = -1;
    printf("%lld\n", k);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/