// Problem: CF 1042 B - Vitamins
// https://codeforces.com/contest/1042/problem/B

/*
B. Vitamins
Purpose: Find the minimum total price of juices to buy to obtain all three vitamins (A, B, C).
Algorithm: Dynamic Programming with bitmasking.
Time Complexity: O(n * 2^3) = O(8n) = O(n), since there are only 8 possible vitamin combinations (2^3).
Space Complexity: O(2^3) = O(1), as we use a fixed-size array of size 8.

This solution uses bitmasks to represent which vitamins are obtained:
- Bit 0 represents vitamin A
- Bit 1 represents vitamin B
- Bit 2 represents vitamin C
Each juice is represented as a bitmask and we update the minimum cost to achieve each combination.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int main() {
  int n, i, j, k;
  cin >> n;
  long c, d[8] = {0}; // d[i] stores min cost to get vitamin combination i (bitmask)
  for (i = 1; i < 8; i++)
    d[i] = 1000000; // Initialize all combinations except empty to infinity
  for (i = 0; i < n; i++) {
    int s = 0;
    string st;
    cin >> c >> st; // Read price and vitamins string
    for (j = 0; j < st.length(); j++)
      s |= (1 << (st[j] - 'A')); // Convert vitamins to bitmask
    for (j = 0; j < 8; j++)
      d[s | j] = min(d[s | j], d[j] + c); // Update cost for all combinations including current juice
  }
  if (d[7] >= 1000000) // If all vitamins (mask 111 in binary) is unreachable
    cout << "-1";
  else
    cout << d[7]; // Output minimum cost to obtain all three vitamins
}


// https://github.com/VaHiX/codeForces/