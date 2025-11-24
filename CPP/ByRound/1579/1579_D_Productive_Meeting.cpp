// Problem: CF 1579 D - Productive Meeting
// https://codeforces.com/contest/1579/problem/D

/*
Algorithm: Greedy approach using a set to manage people based on their sociability.
Approach:
- Use a set to store pairs of (sociability, person_id) to always get the two people with highest sociability.
- In each step, pick the two people with highest remaining sociability, have them talk (decrease their sociability by 1), and put them back if they still have sociability left.
- Continue until only one person remains or the set is empty.
- This ensures maximum number of talks because we're always pairing the most sociable people available.

Time Complexity: O(n * log n) per test case due to set operations (insert, erase, and access).
Space Complexity: O(n) for storing the set and result vector.

Techniques: 
- Set data structure for maintaining sorted order of sociability values.
- Greedy strategy to always pair the most sociable individuals.
*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#include <iterator>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<std::pair<long, long>> s;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > 0) {
        s.insert(std::make_pair(x, p + 1));  // Insert only if sociability > 0
      }
    }
    std::vector<std::pair<long, long>> res;
    while (s.size() > 1) {
      std::pair<long, long> a = *s.rbegin();  // Get the person with highest sociability
      s.erase(a);                             // Remove from set
      std::pair<long, long> b = *s.rbegin();  // Get the next highest
      s.erase(b);                             // Remove from set
      res.push_back(std::make_pair(a.second, b.second));  // Record the talk
      --a.first;  // Decrease sociability
      --b.first;
      if (a.first > 0) {
        s.insert(a);  // Put back if still has sociability
      }
      if (b.first > 0) {
        s.insert(b);
      }
    }
    printf("%ld\n", res.size());
    for (long p = 0; p < res.size(); p++) {
      printf("%ld %ld\n", res[p].first, res[p].second);
    }
  }
}


// https://github.com/VaHiX/CodeForces/