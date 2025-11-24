// Problem: CF 2124 D - Make a Palindrome
// https://codeforces.com/contest/2124/problem/D

/*
D. Make a Palindrome
Algorithms/Techniques: Greedy, Sorting, Two Pointers, Palindrome Check

Time Complexity: O(n log n) per test case due to sorting and linear passes.
Space Complexity: O(n) for storing arrays and auxiliary structures.

The problem asks whether we can make a palindrome from an array after deleting
elements via specific operations. The key idea is that we can delete elements
such that they are the k-th smallest in subarrays of size >= k, effectively allowing us
to remove any element based on its rank in sorted subarrays. This lets us control
the structure of the eventual palindrome.

The approach involves:
1. Sorting a copy of input to quickly get the k-th smallest element (x).
2. Partitioning original array into segments separated by values < x.
3. Check symmetric properties of these segments and counts of x's in each part.
4. If the total number of valid matches in mirrored parts is sufficient, output yes.
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

void work() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  auto b = a;
  sort(b.begin(), b.end());
  int x = b[k - 1], cnt = 0;
  vector<int> c, d;
  for (int i = 0; i < n; i++) {
    if (a[i] < x) { // Partition by elements less than k-th smallest
      c.push_back(a[i]);
      d.push_back(cnt);
      cnt = 0;
    } else if (a[i] == x)
      cnt++; // Count occurrences of x
  }
  d.push_back(cnt); // Add final count

  // Check for symmetric pattern in segments
  for (int i = 0; i < c.size(); i++)
    if (c[i] != c[c.size() - i - 1]) {
      cout << "no" << endl;
      return;
    }

  int sum = 0;
  for (int i = 0; i < d.size(); i++)
    sum += min(d[i], d[d.size() - i - 1]); // Pair up mirrored counts
  
  if (sum + c.size() < k - 1) // Sufficient number of elements to form palindrome
    cout << "no" << endl;
  else
    cout << "yes" << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/