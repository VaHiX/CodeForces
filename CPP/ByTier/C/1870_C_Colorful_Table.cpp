// Problem: CF 1870 C - Colorful Table
// https://codeforces.com/contest/1870/problem/C

/*
Purpose: This code solves the problem of finding the smallest rectangle containing all cells of each color in a 2D array b, where b[i][j] = min(a[i], a[j]). 
         For each color (from 1 to k), it outputs the sum of width and height of that rectangle.

Algorithms/Techniques:
- Preprocessing to find the first and last occurrence of each color in the array a.
- Binary search using the 'search' function to find boundaries for each color.
- Efficiently tracking maximal elements from front and back to determine rectangle bounds.

Time Complexity: O(n * log n) per test case, due to the binary search and preprocessing.
Space Complexity: O(n) for storing intermediate data structures like 'front' and 'back' vectors.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Binary search function to find the first occurrence of color 'x' in 'arr'
int search(vector<pair<int, int>> &arr, int x) {
  int l = 0, r = arr.size(), mid;
  while (r - l > 1) {
    mid = (r + l) / 2;
    if (arr[mid].first < x)
      l = mid;
    else
      r = mid;
  }
  if (arr[l].first >= x)
    return arr[l].second;
  return arr[r].second;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n), ans(k + 1, 0); // ans[i] indicates if color i is present
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
      ans[arr[i]] = 1; // Mark presence of each color
    }
    
    vector<pair<int, int>> front, back; // Store (color, index) pairs from front and back
    front.push_back(make_pair(arr[0], 0)); // Initialize with first element
    for (int i = 1; i < n; i++) {
      if (arr[i] > front.back().first) { // If current element is greater than last in front
        front.push_back(make_pair(arr[i], i));
      }
    }
    
    back.push_back(make_pair(arr[n - 1], n - 1)); // Initialize with last element
    for (int i = n - 2; i >= 0; i--) {
      if (arr[i] > back.back().first) { // If current element is greater than last in back
        back.push_back(make_pair(arr[i], i));
      }
    }
    
    for (int i = 1; i <= k; i++) {
      if (ans[i]) { // If color i is present in input
        int a = search(front, i), b = search(back, i); // Find leftmost and rightmost positions for color i
        cout << (b - a + 1) * 2 << ' '; // Output width + height (each is (b-a+1))
      } else {
        cout << "0 "; // Color not present
      }
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/