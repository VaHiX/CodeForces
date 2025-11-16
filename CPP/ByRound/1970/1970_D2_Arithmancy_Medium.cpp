// Problem: CF 1970 D2 - Arithmancy (Medium)
// https://codeforces.com/contest/1970/problem/D2

// # Arithmancy (Medium) Solution

// This solution uses a precomputed database to map spell powers to the indices of the magic words that created them.

// The approach is to:
// 1. Precompute a set of magic words with specific structures
// 2. For each word, compute the power of all possible concatenations
// 3. Store this mapping in a hash map for lookup

// The key insight is to use words with a pattern that makes the calculation of spell power predictable and unique.

// ## Time Complexity
// - Preprocessing: O(n²) where n=30 (constant)
// - Each query: O(1)
// - Overall: O(1) for queries, O(n²) for preprocessing

// ## Space Complexity
// - O(n²) for the mapping database where n=30 (constant)

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define fastio                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr)
#define i64 long long
#define ld long double
#define F first
#define S second
#define MOD 998244353
#define pairii pair<int, int>
#define pb push_back
#define matrix(type) vector<vector<type>>
#define vi vector<int>
#define vi64 vector<i64>
#define uset unordered_set
#define umap unordered_map
#define mpr make_pair
#define ALL(x) x.begin(), x.end()
#define RALL(data) data.rbegin(), data.rend()
#define TYPEMAX(type) std::numeric_limits<type>::max()
#define TYPEMIN(type) std::numeric_limits<type>::min()
#define null nullptr
#define fr(i, a, b) for (int i = a; i < b; i++)
using namespace std;
class NullBuffer : public std::streambuf {
public:
  int overflow(int c) { return c; }
};
ostream logger(new NullBuffer());
int calc(string &s) {
  uset<string> st;
  for (int i = 0; i < s.size(); i++) {
    string t;
    for (int j = i; j < s.size(); j++) {
      t += s[j];
      st.insert(t);
    }
  }
  return st.size();
}
umap<int, pairii> db;
string ar[30];
void setup() {
  // Precompute magic words and their concatenation powers
  int n = 30;
  int sz[n];
  for (int i = 0; i < n; i++) {
    // Create magic words with specific patterns
    ar[i] = "O";
    int y = (i * (i + 1)) >> 1; // Calculate triangular number
    // Add X's to the word
    for (int j = 0; j <= y; j++) {
      ar[i] += 'X';
    }
    // Add O's to the word
    for (int j = 0; j <= y; j++) {
      ar[i] += 'O';
    }
    sz[i] = y + 1; // Store size of the word
  }
  // Precompute all possible concatenation powers
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x = 0;
      int s = sz[i], t = sz[j];
      int m = max(s, t);
      // Calculate power based on word lengths
      x += m * m + (m << 2);
      x += (s + s + 1) * (t + t);
      x += (s < t ? s + 1 : s > t ? t : 0);
      x += (s >= t ? s + 2 : 0);
      db[x] = {i, j}; // Store the mapping from power to word indices
    }
  }
}
void solveMain() {
  int n;
  cin >> n;
  // Output the magic words
  for (int i = 0; i < n; i++) {
    cout << ar[i] << endl;
  }
  int q;
  cin >> q;
  // Process each query
  while (q--) {
    int p;
    cin >> p;
    pairii &ans = db[p];
    cout << ans.F + 1 << " " << ans.S + 1 << endl; // Output indices (1-based)
  }
}
int main() {
  fastio;
  int t = 1;
  setup();
  while (t--) {
    solveMain();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/