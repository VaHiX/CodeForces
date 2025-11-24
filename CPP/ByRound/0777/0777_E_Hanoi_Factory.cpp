// Problem: CF 777 E - Hanoi Factory
// https://codeforces.com/contest/777/problem/E

/*
E. Hanoi Factory
Algorithms/Techniques: Dynamic Programming with Stack-based Optimization (Similar to Longest Increasing Subsequence with weights)
Time Complexity: O(n log n) due to sorting and each element pushed/popped from stack at most once
Space Complexity: O(n) for storing rings and stack

Of course you have heard the famous task about Hanoi Towers, but did you know that there is a special factory producing the rings for this wonderful game? Once upon a time, the ruler of the ancient Egypt ordered the workers of Hanoi Factory to create as high tower as possible. They were not ready to serve such a strange order so they had to create this new tower using already produced rings.
There are n rings in factory's stock. The i-th ring has inner radius a_i, outer radius b_i and height h_i. The goal is to select some subset of rings and arrange them such that the following conditions are satisfied:
 
 Outer radiuses form a non-increasing sequence, i.e. one can put the j-th ring on the i-th ring only if b_j <= b_i. 
 Rings should not fall one into the the other. That means one can place ring j on the ring i only if b_j > a_i. 
 The total height of all rings used should be maximum possible. 

Input
The first line of the input contains a single integer n (1 <= n <= 100 000) — the number of rings in factory's stock.
The i-th of the next n lines contains three integers a_i, b_i and h_i (1 <= a_i, b_i, h_i <= 10^9, b_i > a_i) — inner radius, outer radius and the height of the i-th ring respectively.
Output
Print one integer — the maximum height of the tower that can be obtained.
*/

#include <stdint.h>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>
#include <utility>

int main() {
  int64_t n;
  scanf("%lld", &n);
  std::vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> v(n);
  for (int64_t p = 0; p < n; p++) {
    int64_t a, b, h;
    scanf("%lld %lld %lld", &a, &b, &h);
    v[p].first = b;           // Store outer radius as first element for sorting
    v[p].second.first = a;    // Store inner radius as second element of nested pair
    v[p].second.second = h;   // Store height as third element of nested pair
  }
  sort(v.rbegin(), v.rend()); // Sort by outer radius in descending order
  std::stack<int64_t> s;      // Stack to maintain indices of rings in current tower
  int64_t height(0), maxHeight(0);  // Current and maximum heights
  for (int64_t p = 0; p < n; p++) {
    // While stack is not empty and current ring can be placed on top of the top of stack
    while (!s.empty() && v[p].first <= v[s.top()].second.first) {
      height -= v[s.top()].second.second;  // Remove height from the top ring
      s.pop();                             // Pop the index from stack
    }
    s.push(p);             // Push current index
    height += v[p].second.second;  // Add height of current ring
    maxHeight = (maxHeight > height) ? maxHeight : height;  // Update max height
  }
  printf("%lld\n", maxHeight);
  return 0;
}


// https://github.com/VaHiX/codeForces/