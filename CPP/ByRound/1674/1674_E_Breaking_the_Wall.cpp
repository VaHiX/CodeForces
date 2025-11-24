// Problem: CF 1674 E - Breaking the Wall
// https://codeforces.com/contest/1674/problem/E

/*
Purpose: 
This code solves the problem of finding the minimum number of onager shots required to break at least two sections of a wall. 
Each shot deals 2 damage to a targeted section and 1 damage to adjacent sections. 
The algorithm considers different strategies for breaking sections based on adjacent section durability.

Algorithms/Techniques:
- Greedy approach with case analysis
- Dynamic programming ideas for minimal shot count calculation
- Sorting for certain cases

Time Complexity: O(n log n) due to sorting step
Space Complexity: O(1) - only using a fixed amount of extra space
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
int n, a[200003], T;
int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int ret = 19260817; // Initialize with a large value to find minimum
  // Case 1: Break two adjacent sections by targeting one of them optimally
  for (int i = 1; i < n; i++) {
    int x = a[i], y = a[i - 1];
    // Calculate minimal shots required to break both sections
    ret = min(ret, max(max((x + 1) / 2, (y + 1) / 2), (x + y + 2) / 3));
  }
  // Case 2: Break two non-adjacent sections using a middle section as a pivot
  for (int i = 1; i < n - 1; i++)
    ret =
        min(ret, min(a[i - 1], a[i + 1]) + (abs(a[i - 1] - a[i + 1]) + 1) / 2);
  // Case 3: Break the two sections with least durability by shooting them directly
  sort(a, a + n);
  ret = min(ret, (a[0] + 1) / 2 + (a[1] + 1) / 2);
  cout << ret;
}


// https://github.com/VaHiX/CodeForces/