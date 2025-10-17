// Problem: CF 1995 C - Squaring
// https://codeforces.com/contest/1995/problem/C

/*
C. Squaring
Algorithms/Techniques: Greedy, Simulation
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

Problem Description:
Given an array of integers, we want to make it non-decreasing by replacing elements with their squares.
Each replacement counts as one "act of justice". We need to find the minimum number of such acts,
or return -1 if impossible.

The key idea is:
- If a previous element > 1 and current element = 1, it's impossible to make array non-decreasing
- For each element from left to right, simulate how many squares are needed to make it >= previous element
- Keep track of the number of operations required at each step.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    
    bool possible(true);
    // Check if it's impossible to make array non-decreasing
    for (ll p = 1; possible && p < n; p++) {
      if (a[p - 1] > 1 && a[p] == 1) {
        possible = false;
      }
    }
    
    if (!possible) {
      puts("-1");
      continue;
    }
    
    ll cnt(0), prev(0);
    // Process each element to calculate operations needed
    for (ll p = 1; p < n; p++) {
      ll num(prev); // Start with previous operation count
      ll x(a[p - 1]), y(a[p]);
      
      // Reduce x by squaring until it can reach or exceed y, or x becomes 1
      while (x > 1 && x * x <= y) {
        x *= x;
        --num;
      }
      
      // Increase y by squaring until it reaches or exceeds x
      while (y < x) {
        y *= y;
        ++num;
      }
      
      // Ensure num is not negative
      num = (num > 0 ? num : 0);
      cnt += num;
      prev = num; // Update previous operation count for next iteration
    }
    
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/