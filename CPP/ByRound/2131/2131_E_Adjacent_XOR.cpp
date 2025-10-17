// Problem: CF 2131 E - Adjacent XOR
// https://codeforces.com/contest/2131/problem/E

/*
E. Adjacent XOR

Purpose:
This code determines whether an array 'a' can be transformed into another array 'b'
using a specific set of operations where each element at index i (1 <= i < n)
can be updated to a[i] ^ a[i+1] at most once.

Algorithm:
- Key insight: Operations can only modify elements based on XOR of adjacent pairs.
- The last element of the arrays must match; otherwise transformation is impossible.
- Working backwards from the end, for each position:
  * If a[i] == b[i], no action needed.
  * Else check if we could have achieved b[i] by XORing with either next element in original or target array.
- This ensures that changes do not propagate incorrectly.

Time Complexity: O(n) per test case
Space Complexity: O(n) for input storage (excluding output)

Techniques:
- Greedy backward simulation with bitwise XOR operations.
- Sufficient condition check using XOR properties.

*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 200001;

bool can_transform(int n, const vector<int> &a, const vector<int> &b) {
  // Last elements must be equal; otherwise transform is impossible
  if (a[n - 1] != b[n - 1]) {
    return false;
  }
  
  // Process from right to left
  for (int i = n - 2; i >= 0; i--) {
    // If current element matches target, no operation needed
    if (a[i] == b[i]) {
      continue;
    }
    
    // Check whether the desired value b[i] can be obtained
    // either by XOR with a[i+1] (original) or b[i+1] (target)
    if ((a[i] ^ a[i + 1]) != b[i] && (a[i] ^ b[i + 1]) != b[i]) {
      return false;
    }
  }
  
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  int test_cases;
  cin >> test_cases;
  while (test_cases--) {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> b[i];
    }
    
    if (can_transform(n, a, b)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/