// Problem: CF 2151 A - Incremental Subarray
// https://codeforces.com/contest/2151/problem/A

/*
Purpose: This code solves the problem of counting how many subarrays in a specific sequence b match a given array a.
The sequence b is built incrementally: it starts with 1, then 1,2, then 1,2,3, ..., up to 1,2,...,n.
Algorithm: 
- For each test case:
  1. Read n and m (maximum number written and length of favorite array).
  2. Read the favorite array a.
  3. Check that the elements in a are strictly increasing (to ensure it's a valid prefix of b).
  4. If not strictly increasing, answer is 1 (as per logic).
  5. Otherwise, calculate how many subarrays equal to a exist starting from a specific position.

Time Complexity: O(m) per test case.
Space Complexity: O(N), where N = 100010 for storing a array.

*/
#include <iostream>
using namespace std;
const int N = 100010;
int a[N];

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, m, i;
    bool pd = 1; // flag to check if array a is strictly increasing
    cin >> n >> m;
    for (i = 1; i <= m; i++) {
      cin >> a[i];
      if (i != 1 && a[i] <= a[i - 1]) // Check strictly increasing
        pd = 0;
    }
    cout << (pd == 0 ? 1 : (n - a[m] + 1)) << endl; // Output based on logic
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/