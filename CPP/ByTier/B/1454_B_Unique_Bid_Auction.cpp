// Problem: CF 1454 B - Unique Bid Auction
// https://codeforces.com/contest/1454/problem/B

/*
B. Unique Bid Auction
Algorithm: Use a map to track unique bids and a set to track duplicates.
For each bid:
  - If already exists in map, remove from map and add to duplicates.
  - If not in duplicates, add to map with its index.
At the end, if map is not empty, return the index of the smallest bid.
Time Complexity: O(n log n) per test case due to map operations.
Space Complexity: O(n) for storing bids and duplicates.
*/

#include <cstdio>
#include <map>
#include <set>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> bids; // Maps bid value to participant index
    std::set<long> dupes;      // Tracks duplicate bid values
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (bids.count(x)) {
        // If bid already exists, remove it from bids and mark as duplicate
        bids.erase(x);
        dupes.insert(x);
      } else if (!dupes.count(x)) {
        // If not a duplicate, add to bids with its index
        bids[x] = p;
      }
    }
    // Print the index of the smallest unique bid, or -1 if none exist
    printf("%ld\n", bids.size() ? bids.begin()->second : -1);
  }
}


// https://github.com/VaHiX/codeForces/