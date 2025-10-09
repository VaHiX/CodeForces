// Problem: CF 2057 B - Gorilla and the Exam
// https://codeforces.com/contest/2057/problem/B

/*
B. Gorilla and the Exam
Algorithms/Techniques: Greedy, Map, Frequency Counting

Time Complexity: O(n log n) per test case due to map operations and sorting-like behavior of map traversal.
Space Complexity: O(n) for storing frequency maps.

The problem asks to minimize the number of operations needed to empty an array,
where each operation removes all elements equal to the minimum in a subarray.
We use a greedy strategy:
1. Count frequencies of each element.
2. Then count how many elements have each frequency.
3. Try to reduce the number of distinct frequencies by using up to k changes to make some elements
   have the same frequency, thereby reducing the number of operations needed.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

using namespace std;
typedef long long ll;
const int N = 500103;

void solve() {
  int n, k;
  cin >> n >> k;
  int res = 0, o = 1;
  map<int, int> ans, occ; // ans: element -> frequency, occ: frequency -> count of elements with that frequency
  for (int i = 1, x; i <= n; i++)
    cin >> x, ans[x]++; // Count frequency of each element
  for (auto [x, y] : ans)
    occ[y]++; // Count how many elements have each frequency
  for (auto [z, c] : occ) {
    // While we can use k operations to reduce the count of elements with frequency z,
    // and there are still such elements, reduce them
    while (k >= z && c)
      k -= z, c--;
    res += c; // Add remaining elements that cannot be reduced further
  }
  res = max(res, 1); // Minimum result is 1 - you always need at least one operation if array is non-empty
  cout << res << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/