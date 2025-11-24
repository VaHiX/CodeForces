// Problem: CF 2130 A - Submission is All You Need
// https://codeforces.com/contest/2130/problem/A

/*
Purpose:
This code solves a problem where we are given a multiset of non-negative integers and must compute the maximum possible score 
by performing operations: either adding the sum of a subset or the mex of a subset to our score, then removing that subset.

Approach:
For each test case, we process the array and adjust values:
- If an element is 0, we replace it with 1 (since 0 doesn't contribute to sum but can be used for mex operations).
- For all other elements, keep them as they are.
Then, we simply sum up these adjusted values.

Time Complexity: O(n) per test case
Space Complexity: O(1)

Algorithms/Techniques:
- Greedy approach on adjusted array elements
- Simple summation with conditional value replacement

*/

#include <iostream>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int numTestCases;
  cin >> numTestCases;
  while (numTestCases--) {
    int arraySize, totalSum = 0;
    cin >> arraySize;
    for (int i = 0; i < arraySize; ++i) {
      int currentNumber;
      cin >> currentNumber;
      // If the number is 0, treat it as 1 for sum calculation to simulate optimal mex selection
      totalSum += (currentNumber != 0) ? currentNumber : 1;
    }
    cout << totalSum << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/