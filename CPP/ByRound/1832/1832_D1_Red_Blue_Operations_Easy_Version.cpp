// Problem: CF 1832 D1 - Red-Blue Operations (Easy Version)
// https://codeforces.com/contest/1832/problem/D1

/*
Purpose: This code solves the "Red-Blue Operations" problem where we have an
array of integers, initially all red. We perform k operations on the array,
where during the i-th operation, we select an element:
         - if red, it increases by i and becomes blue;
         - if blue, it decreases by i and becomes red.
         The goal is to determine the maximum possible minimum value in the
array after exactly k operations.

Algorithms/Techniques:
- Preprocessing with prefix and suffix arrays
- Mathematical analysis for different cases of k relative to n
- Binary search or direct calculation depending on k's relationship with n

Time Complexity: O(n log n + q), dominated by sorting and processing q queries
Space Complexity: O(n), for storing prefix and suffix minimums

*/
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <random>
#include <utility>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T> using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
clock_t startTime;
double getCurrentTime() {
  return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
const ll INF = (ll)1e16;
const int N = 200200;
ll a[N];
ll minPref[N], minSuf[N];
int n;
int main() {
  startTime = clock();
  int q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  sort(a, a + n);
  minPref[0] = INF;
  for (int i = 0; i < n; i++) {
    minPref[i + 1] = min(
        minPref[i], a[i] - i); // Precompute prefix minimums adjusted by index
  }
  minSuf[n] = INF;
  for (int i = n - 1; i >= 0; i--) {
    minSuf[i] = min(minSuf[i + 1], a[i]); // Precompute suffix minimums
  }
  ll S = 0;
  for (int i = 0; i < n; i++)
    S += a[i] - i; // Compute total sum adjusted by indices
  while (q--) {
    ll k;
    scanf("%lld", &k);
    if (k < n) {
      // When k is less than n, we can directly use prefix and suffix arrays
      printf("%lld ", min(minPref[k] + k, minSuf[k]));
    } else if ((k - n) % 2 == 0) {
      // When k - n is even, all operations are balanced
      ll m = minPref[n] + k;
      ll s = S + k * n - (k - n) / 2;
      if (s < 0)
        s = (s - n + 1) / n;
      else
        s = s / n;
      printf("%lld ", min(m, s));
    } else {
      // When k - n is odd, adjust calculations
      ll m = min(minPref[n - 1] + k, a[n - 1]);
      ll s = S + k * (n - 1) + (n - 1) - (k - n + 1) / 2;
      if (s < 0)
        s = (s - n + 1) / n;
      else
        s = s / n;
      printf("%lld ", min(m, s));
    }
  }
  printf("\n");
  return 0;
}

// https://github.com/VaHiX/CodeForces/