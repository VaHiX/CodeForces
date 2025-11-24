// Problem: CF 1223 C - Save the Nature
// https://codeforces.com/contest/1223/problem/C

/*
 * Problem: Save the Nature
 * 
 * Task: Given n tickets with prices, and two ecological programs that apply to every 'a'-th and 'b'-th ticket sold,
 *       determine the minimum number of tickets to sell such that total contribution reaches at least k.
 *       Each program contributes x% and y% respectively, and if both apply, it's x+y%.
 * 
 * Algorithm:
 * - Binary search on the answer (number of tickets to sell)
 * - For each candidate number, use a greedy strategy to maximize contribution:
 *   - Sort tickets in descending order
 *   - Assign tickets to programs optimally to maximize sum
 * - Use inclusion-exclusion principle for LCM calculation
 * 
 * Time Complexity: O(n log n + q * n * log(max_n))
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// Helper function to compute GCD
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

// Check if we can achieve at least k contribution with 'num' tickets
bool check(const std::vector<ll> v, ll num, ll x, ll a, ll y, ll b, ll lcm, ll k) {
  ll both = num / lcm;                 // Count of tickets benefiting from both programs
  ll fc = (num / a) - both;            // Count of tickets benefiting only first program
  ll sc = (num / b) - both;            // Count of tickets benefiting only second program
  ll total(0);
  
  // Greedily assign tickets to maximize contribution
  for (ll p = 0; p < num; p++) {
    if (both > 0) {
      // If the ticket benefits both programs, apply combined percentage
      total += v[p] * (x + y) / 100;
      --both;
    } else if (fc > 0) {
      // Otherwise apply first program's percentage
      total += v[p] * x / 100;
      --fc;
    } else if (sc > 0) {
      // Otherwise apply second program's percentage
      total += v[p] * y / 100;
      --sc;
    }
  }
  
  return (total >= k);
}

int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    
    // Read input parameters
    ll x, a, y, b, k;
    scanf("%lld %lld %lld %lld %lld", &x, &a, &y, &b, &k);
    
    // Normalize to ensure x >= y for easier handling
    if (x < y) {
      ll t = x;
      x = y;
      y = t;
      t = a;
      a = b;
      b = t;
    }
    
    // Compute LCM of a and b using GCD
    ll g = gcd(a, b);
    ll lcm = a * b / g;
    
    // Sort tickets in descending order for greedy selection
    sort(v.rbegin(), v.rend());
    
    // Binary search on the number of tickets to sell
    ll left(1), right(n), res(-1);
    while (left <= right) {
      ll mid = (left + right) / 2;
      if (check(v, mid, x, a, y, b, lcm, k)) {
        res = mid;           // Found valid answer
        right = mid - 1;     // Try to minimize the number of tickets
      } else {
        left = mid + 1;      // Need more tickets
      }
    }
    
    printf("%lld\n", (res > 0) ? res : -1);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/