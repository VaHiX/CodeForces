// Problem: CF 1758 D - Range = √Sum
// https://codeforces.com/contest/1758/problem/D

/*
Purpose:
This code generates a sequence of n distinct integers satisfying the condition:
max - min = sqrt(sum). The approach uses a pattern that ensures the sum is a perfect square
and the difference between max and min also equals the square root of that sum.

Algorithms/Techniques:
- Mathematical construction: The solution constructs the sequence by fixing the first element
  and then incrementally building the rest such that the sum becomes a perfect square,
  and the difference between max and min matches the square root of the sum.

Time Complexity: O(n) per test case, as we iterate through n elements once to build the sequence.
Space Complexity: O(1) excluding the output space, as we use only a few variables regardless of input size.

*/
#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << 3 * n + 9 << ' '; // First element of the sequence
    for (int i = 1; i <= n - 2; i++) {
      cout << 2 * i + 3 * n + 9 << ' '; // Generate middle elements based on formula
    }
    cout << 5 * n + 11 << '\n'; // Last element of the sequence
  }
}


// https://github.com/VaHiX/CodeForces/