// Problem: CF 1462 C - Unique Number
// https://codeforces.com/contest/1462/problem/C

/*
C. Unique Number
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
You are given a positive number x. Find the smallest positive integer number that has the sum of digits equal to x and all digits are 
distinct
 (unique).
Input
The first line contains a single positive integer t (1 ≤ t ≤ 50) — the number of test cases in the test. Then t test cases follow.
Each test case consists of a single integer number x (1 ≤ x ≤ 50).
Output
Output t answers to the test cases:
 
 if a positive integer number with the sum of digits equal to x and all digits are different exists, print the smallest such number; 
 otherwise print 
-1
. 

Algorithm: Greedy approach
We want the smallest number with given digit sum and distinct digits.
To get the smallest number, we want to:
1. Use as few digits as possible
2. Place smaller digits in more significant positions

Strategy:
1. Start from the largest digit (9) and work backwards
2. For each digit, use it if it doesn't exceed remaining sum
3. Build the result by multiplying with increasing powers of 10
4. If final sum is not zero, no valid solution exists

Time complexity: O(x) where x <= 50 (constant time)
Space complexity: O(1) - only using a few variables
*/

#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, ans = 0, p = 1; // n: remaining sum, ans: result, p: place value multiplier
    cin >> n;
    for (int i = 9; i; i--) // iterate from 9 down to 1
      if (n >= i) // if current digit can be used
        n -= i, ans += p * i, p *= 10; // subtract digit from sum, add to result, increase place value
    if (n) // if remaining sum is not zero, no valid solution
      cout << "-1" << '\n';
    else
      cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/