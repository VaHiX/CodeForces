// Problem: CF 2169 A - Alice and Bob
// https://codeforces.com/contest/2169/problem/A

/*
Code Purpose:
This program solves a game problem where Alice and Bob are choosing integers to maximize their points based on proximity to marbles' values. 
Bob needs to choose an integer 'b' to maximize the number of marbles he gets points for, given that Alice's choice 'a' is known.

Algorithms/Techniques:
- Sorting and binary search approach (implied by preprocessing and comparing distances)
- Greedy selection strategy: Bob chooses either m-1 or m+1 based on which gives more points

Time Complexity: O(n) per test case, where n is the number of marbles. We process all marbles once.
Space Complexity: O(1) extra space, not counting input storage.

*/
#include <iostream>

using namespace std;
int main() {
  int T, n, m, x;
  cin >> T;
  while (T--) {
    int s1 = 0, s2 = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> x;
      if (x <= m - 1)   // Count marbles where Alice's choice is closer or equal distance to x than Bob's choice of m-1
        s1++;
      if (x >= m + 1)   // Count marbles where Alice's choice is closer or equal distance to x than Bob's choice of m+1
        s2++;
    }
    cout << (s1 > s2 ? m - 1 : m + 1) << endl;  // Choose the option that maximizes Bob's points
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/