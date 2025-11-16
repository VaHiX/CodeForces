// Problem: CF 1090 M - The Pleasant Walk
// https://codeforces.com/contest/1090/problem/M

/*
M. The Pleasant Walk
time limit per test
1 second
memory limit per test
512 megabytes
input
standard input
output
standard output

There are n houses along the road where Anya lives, each one is painted in one of k possible colors.
Anya likes walking along this road, but she doesn't like when two adjacent houses at the road have the same color. She wants to select a long segment of the road such that no two adjacent houses have the same color.
Help Anya find the longest segment with this property.

Algorithms/Techniques:
- Sliding window / Two pointers approach
- Linear scan through array to track maximum length of valid segment

Time complexity: O(n)
Space complexity: O(1)

Input
The first line contains two integers n and k — the number of houses and the number of colors (1 ≤ n ≤ 100,000, 1 ≤ k ≤ 100,000).
The next line contains n integers a1, a2, ..., an — the colors of the houses along the road (1 ≤ ai ≤ k).

Output
Output a single integer — the maximum number of houses on the road segment having no two adjacent houses of the same color.

Example
Input
8 3
1 2 3 3 2 1 2 2

Output
4

Note
In the example, the longest segment without neighboring houses of the same color is from the house 4 to the house 7. The colors of the houses are [3, 2, 1, 2] and its length is 4 houses.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int n, m, ans, now, l;
signed main() {
  scanf("%d%d", &n, &m);
  for (int x, i = 1; i <= n; i++, l = x)  // iterate through houses, store previous color in l
    scanf("%d", &x), x == l ? now = 1 : ans = max(ans, ++now);  // if current color equals previous, reset counter; else increment and update max
  cout << ans;
}


// https://github.com/VaHiX/codeForces/