// Problem: CF 2131 C - Make it Equal
// https://codeforces.com/contest/2131/problem/C

/*
C. Make it Equal
Algorithms/Techniques: Modular arithmetic, sorting, multiset comparison

Time Complexity: O(n log n) per test case due to sorting operations.
Space Complexity: O(n) for storing the arrays arr1 and arr2.

Given two multisets S and T of size n and a positive integer k,
you may perform the following operations any number (including zero) of times on S:
Select an element x in S, and remove one occurrence of x in S. Then, either insert x+k into S,
or insert |x−k| into S.
Determine if it is possible to make S equal to T.

The key insight is that for any number x, it can be transformed to:
- x + k
- |x - k|

Both transformations result in values that are equivalent modulo k. 
Specifically, for any x,
min(x % k, k - (x % k)) gives the minimal distance to a multiple of k.
Thus, we transform each number into its "remainder class" and check if both multisets
have the same multiset of such transformed values.

This method works because:
- Two numbers are in the same equivalence class if they can be reached from one another through allowed operations.
- This approach reduces all elements to a canonical form and then compares multisets.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool can_make_equal(int n, long long k) {
  vector<long long> arr1(n), arr2(n);
  for (int i = 0; i < n; ++i) {
    long long num;
    cin >> num;
    arr1[i] = min(num % k, k - num % k);  // Transform to minimal distance to multiple of k
  }
  for (int i = 0; i < n; ++i) {
    long long num;
    cin >> num;
    arr2[i] = min(num % k, k - num % k);  // Transform to minimal distance to multiple of k
  }
  sort(arr1.begin(), arr1.end());  // Sort the transformed array
  sort(arr2.begin(), arr2.end());  // Sort the transformed array
  return arr1 == arr2;  // Compare multisets
}

void solve() {
  int n;
  long long k;
  cin >> n >> k;
  if (can_make_equal(n, k)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int test_cases;
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/