// Problem: CF 1725 H - Hot Black Hot White
// https://codeforces.com/contest/1725/problem/H

/*
Purpose: This code solves the problem of assigning colors (black/white) to magical stones such that 
         exactly half are black and half are white, and no two stones react with each other 
         under a specific magic condition. It determines a valid coloring and magic coefficient Z.

Algorithm/Techniques:
- Greedy assignment of colors based on modulo 3 values of stone strengths.
- Adjusts the count of white stones to ensure exactly half are white.
- Uses modulo arithmetic to determine magic coefficient Z.

Time Complexity: O(N) - Single pass through the input array to assign colors.
Space Complexity: O(N) - Space used to store the color assignment string.
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
  int n;
  cin >> n;
  string ans(n, '0'); // Initialize result string with all '0' (black)
  int cnt = 0; // Count of white stones (1s)

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    
    // If stone strength is divisible by 3 or if placing a white stone would exceed half,
    // then make this stone white ('1')
    if (x % 3 == 0 || n / 2 + cnt == i) {
      ans[i] = '1';
      ++cnt;
    }
    
    // If we have more than n/2 white stones so far, make this stone black ('0')
    if (cnt > n / 2) {
      ans[i] = '0';
    }
  }
  
  // Output Z: 0 if white count is <= n/2, otherwise 2
  // Output the coloring string
  cout << (cnt <= n / 2 ? 0 : 2) << '\n' << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/