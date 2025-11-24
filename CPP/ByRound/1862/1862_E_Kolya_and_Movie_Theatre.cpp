// Problem: CF 1862 E - Kolya and Movie Theatre
// https://codeforces.com/contest/1862/problem/E

/*
E. Kolya and Movie Theatre

Algorithm: Sliding window with multiset to maintain the best m movies visited so far.
Key technique: Use a sliding window approach with a multiset to efficiently track the maximum sum of 
               entertainment values while ensuring at most m movies are selected.

Time Complexity: O(n log m) per test case, where n is the number of days and m is the maximum number of movies Kolya can attend.
Space Complexity: O(m) for storing the multiset.

The approach uses a greedy method with a sliding window:
- For each day i, we consider whether including the movie on that day is beneficial.
- We maintain a multiset of the last m entertainment values (in descending order).
- When adding a new movie, if the size exceeds m, we remove the smallest value to keep only the top m.
- The score for a visit on day i is calculated as: sum of selected movie values minus d * number of days since last visit.
- This is done by tracking the cumulative sum and adjusting for the decreasing value effect over time.

*/

#include <cstdio>
#include <set>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m, d;
    scanf("%lld %lld %lld", &n, &m, &d);
    std::multiset<ll> w; // multiset to maintain the top m entertainment values seen so far
    ll cur(0), mx(0);    // cur: current sum of selected movies, mx: maximum score found so far

    for (ll p = 1; p <= n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x < 0) {
        continue; // skip non-positive entertainment values
      }

      cur += x;           // add current movie's value to the running sum
      w.insert(x);        // insert into multiset

      // if we've selected more than m movies, remove the smallest one
      if (w.size() > m) {
        cur -= *w.begin();  // subtract the smallest value from the sum
        w.erase(w.begin()); // remove it from the set
      }

      // calculate score for visiting on day p
      // total = (sum of selected movies) - (days since last visit) * d
      ll score = cur - p * d;
      mx = (mx > score) ? mx : score; // update max score
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/