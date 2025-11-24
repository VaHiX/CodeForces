// Problem: CF 1869 D1 - Candy Party (Easy Version)
// https://codeforces.com/contest/1869/problem/D1

/*
Purpose: This code solves the problem of determining whether it's possible to redistribute candies among people at a party such that everyone ends up with the same number of candies, following specific swap rules.

Algorithm:
- Check if total candies can be evenly distributed among all people.
- For each person, calculate how many candies they need to give or receive to reach the average.
- Use bit manipulation and binary representation to determine if the distribution is valid.
- For each difference, check if it can be represented as a power of 2 or sum of powers of 2.
- Track the net change in bit counts to ensure all changes balance out.

Time Complexity: O(n * log(max(a_i))) where n is number of people and max(a_i) is the maximum candy count.
Space Complexity: O(1) as we use a fixed-size vector of size 32 regardless of input size.
*/

#include <bits/std_abs.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define fore(i, l, r) for (int i = (int)(l); i < (int)(r); ++i)
#define fi first
#define se second
#define endl '\n'
#define lowbit(x) ((x) & (-x))
const int INF = 0x3f3f3f3f;
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
typedef long long ll;

bool solve() {
  int n;
  std::cin >> n;
  std::vector<int> a(n + 1);
  ll sum = 0;
  fore(i, 1, n + 1) {
    std::cin >> a[i];
    sum += a[i];
  }
  
  // If total candies cannot be evenly divided, return false
  if (sum % n != 0)
    return false;
    
  // Vector to count bit differences
  std::vector<int> bit(32, 0);
  int x = sum / n; // Target number of candies per person
  
  fore(i, 1, n + 1) {
    if (x == a[i])
      continue;
      
    int d = std::abs(x - a[i]); // Difference from target
    
    // Check if the difference can be expressed as a power of 2 plus its lowbit
    // This condition ensures that we can achieve the final state through valid swaps
    if (__builtin_popcount(d + lowbit(d)) == 1) {
      if (x > a[i]) {
        // Person needs to receive candies
        --bit[std::__lg(lowbit(d))];      // Reduce count of this power of 2
        ++bit[std::__lg(d + lowbit(d))];  // Increase count of the complement power of 2
      } else {
        // Person needs to give away candies  
        --bit[std::__lg(d + lowbit(d))];  // Reduce count of this power of 2
        ++bit[std::__lg(lowbit(d))];      // Increase count of the complement power of 2
      }
    } else {
      // If difference cannot be expressed in the required form, return false
      return false;
    }
  }
  
  // If all bit counts are zero, a valid distribution exists
  fore(i, 0, 32) if (bit[i]) return false;
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    std::cout << (solve() ? "YES" : "NO") << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/