// Problem: CF 898 E - Squares and not squares
// https://codeforces.com/contest/898/problem/E

/*
 * Problem: E. Squares and not squares
 * 
 * Purpose: Given n piles of candies (n is even), we want to make exactly n/2 piles
 *          contain a square number of candies and n/2 piles not containing square numbers.
 *          We can add or remove one candy from any pile in one move.
 * 
 * Algorithm:
 * 1. Precompute all square numbers up to 2e9 using a set for fast lookup.
 * 2. For each pile:
 *    - Determine if the current amount is a square number.
 *    - Count how many piles are already square (nsq) and how many are zero (nz).
 * 3. Based on current distribution:
 *    - If too many are square: Calculate minimum moves to convert some to non-square.
 *    - If too few are square: Find cheapest moves to convert non-square piles to square.
 * 
 * Time Complexity: O(n * sqrt(max_a) + n log n)
 * Space Complexity: O(n + sqrt(max_a)) = O(n)
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {
  const ll N = 2e9;
  std::set<ll> s;
  // Precompute all square numbers up to 2*10^9
  for (ll p = 0; p * p <= N; p++) {
    s.insert(p * p);
  }
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  ll nsq(0), nz(0);
  std::vector<bool> vsq(n);
  for (ll p = 0; p < n; p++) {
    vsq[p] = s.count(a[p]); // Check if current pile size is a perfect square
    nsq += vsq[p];
    nz += (a[p] == 0);
  }
  ll cnt(0);
  if (nsq > n / 2) {
    // Too many square piles; convert some to non-square
    ll nonsq = n - nsq;
    ll diff = nsq - n / 2;
    ll nonzero = nsq - nz;
    cnt = diff + (diff - nonzero) * (diff > nonzero);
  } else if (nsq < n / 2) {
    // Too few square piles; convert some to square
    std::vector<ll> moves;
    ll diff = n / 2 - nsq;
    for (ll p = 0; p < n; p++) {
      if (vsq[p]) {
        continue; // Skip if already a square
      }
      ll sr = sqrt(a[p]); // Find the floor of sqrt of current pile size
      ll diff1 = a[p] - sr * sr; // Cost to go down to perfect square below
      ll diff2 = (sr + 1) * (sr + 1) - a[p]; // Cost to go up to next perfect square
      moves.push_back(diff1 < diff2 ? diff1 : diff2); // Take minimum cost
    }
    sort(moves.begin(), moves.end()); // Sort to get cheapest conversions first
    for (ll p = 0; p < diff; p++) {
      cnt += moves[p];
    }
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/