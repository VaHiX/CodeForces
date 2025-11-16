// Problem: CF 1972 D2 - Reverse Card (Hard Version)
// https://codeforces.com/contest/1972/problem/D2

/*
Algorithm: Number Theoretic Approach with GCD Optimization
Approach:
- The condition is b * gcd(a, b) is divisible by (a + b)
- Rearranging: b * gcd(a, b) ≡ 0 (mod a + b)
- If we let g = gcd(a, b), then a = g * i, b = g * j with gcd(i, j) = 1
- Substituting: g * j * g = k * (g * i + g * j) = k * g * (i + j)
- Simplifying: j * g = k * (i + j)
- So: g = k * (i + j) / j, where k must be divisible by j to make g integer.
- We iterate over all coprime pairs (i, j) and count valid (a, b) pairs using the formula:
  count = min(n / (i + j) / i, m / (i + j) / j)

Time Complexity: O(n^(3/2)) amortized due to nested loops and gcd checking
Space Complexity: O(1) - only using a few variables for computation

*/
#include <stddef.h>
#include <ext/pb_ds/detail/type_utils.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
using namespace __gnu_pbds;
#define ordered_set                                                            \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
       tree_order_statistics_node_update>
#define ordered_setpair                                                        \
  tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,           \
       tree_order_statistics_node_update>
#define FAST                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define sp fixed << setprecision
#define ld long double
#define ll long long
#define PI acos(-1)
#define all(x) (x).begin(), (x).end()
#define fr(a, b) for (int i = a; i < b; i++)
#define rfr(a, b) for (int i = a; i >= b; i--)
#define rep(i, a, b) for (int i = a; i < b; i++)
ll mod = 1e9 + 7;
ll power(ll a, ll b) {
  ll ans = 1ll;
  while (b > 0) {
    if (b & 1)
      ans = (ans * a);
    b = b >> 1;
    a = (a * a);
  }
  return ans;
}
ll powerm(ll a, ll b) {
  ll ans = 1ll;
  while (b > 0) {
    if (b & 1)
      ans = (ans * a) % mod;
    b = b >> 1;
    a = (a * a) % mod;
  }
  return ans;
}
void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}
struct range {
  int left, right, index;
  bool operator<(const range &other) const {
    if (left == other.left)
      return right > other.right;
    return left < other.left;
  }
};
int main() {
  FAST ll tc;
  cin >> tc;
  while (tc--) {
    ll ans = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i * i <= n; i++) {
      for (int j = 1; (i + j) * i <= n && (i + j) * j <= m; j++) {
        if (gcd(i, j) == 1) {
          ans += min(n / (i + j) / i, m / (i + j) / j); // Count valid (a,b) pairs for coprime (i,j)
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/