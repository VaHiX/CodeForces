// Problem: CF 1784 A - Monsters (easy version)
// https://codeforces.com/contest/1784/problem/A

/*
A. Monsters (easy version)
Algorithms/Techniques: Sorting, Greedy
Time Complexity: O(n log n) due to sorting, where n is the number of monsters
Space Complexity: O(n) for storing the health points

This problem involves finding the minimum number of type-1 spells needed 
to kill all monsters, given that we can cast at most one type-2 spell.
The key insight is:
- A type-2 spell deals 1 damage to all alive monsters and repeats if any monster dies
- We want to minimize the number of type-1 spells
- Sorting helps us process monsters in order to optimize damage distribution
*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> h(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &h[p]);
    }
    sort(h.begin(), h.end());  // Sort monsters by health to process in order
    ll cnt(0);  // Count of type-1 spells needed
    for (long p = 0; p < n; p++) {
      long prev = (p ? h[p - 1] : 0);  // Previous monster's health after processing
      if (h[p] > prev + 1) {  // If current monster needs more than 1 damage from previous to be reduced by 1
        cnt += h[p] - (prev + 1);  // Add required type-1 spells for this gap
        h[p] = prev + 1;  // Simulate the effect of applying type-2 spells on current monster's health
      }
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/