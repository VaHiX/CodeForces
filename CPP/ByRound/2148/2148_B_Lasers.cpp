// Problem: CF 2148 B - Lasers
// https://codeforces.com/contest/2148/problem/B

/*
B. Lasers

Purpose:
This code solves the problem of finding the minimum number of laser crossings required to travel from (0,0) to (x,y) in a 2D plane with horizontal and vertical lasers. The key insight is that we only need to count how many horizontal and vertical lasers we cross.

Algorithms/Techniques:
- Greedy approach based on counting intersections.
- Efficiently determine minimal crossings by calculating how many lasers are crossed in each direction.

Time Complexity: O(n + m) per test case, where n is number of horizontal lasers and m is number of vertical lasers.
Space Complexity: O(1), only using a few variables for computation.

Input Format:
- t test cases
- For each test case: n, m, x, y followed by lists of a_i (horizontal laser y-coordinates) and b_i (vertical laser x-coordinates)

Output Format:
- Minimum number of crossings for each test case
*/

#include <iostream>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, x, y, a;
    cin >> n >> m >> x >> y;
    // Read horizontal lasers; we only need to know how many are below our path
    for (int i = 0; i < n + m; i++)
      cin >> a;
    // Output the total number of lasers crossed: 
    // n (horizontal lasers) + m (vertical lasers)
    cout << n + m << '\n';
  }
}


// https://github.com/VaHiX/codeForces/