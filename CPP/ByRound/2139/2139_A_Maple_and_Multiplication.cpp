// Problem: CF 2139 A - Maple and Multiplication
// https://codeforces.com/contest/2139/problem/A

/*
Problem: A. Maple and Multiplication
Purpose: Determine the minimum number of operations to make two positive integers a and b equal,
         where each operation allows multiplying either a or b by any positive integer.

Algorithms/Techniques: 
    - Mathematical analysis of divisibility and equality conditions.
    - Direct comparison logic based on relation between inputs.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input:
    Each test case contains two integers a and b (1 ≤ a, b ≤ 1000).
Output:
    Minimum operations needed to make a equal to b.
*/

#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t; // Read number of test cases
  while (t--) { // Process each test case
    int x, y;
    cin >> x >> y; // Read the two integers a and b
    
    if (x == y)
      cout << "0\n"; // If already equal, no operations needed
    else if (x % y == 0 || y % x == 0)
      cout << "1\n"; // One of them is divisible by the other -> 1 operation needed
    else
      cout << "2\n"; // Neither divides the other -> 2 operations needed
  }
}


// https://github.com/VaHiX/codeForces/