// Problem: CF 750 A - New Year and Hurry
// https://codeforces.com/contest/750/problem/A

/*
Purpose: 
This code determines the maximum number of problems Limak can solve before the contest ends (at midnight) 
so that he still has enough time to get to the New Year's Eve party. 
The contest lasts 4 hours (240 minutes), and Limak needs 'k' minutes to travel to the party.
Each problem i takes 5*i minutes to solve.

Algorithms/Techniques:
- Greedy approach: Solve problems in increasing order of difficulty (1 to n) to maximize the count.
- Iteration through problems and subtracting time used from available time.

Time Complexity: O(n) where n is the number of problems.
Space Complexity: O(1) as only a few variables are used.
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  cin >> n >> k;
  m = 240 - k;  // Available time after accounting for travel time
  ll count = 0;
  for (i = 1; i <= n; i++) {
    if (m - (5 * i) >= 0) {  // Check if we can solve problem i
      count++;
      m = m - (5 * i);       // Reduce remaining time
    } else
      break;  // Cannot solve more problems
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/