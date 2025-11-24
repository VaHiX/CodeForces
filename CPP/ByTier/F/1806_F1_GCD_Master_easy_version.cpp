// Problem: CF 1806 F1 - GCD Master (easy version)
// https://codeforces.com/contest/1806/problem/F1

/*
Algorithm: GCD Master (Easy Version)
Purpose: To find the maximum possible sum of the array after exactly k operations,
where each operation takes two elements, computes their GCD, and appends it to the array.

Approach:
1. For each element in the input array, we count its occurrences.
2. If an element appears more than once, we store it in a separate array 'b'.
3. Using a sieve-like technique, we compute for each possible GCD value i,
   what is the maximum possible sum we can get by taking elements whose GCD is at least i.
4. Then, we greedily try out combinations of taking elements from 'b' (which were duplicates) 
   to maximize the total sum.

Time Complexity: O(m * log(m) + n * log(n)) - due to sorting and iterating over divisors for each element.
Space Complexity: O(m + n) - for arrays 'cnt', 'b', and 'ans'.

Techniques Used:
- Frequency counting
- Sieve-like processing of divisors
- Greedy selection with prefix optimization
*/

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int T, n, m, k, tot, a[N], b[N], cnt[N];
ll sum, res, ans[N];

inline void solve() {
  cin >> n >> m >> k;
  tot = sum = 0;
  for (int i = 0; i <= n; ++i) {
    ans[i] = 0;
  }
  for (int i = 1; i <= m; ++i) {
    cnt[i] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum += a[i], ++cnt[a[i]];
    if (cnt[a[i]] > 1) {
      b[++tot] = a[i];
    }
  }
  sort(b + 1, b + tot + 1); // Sorting the duplicate elements to process them in order

  // For each potential GCD value i, compute the best possible contribution to ans[p]
  for (int i = 1; i <= m; ++i) {
    ll p = -1, q = 0;
    for (int j = i; j <= m; j += i) {
      if (cnt[j]) {
        ++p, q += j;
        ans[p] = max(ans[p], sum - q + i); // Update best sum if current combination is better
      }
    }
  }

  // Use prefix sums to evaluate different numbers of operations and find maximum
  sum = res = 0;
  for (int i = 0; i <= min(k, tot); ++i) {
    res = max(res, sum + ans[k - i]);
    sum -= b[i + 1]; // subtracting elements considered in greedy selection
  }
  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/