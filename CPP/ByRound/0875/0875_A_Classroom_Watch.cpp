// Problem: CF 875 A - Classroom Watch
// https://codeforces.com/contest/875/problem/A

/*
 * Problem: Classroom Watch
 * Purpose: Find all positive integers x such that x + sum_of_digits(x) = n.
 * Approach:
 *   - Iterate over possible values of sum_of_digits(x) (from 1 to 100).
 *   - For each sum s, compute x = n - s.
 *   - Check if sum_of_digits(x) equals s.
 *   - If true, add x to the result list.
 * 
 * Time Complexity: O(1) since sum_of_digits(x) is bounded by a small constant (at most 9*10 = 90 for 10^9).
 * Space Complexity: O(1) as the number of valid x values is at most a small constant.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int n, x, i, s;
vector<int> b;

int main() {
  cin >> n;
  // Loop through possible sums of digits (up to 100, as maximum sum for 10^9 is 9*10 = 90)
  for (i = 100; i > 0; i--) {
    // Compute x such that x + i = n => x = n - i
    for (x = n - i, s = 0; x; x /= 10)
      s += x % 10; // Calculate sum of digits of x
    // If sum of digits of x equals i, then x is a valid solution
    i == s ? b.push_back(n - i), 0 : 0;
  }
  cout << b.size() << endl;
  for (auto y : b)
    cout << y << " ";
}


// https://github.com/VaHiX/CodeForces/