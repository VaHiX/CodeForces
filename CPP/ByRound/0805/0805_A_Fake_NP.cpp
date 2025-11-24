// Problem: CF 805 A - Fake NP
// https://codeforces.com/contest/805/problem/A

/*
Purpose: 
This code solves a problem where we are given a range [l, r] and need to find the integer that appears 
the maximum number of times as a divisor (excluding 1) among all integers in that range. 
The key insight is that for any range [l, r], the number 2 will appear as a divisor in the most numbers 
if l > 1, otherwise if l == r, the number itself is the answer.

Algorithms/Techniques:
- Observation-based approach
- No need for actual enumeration or computation of divisors

Time Complexity: O(1)
Space Complexity: O(1)

*/
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie();
  ll i, j, k;
  ll u, v, n;
  ll l, r;
  cin >> l >> r;
  
  // If l equals r, the only number in the range is l itself
  if (l == r)
    cout << l;
  else
    // For any range larger than 1, the number 2 appears as a divisor in the most numbers
    cout << "2";
    
  cin.clear();
  cin.ignore();
  return 0;
}


// https://github.com/VaHiX/CodeForces/