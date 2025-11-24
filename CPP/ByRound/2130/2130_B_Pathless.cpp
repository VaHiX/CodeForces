// Problem: CF 2130 B - Pathless
// https://codeforces.com/contest/2130/problem/B

/*
B. Pathless
Purpose: Determine if it's possible to rearrange an array of 0s, 1s, and 2s such that no valid path exists from index 1 to n with a sum exactly equal to s. If possible, output the rearranged array; otherwise, output -1.

Algorithms/Techniques:
- Greedy rearrangement approach.
- Analyze current sum vs target sum to determine whether the arrangement is invalid or not.
- Reorganize elements: place all 0s first, then 2s, then 1s to prevent valid paths.

Time Complexity: O(n), where n is the size of the array. We scan the array once and output results in linear time.

Space Complexity: O(n), for storing the input vector and auxiliary arrays (zeros, ones, twos).

*/
#include <iostream>
#include <vector>
using namespace std;

void solveTestCase(int arraySize, int targetSum) {
  vector<int> numbers(arraySize);
  int currentSum = 0;
  for (int i = 0; i < arraySize; ++i) {
    cin >> numbers[i];
    currentSum += numbers[i]; // Compute total sum
  }
  int remaining = targetSum - currentSum;
  if (targetSum < currentSum || remaining == 1) {
    // If target is less than current sum or difference is exactly 1,
    // try to rearrange the array to prevent valid path
    vector<int> zeros, twos, ones;
    for (int num : numbers) {
      switch (num) {
      case 0:
        zeros.push_back(num);
        break;
      case 1:
        ones.push_back(num);
        break;
      case 2:
        twos.push_back(num);
        break;
      default:
        break;
      }
    }
    // Output by putting zeros first, then twos, then ones
    for (int num : zeros)
      cout << num << ' ';
    for (int num : twos)
      cout << num << ' ';
    for (int num : ones)
      cout << num << ' ';
    cout << '\n';
  } else {
    // If target sum is achievable, return -1
    cout << "-1\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int numTestCases;
  cin >> numTestCases;
  while (numTestCases--) {
    int arraySize, targetSum;
    cin >> arraySize >> targetSum;
    solveTestCase(arraySize, targetSum);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/