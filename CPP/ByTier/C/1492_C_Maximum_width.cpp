// Problem: CF 1492 C - Maximum width
// https://codeforces.com/contest/1492/problem/C

/*
* Problem: Maximum width of a beautiful sequence
* Algorithm: Two-pointer technique with pre-processing
* Time Complexity: O(n + m)
* Space Complexity: O(m)
*
* Approach:
* 1. Preprocess the string s to find the earliest occurrence of each character in t (from left to right)
* 2. Preprocess the string s to find the latest occurrence of each character in t (from right to left)
* 3. For each consecutive pair in t, compute the gap between corresponding positions in s
* 4. Return the maximum gap found
*/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
#define N 1000005
int ans, n, m, q[N], h[N]; // q: earliest positions, h: latest positions
string s, t;
int main() {
  cin >> n >> m >> s >> t;
  
  // Preprocess: find earliest positions for each character in t
  for (int i = 0, j = 0; j < m; i++)
    if (s[i] == t[j])
      q[j++] = i; // Store index where t[j] appears in s
  
  // Preprocess: find latest positions for each character in t
  for (int i = n - 1, j = m - 1; j >= 0; i--)
    if (s[i] == t[j])
      h[j--] = i; // Store index where t[j] appears in s (from right to left)
  
  // Calculate maximum gap between consecutive characters in t
  for (int i = 0; i < m - 1; i++)
    ans = max(ans, h[i + 1] - q[i]); // Gap between next character's earliest and previous character's latest position
  
  cout << ans;
}


// https://github.com/VaHiX/CodeForces/