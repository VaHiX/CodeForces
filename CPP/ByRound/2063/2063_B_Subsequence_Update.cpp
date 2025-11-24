// Problem: CF 2063 B - Subsequence Update
// https://codeforces.com/contest/2063/problem/B

/*
B. Subsequence Update
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing vectors

Problem Description:
Given a sequence of integers and a segment [l, r], we are allowed to reverse any subsequence once.
We want to minimize the sum of elements in the segment [l, r] after the operation.

Approach:
1. Separate elements into three groups based on their positions:
   - Elements before l (vl)
   - Elements in segment [l, r] (vs)
   - Elements after r (vr)
2. Sort:
   - vl in ascending order
   - vr in ascending order
   - vs in descending order
3. Try to improve the sum by swapping smaller values from vl with larger values in vs,
   and similarly from vr with vs.
4. Choose the better improvement (smaller diffA or diffB) and subtract it from original sum.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, l, r;
    scanf("%ld %ld %ld", &n, &l, &r);
    std::vector<long> vl, vs, vr;
    ll sum(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (p < l) {                    // Elements before segment [l,r] go to vl
        vl.push_back(x);
      } else if (p <= r) {             // Elements in segment [l,r] go to vs
        vs.push_back(x);
        sum += x;                     // Add to total sum of segment [l,r]
      } else {                         // Elements after segment [l,r] go to vr
        vr.push_back(x);
      }
    }
    sort(vl.begin(), vl.end());       // Sort left part ascending for greedy swap
    sort(vr.begin(), vr.end());       // Sort right part ascending for greedy swap
    sort(vs.rbegin(), vs.rend());     // Sort middle part descending to get large values first
    
    ll diffA(0);
    for (long p = 0; p < vl.size() && p < vs.size(); p++) {
      if (vl[p] < vs[p]) {
        diffA += vl[p] - vs[p];       // Potential gain from swapping
      } else {
        break;                        // No benefit if element in vl >= element in vs
      }
    }

    ll diffB(0);
    for (long p = 0; p < vr.size() && p < vs.size(); p++) {
      if (vr[p] < vs[p]) {
        diffB += vr[p] - vs[p];       // Potential gain from swapping
      } else {
        break;                        // No benefit if element in vr >= element in vs
      }
    }

    printf("%lld\n", sum + (diffA < diffB ? diffA : diffB));  // Output minimum possible sum
  }
}


// https://github.com/VaHiX/codeForces/