// Problem: CF 1641 B - Repetitions Decoding
// https://codeforces.com/contest/1641/problem/B

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int t, n;
vector<int> vec;
vector<int> ans;
int cidx;
vector<pair<int, int>> ops;
void solve() {
  cin >> n;
  vec.resize(n);
  for (int &e : vec)
    cin >> e;
  ops.clear();
  ans.clear();
  cidx = 0;
  while (!vec.empty()) {
    cidx++;
    // Find the first occurrence of the first element in the rest of the array
    auto it = find(vec.begin() + 1, vec.end(), vec.front());
    if (it == vec.end()) {
      // If no such element is found, it's impossible to form tandem repeats
      cout << "-1\n";
      return;
    }
    // Update the index for insertion operations
    cidx += it - vec.begin();
    // Record the length of the current tandem repeat (as number of elements to be inserted)
    ans.push_back(it - vec.begin());
    // Insert all elements between the first element and the found element
    for (auto e = ++vec.begin(); e != it; e++)
      ops.emplace_back(cidx++, *e);
    // Reverse the portion between the first element and the found element
    reverse(vec.begin() + 1, it);
    // Remove the found element
    vec.erase(it);
    // Remove the first element
    vec.erase(vec.begin());
  }
  // Output the number of operations
  cout << ops.size() << '\n';
  // Output each operation
  for (auto e : ops)
    cout << e.first << ' ' << e.second << '\n';
  // Output the number of tandem repeats
  cout << ans.size() << '\n';
  // Output the lengths of each tandem repeat (each length is doubled since tandem repeat has equal halves)
  for (int e : ans)
    cout << e * 2 << ' ';
  cout << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/