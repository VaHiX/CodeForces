// Problem: CF 2065 E - Skibidus and Rizz
// https://codeforces.com/contest/2065/problem/E

/*
E. Skibidus and Rizz

Purpose:
Construct a binary string of length n+m with exactly n 0's and m 1's such that 
the maximum balance-value among all substrings is exactly k. The balance-value 
of a substring is defined as max(zeros - ones, ones - zeros).

Algorithm:
- For a valid string to exist:
  * The difference between n and m must not exceed k.
  * The larger count (n or m) must be at least k.
- We construct the string by placing the excess characters (beyond k) 
  in the middle with alternating patterns to avoid creating higher balance.

Time Complexity: O(n + m) per test case — linear scan to build the output string.
Space Complexity: O(1) additional space (excluding input/output).

*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    
    // Check if it's impossible to achieve balance k
    if (abs(n - m) > k || max(m, n) < k)
      cout << "-1" << endl;
    else {
      // Determine how many 1s we can place before alternating pattern starts
      int t = max(m, n) - k;
      
      // Print '0' for (n - t) times
      for (int i = 0; i < n - t; i++)
        cout << "0";
        
      // Print '10' for t times (this creates the alternating pattern to control balance)
      for (int i = 0; i < t; i++)
        cout << "10";
        
      // Print remaining '1's
      for (int i = 0; i < m - t; i++)
        cout << "1";
        
      cout << endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/