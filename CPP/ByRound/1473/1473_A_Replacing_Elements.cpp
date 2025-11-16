// Problem: CF 1473 A - Replacing Elements
// https://codeforces.com/contest/1473/problem/A

/*
Algorithm: Replacing Elements
Techniques: Sorting, Greedy Approach

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(1) excluding input storage

The problem asks whether we can reduce all array elements to be at most d by replacing 
one element with the sum of two others. The key insight is:
- If the largest element exceeds d, we must reduce it.
- However, if the two smallest elements sum to more than d, we cannot reduce the largest.
- Otherwise, it's always possible to reduce all elements to at most d.

The algorithm sorts the array and checks if:
1. The maximum element is greater than d
2. The sum of the two smallest elements is also greater than d

If both conditions are true, it's impossible to make all elements <= d.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int t, a[110];
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a + n); // Sort the array to easily access smallest and largest elements
    
    // Check if it's impossible to make all elements <= d
    if (a[n - 1] > d && a[0] + a[1] > d)
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/