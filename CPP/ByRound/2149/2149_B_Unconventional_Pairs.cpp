// Problem: CF 2149 B - Unconventional Pairs
// https://codeforces.com/contest/2149/problem/B

/*
B. Unconventional Pairs

Task: Given an array of even length n, pair up elements such that the maximum difference
      among all pairs is minimized.

Algorithm: 
- Sort the array.
- Pair adjacent elements (i, i+1), (i+2, i+3), etc.
- The maximum difference in this pairing is the answer.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) excluding input storage

Sample Input:
5
2
1 2
4
10 1 2 9
6
3 8 9 3 3 2
8
5 5 5 5 5 5 5 5
4
-5 -1 2 6

Sample Output:
1
1
1
0
4
*/

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n, t;
  cin >> t; // Read number of test cases
  for (int z = 0; z < t; ++z) {
    cin >> n; // Read array size
    int ma = 0; // Initialize maximum difference
    int a[n]; // Array to store elements
    for (int i = 0; i < n; ++i) {
      cin >> a[i]; // Read array elements
    }
    sort(a, a + n); // Sort the array to pair adjacent elements optimally
    for (int i = 0; i < n; i += 2) {
      ma = max(a[i + 1] - a[i], ma); // Calculate difference between pairs and track maximum
    }
    cout << ma << endl; // Output result for current test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/