// Problem: CF 1669 B - Triple
// https://codeforces.com/contest/1669/problem/B

/*
B. Triple

Purpose:
This code solves the problem of finding any element in an array that appears at least three times.
If no such element exists, it prints -1.

Algorithm:
- For each test case, we use a frequency counting approach with a vector to count occurrences of each element.
- As we read elements, we increment their count in the vector.
- If any element's count reaches or exceeds 3, we immediately store that element and stop further processing for this test case.
- This ensures early termination when a valid answer is found.

Time Complexity: O(n) per test case, where n is the size of the array. In worst case, we process all elements once.
Space Complexity: O(n) for the frequency vector used to store counts.

Techniques:
- Frequency counting with vector
- Early termination upon finding first valid element
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, f = -1; // 'f' stores the result (-1 if none found)
    cin >> n;
    vector<int> v(n + 1, 0); // Vector to store frequency of each element (index 0 unused)
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      v[x] = v[x] + 1; // Increment frequency of element x
      if (v[x] >= 3)   // If x appears at least 3 times
        f = x;         // Store x as the answer
    }
    cout << f << endl; // Print result for this test case
  }
}


// https://github.com/VaHiX/codeForces/