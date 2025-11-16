// Problem: CF 884 D - Boxes And Balls
// https://codeforces.com/contest/884/problem/D

#include <cstdio>
#include <set>
typedef long long ll;

/*
 * Problem: Distribute balls into boxes such that each box contains only balls of one color.
 * Goal: Minimize the total penalty, where penalty is the sum of balls taken in each turn.
 * 
 * Algorithm:
 * - Use a greedy approach with a multiset to always combine the three smallest piles.
 * - At each step, extract the three smallest elements from the multiset, sum them, and insert back.
 * - This mimics a Huffman-like tree construction to minimize total cost.
 * 
 * Time Complexity: O(n log n) due to multiset operations (insert, erase, find).
 * Space Complexity: O(n) for storing the elements in the multiset.
 */

int main() {
  long n;
  scanf("%ld", &n);
  std::multiset<ll> s;
  for (long p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    s.insert(x);  // Insert each ball count into multiset
  }
  
  // If number of elements is even, insert a dummy zero to make it odd
  // This ensures we can always group into triplets until the last two elements remain
  if (s.size() % 2 == 0) {
    s.insert(0);
  }
  
  ll penalty(0);
  // Continue combining smallest elements until only 2 elements remain
  while (s.size() > 2) {
    ll x = *(s.begin());  // Get smallest
    s.erase(s.begin());
    ll y = *(s.begin());  // Get second smallest
    s.erase(s.begin());
    ll z = *(s.begin());  // Get third smallest
    s.erase(s.begin());
    
    penalty += (x + y + z);  // Accumulate penalty
    s.insert(x + y + z);     // Insert the merged pile back
  }
  
  printf("%lld\n", penalty);
  return 0;
}

// https://github.com/VaHiX/CodeForces/