// Problem: CF 1931 E - Anna and the Valentine's Day Gift
// https://codeforces.com/contest/1931/problem/E

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define all(v) v.begin(), v.end()
using namespace std;
using i64 = int64_t;
void solve() {
  int n, m;
  cin >> n >> m;
  m++; // Increment m to simplify comparison later
  i64 total = 0; // Total number of digits in all numbers
  vector<int> a(n); // Vector to store trailing zeros for each number
  for (int &e : a) {
    string s;
    cin >> s;
    total += s.size(); // Add length of the string to total
    // Count trailing zeros by iterating from the end of the string
    for (int i = s.size() - 1; i >= 0; i--) {
      if (s[i] == '0')
        e++; // Increment count of trailing zeros
      else
        break; // Stop when a non-zero digit is encountered
    }
  }
  // Sort a in descending order to prioritize larger trailing zeros
  sort(a.rbegin(), a.rend());
  // Subtract the contribution of pairs of numbers with high trailing zeros
  for (int i = 0; i < n; i += 2)
    total -= a[i]; // Only consider every other element (pairing strategy)
  // Output winner based on whether total digits is sufficient
  cout << (total >= m ? "Sasha" : "Anna") << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--)
    solve();
  return 0;
}

// ### Complexity Analysis:
// - **Time Complexity**: O(n log n), where n is the number of integers in the list. Sorting takes O(n log n), and the rest of the operations are linear.
// - **Space Complexity**: O(n), due to the vector `a` storing trailing zero counts and the input string storage.

// https://github.com/VaHiX/CodeForces/