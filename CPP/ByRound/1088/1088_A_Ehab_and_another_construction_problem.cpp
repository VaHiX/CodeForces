// Problem: CF 1088 A - Ehab and another construction problem
// https://codeforces.com/contest/1088/problem/A

/*
Code Purpose:
This code solves the problem of finding two integers a and b such that:
1. 1 ≤ a, b ≤ x
2. b divides a (a is divisible by b)
3. a * b > x
4. a / b < x

The algorithm uses a mathematical approach:
- If n > 1, we return n and n-1
- If n = 1, we return -1 (no solution exists)

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage

Algorithms/Techniques:
Mathematical approach with edge case handling
*/

#include <iostream>

using namespace std;
int n;
int main() {
  cin >> n;
  (n - 1) ? cout << n << " " << n : cout << -1;
}


// https://github.com/VaHiX/CodeForces/