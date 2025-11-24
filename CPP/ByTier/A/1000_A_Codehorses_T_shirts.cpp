// Problem: CF 1000 A - Codehorses T-shirts
// https://codeforces.com/contest/1000/problem/A

#include <iostream>
#include <map>
#include <string>

using namespace std;
int n, a;
int main(void) {
  string s;
  map<string, int> m; // Map to store frequency of each T-shirt size from previous year
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> s, m[s]++; // Read and count occurrences of each size from previous year
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (m[s] > 0)
      m[s]--; // If current size exists in map, decrease its count (match found)
    else
      a++; // If size not found, increment changes needed
  }
  cout << a; // Output minimal number of changes required
}

// Time Complexity: O(n log n) due to map operations (insertion and lookup)
// Space Complexity: O(n) for storing the map of T-shirt sizes

// https://github.com/VaHiX/CodeForces/