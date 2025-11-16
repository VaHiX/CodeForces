// Problem: CF 1733 C - Parity Shuffle Sorting
// https://codeforces.com/contest/1733/problem/C

/*
Code Purpose:
This code solves the "Parity Shuffle Sorting" problem where we are given an array of non-negative integers and must perform at most n operations to make the array non-decreasing. Each operation selects two indices l and r, and depending on whether a[l] + a[r] is odd or even, it updates either a[r] := a[l] or a[l] := a[r].

Algorithm:
1. For each test case:
   - Read input array
   - If n=1, no operations needed
   - If n>1:
     - First operation: Choose indices 1 and n
     - Then iterate from index 2 to n-1:
       - If a[i] and a[1] have same parity, use operation (i, n)
       - Otherwise, use operation (1, i)

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array and answer

*/
#include <stdio.h>
#include <iostream>

using namespace std;
int t, n, a[200005], ans[200005];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    cout << n - 1 << endl;
    if (n > 1)
      printf("1 %d\n", n); // First operation: take last element to first position
    for (int i = 2; i < n; i++)
      if (a[i] % 2 == a[1] % 2) // If a[i] and a[1] have same parity
        printf("%d %d\n", i, n); // Use (i, n) operation
      else
        printf("%d %d\n", 1, i); // Use (1, i) operation
  }
}


// https://github.com/VaHiX/CodeForces/