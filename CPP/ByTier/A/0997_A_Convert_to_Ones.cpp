// Problem: CF 997 A - Convert to Ones
// https://codeforces.com/contest/997/problem/A

/*
Algorithm/Technique: Greedy with pattern recognition
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to convert a binary string of 0s and 1s into a string of all 1s,
using two operations:
1. Reverse a substring (cost x)
2. Invert a substring (cost y)

Key insight:
- To minimize cost, we want to reduce the number of "groups" of 0s.
- A group of 0s is a continuous sequence of 0s.
- If there are no 0s, the answer is 0.
- If there are k groups of 0s, we need to perform k-1 reversals and 1 inversion.
  - The optimal strategy is to perform one inversion (cost y) on one group,
    and let reversals handle the others.
  - If it's cheaper to reverse than to invert, we might prefer reversals.

However, a key observation is that to convert all 0s to 1s:
- If there are 'zeros' number of groups of 0s (where consecutive 0s are considered one group),
  we must do k-1 reversals if x < y, else we do 1 inversion (y) and (k-1) reversals, 
  but in the optimal case, we are only considering 1 inversion for the group with most 0s.

Actually, the correct model:
- We count the number of transitions from '1' to '0' in the string.
- Each such transition represents a separate group of 0s.
- Let's say we have 'zeros'-number of such groups of 0s (not total count of 0s).
- If there are no 0s, nothing needs to be done.
- Otherwise, we can either:
  - Invert the entire string (cost y), or
  - Pay for (zeros - 1) reversals (if reversing is cheaper than inverting), 
    and one inversion to fix the last group (cost y).
  - The minimum is computed as: (zeros-1) * min(x, y) + y
  - But if x >= y, we may consider just inverting (and that means cost y for one group).
  - So, the formula becomes: (zeros - 1) * min(x, y) + y, which considers 
    that to change all 0s to 1s, 
    we do one invert for the last 0, and (zeros-1) reversals to fix up rest of the 0 groups.
*/

#include <stdio.h>
#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll n, x, y;
  std::cin >> n >> x >> y;
  std::string s;
  std::cin >> s;
  ll zeros(s[0] == '0');  // Initialize with first character being 0
  for (ll p = 1; p < s.size(); p++) {
    zeros += (s[p] == '0' && s[p - 1] == '1');  // Count transitions from 1 to 0
  }
  if (zeros == 0) {
    puts("0");
  } else {
    // If there's at least one group of 0s, compute minimal cost using minimum of x and y
    // for the cheaper operation of reversing or inverting.
    std::cout << ((zeros - 1) * (x < y ? x : y) + y) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/