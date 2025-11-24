// Problem: CF 1077 D - Cutting Out
// https://codeforces.com/contest/1077/problem/D

/*
Algorithm/Technique: 
- Count frequency of each element in the array
- For each element, calculate how many times it can contribute to forming copies of t
- Use a greedy approach to select k elements that maximize the number of copies that can be formed
- Time Complexity: O(n + max_value * log(max_value)) where max_value <= 2*10^5
- Space Complexity: O(max_value)

The approach works by:
1. Counting frequency of each element
2. For each element, calculating how many complete copies each frequency allows
3. Sorting these possibilities to greedily select the best k elements
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<pair<int, int>> ans;
  int n, k, a[200020] = {0}, p[200020] = {0};
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    p[a[i]]++;
  }
  for (int i = 0; i < 200020; i++) {
    for (int j = 1; j <= p[i]; j++)
      ans.push_back({p[i] / j, i});  // Store (max_copies, element_value)
  }
  sort(ans.begin(), ans.end());
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < k; i++)
    cout << ans[i].second << " ";
  return 0;
}


// https://github.com/VaHiX/CodeForces/