// Problem: CF 1251 D - Salary Changing
// https://codeforces.com/contest/1251/problem/D

/*
D. Salary Changing
Algorithm: Binary search on the answer + Greedy selection of salaries
Time Complexity: O(n * log(max_range) * log(n)) where max_range is up to 10^9
Space Complexity: O(n)

The problem involves maximizing the median salary among n employees (n is odd).
We use binary search on the possible median value.
For each candidate median:
- We greedily assign as low as possible to elements less than the median,
- Assign maximum allowed to elements greater than or equal to median.
- Use prefix sums and sorting for efficient calculation of minimum required
  amount when setting a specific median.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#pragma GCC optimize("O2")
#define ll long long
#define mod 1000000007LL
#define eps 1e-8
using namespace std;

int main() {
  cin.tie(0), ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    ll s;
    cin >> n >> s;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
      cin >> a[i] >> b[i], s -= a[i]; // Deduct minimum salaries from total budget
    ll l = *min_element(a.begin(), a.end()), // Lower bound of possible median
       r = *max_element(b.begin(), b.end()), m;
    while (l < r) {
      m = (l + r + 1) >> 1; // Midpoint for binary search (upper mid to avoid infinite loop)
      vector<ll> tmp;      // To store excess amounts needed for elements in range [a[i], m)
      int c = n / 2 + 1;   // Number of elements >= median that need to be selected (to satisfy median condition)

      for (int i = 0; i < n; i++) {
        if (a[i] < m && b[i] >= m)
          tmp.push_back(m - a[i]); // Amount needed to raise low element to at least m
        else if (a[i] >= m)
          c--; // This element already satisfies the condition, so reduce count
      }

      sort(tmp.begin(), tmp.end()); // Sort excess values to pick minimum required

      // Check if total money sufficient to make it possible to have median = m
      if (c <= 0 || (tmp.size() >= c && 
                     accumulate(tmp.begin(), tmp.begin() + c, 0ll) <= s))
        l = m;  // Accept this median value
      else
        r = m - 1; // Reject and try smaller median
    }
    cout << l << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/