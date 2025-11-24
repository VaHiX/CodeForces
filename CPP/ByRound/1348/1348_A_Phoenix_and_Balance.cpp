// Problem: CF 1348 A - Phoenix and Balance
// https://codeforces.com/contest/1348/problem/A

/*
Problem: Phoenix and Balance
Algorithm/Technique: Greedy approach to minimize the difference between two piles of coins.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The optimal strategy is to pair the largest coin with the smallest coin,
the second largest with the second smallest, etc., so that the sum difference is minimized.
For n coins numbered 1 to n, the weights are 2^1, 2^2, ..., 2^n.
To minimize |a - b| where a and b are sums of two groups of size n/2:
We place the largest coin (2^n) with the smallest coin (2^1), and so on.
The result is derived from the mathematical formula: 2 * (2^(n/2) - 1).

Test cases:
Input:
2
2
4

Output:
2
6
*/

#include <math.h>
#include <iostream>

int main() {
  int t, n;
  for (std::cin >> t; t--;) {           // Read number of test cases and loop through them
    std::cin >> n,                       // Read the value of n
    std::cout << 2 * (pow(2, n / 2) - 1) << '\n';  // Calculate and output the minimum difference using the derived formula
  }
}


// https://github.com/VaHiX/codeForces/