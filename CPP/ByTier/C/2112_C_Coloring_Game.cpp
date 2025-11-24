// Problem: CF 2112 C - Coloring Game
// https://codeforces.com/contest/2112/problem/C

/*
C. Coloring Game
Algorithms/Techniques: Two-pointer technique, sorting, combinatorics.

Time Complexity: O(n^2) per test case due to nested loops and two-pointer traversal.
Space Complexity: O(1) additional space (excluding input storage).

The problem involves choosing 3 elements such that Alice wins regardless of Bob's choice.
Bob can choose any element (even a red one) to make it blue, so the sum of red elements must be
strictly greater than the maximum possible value of the blue element, which is max(arr[i], arr[n-1] - arr[i]).

For each valid triplet (i, j, k) where i < j < k:
    - If arr[i] + arr[j] > max(arr[k], arr[n-1] - arr[k]), then Alice wins.
    - Using two pointers to efficiently count how many valid combinations exist.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
      cin >> arr[i];
    ll cnt = 0;
    for (int i = 2; i < n; i++) {
      // For each valid index i, we compute max(arr[i], arr[n-1] - arr[i])
      // This is the maximum value that Bob can choose as blue element
      int val = max(arr[i], (arr[n - 1] - arr[i]));
      int left = 0, right = i - 1;
      while (right > left) {
        // If sum of elements at left and right is greater than val,
        // then all elements from left to right-1 also satisfy the condition
        if (arr[left] + arr[right] > val) {
          cnt += (right - left);
          right -= 1;
        } else
          left += 1;
      }
    }
    cout << cnt << endl;
  }
}


// https://github.com/VaHiX/codeForces/