// Problem: CF 1971 A - My First Sorting Problem
// https://codeforces.com/contest/1971/problem/A

#include <cstdio>
/*
A. My First Sorting Problem
time limit per test1 second
memory limit per test256 megabytes

You are given two integers x and y.
Output two integers: the minimum of x and y, followed by the maximum of x and y.

Algorithms/Techniques: Simple comparison and swap logic using ternary operators

Time Complexity: O(t) where t is the number of test cases
Space Complexity: O(1) - constant extra space used

Input:
The first line contains a single integer t (1≤t≤100) — the number of test cases.
The only line of each test case contains two space-separated integers x and y (0≤x,y≤9).

Output:
For each test case, output two integers: the minimum of x and y, followed by the maximum of x and y.

Example:
input
10
1 9
8 4
1 4
3 4
2 0
2 4
6 9
3 3
0 0
9 9
output
1 9
4 8
1 4
3 4
0 2
2 4
6 9
3 3
0 0
9 9
*/
int main() {
  long t;
  scanf("%ld", &t);  // Read number of test cases
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);  // Read two integers x and y
    printf("%ld %ld\n", (x < y ? x : y), (x > y ? x : y));  // Print min then max using ternary operators
  }
}

// https://github.com/VaHiX/codeForces/