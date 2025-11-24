// Problem: CF 1428 E - Carrots for Rabbits
// https://codeforces.com/contest/1428/problem/E

/*
E. Carrots for Rabbits
Algorithm: Greedy with a priority queue (set) to always distribute the carrot that gives maximum improvement in total time.
Time Complexity: O(n log n + k log n), where n is number of carrots and k is number of rabbits.
Space Complexity: O(n), for storing carrot lengths and set.

This solution uses a greedy approach:
1. Initially, all carrots are divided into 1 piece (the whole carrot).
2. We use a set to always select the carrot that when split into one more piece,
   would give the maximum reduction in total eating time.
3. The improvement for splitting a carrot of length L into (ps[p]+1) pieces
   is calculated using a helper function.
4. We repeat this process until we have k pieces total.
*/

#include <cstdio>
#include <set>
#include <vector>
#include <utility>

typedef long long ll;

// Calculate the improvement in total time when splitting a carrot of length 'total'
// into 'num' pieces instead of 'num-1' pieces
ll bestTime(ll total, ll num) {
  ll div = total / num;
  ll rem = total % num;
  ll nrem = num - total % num;
  ll res = nrem * div * div + rem * (div + 1) * (div + 1);
  return res;
}

int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::set<std::pair<ll, ll>> s; // Set to store {improvement, index of carrot}
  std::vector<ll> len(n, 0), ps(n, 1); // len: original lengths, ps: number of pieces per carrot
  ll ans(0);
  
  // Initialize with each carrot as one piece and calculate initial total time
  for (long p = 0; p < n; p++) {
    scanf("%lld", &len[p]);
    ans += len[p] * len[p]; // Add square of current length to total time cost
    s.insert(std::make_pair(
        bestTime(len[p], ps[p] + 1) - bestTime(len[p], ps[p]), p)); // Insert initial improvement
  }
  
  // Distribute remaining pieces (k - n pieces)
  for (long p = 0; p < k - n; p++) {
    std::pair<ll, ll> elem = *s.begin(); // Get the carrot with max improvement
    ll improvement = elem.first;
    ll which = elem.second;
    ans += improvement; // Add improvement to total time
    ++ps[which]; // Increment number of pieces for this carrot
    
    s.erase(s.begin()); // Remove old element from set
    
    // Insert updated improvement for this carrot after splitting it once more
    s.insert(std::make_pair(bestTime(len[which], ps[which] + 1) -
                                bestTime(len[which], ps[which]),
                            which));
  }
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/