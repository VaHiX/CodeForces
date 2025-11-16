// Problem: CF 2097 D - Homework
// https://codeforces.com/contest/2097/problem/D

/*
Algorithm/Techniques: Gaussian elimination on binary strings to determine if two strings can be transformed into each other using allowed operations.
Time Complexity: O(n^2 / 64) per test case, where n is the length of the strings.
Space Complexity: O(n^2 / 64) for storing the binary vectors and auxiliary data structures.

The problem involves determining if two binary strings can be made equal using a specific set of operations:
- Split a string into two equal halves
- Apply XOR operation between corresponding bits of the halves (either in x or y)
- Recursively apply operations to the halves

This can be modeled as a system of linear equations in GF(2) (binary field).
The approach uses Gaussian elimination on the bit vectors to find if the two strings belong to the same linear space.
*/
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
typedef unsigned long long ull;
const int maxn = 1e6 + 5;
  
// BITSET class for handling binary vectors efficiently
struct BITSET {
  vector<ull> vec;
  void clear() { vec.clear(); }
  bool any() {
    for (int i = 0; i < vec.size(); i++)
      if (vec[i])
        return true;
    return false;
  }
  int _Find_first() {
    for (int i = 0; i < vec.size(); i++)
      if (vec[i])
        return __builtin_ctzll(vec[i]) | (i << 6);
    return -1;
  }
} bt[2][1005], tmp;

// XOR operation between two bitsets
void XOR(BITSET &A, BITSET &B) {
  int x = max(A.vec.size(), B.vec.size());
  A.vec.resize(x);
  for (int i = 0; i < B.vec.size(); i++)
    A.vec[i] ^= B.vec[i];
}

char s[2][maxn];
int pos[2][maxn], tot[2];

// Insert a bitset into the basis
void ins(int op) {
  while (tmp.any()) {
    int p = tmp._Find_first();
    if (!pos[op][p]) {
      pos[op][p] = ++tot[op], bt[op][tot[op]] = tmp;
      break;
    } else
      XOR(tmp, bt[op][pos[op][p]]);
  }
}

// Try inserting a bitset, returns true if it was linearly dependent
bool tryins(int op) {
  while (tmp.any()) {
    int p = tmp._Find_first();
    if (!pos[op][p])
      return true;
    else
      XOR(tmp, bt[op][pos[op][p]]);
  }
  return false;
}

// Initialize a bitset from a segment of string
void init(int op, int l, int r) {
  tmp.vec.resize(((r - l) >> 6) + 1);
  for (int i = l; i < r; i += 64) {
    ull S = 0;
    for (int j = i; j < r && j < i + 64; j++)
      S |= ((ull)(s[op][j] == '1') << (j - i));
    tmp.vec[(i - l) >> 6] = S;
  }
}

// Work function to solve each test case
void work() {
  int n;
  cin >> n >> s[0] >> s[1];
  tot[0] = tot[1] = 0;
  int x = n, y = 1;
  // Find the largest power of 2 that divides n
  while (!(x & 1))
    x >>= 1, y <<= 1;
  // Initialize the basis for both strings by splitting into blocks
  for (int op = 0; op < 2; op++)
    for (int i = 0; i < n; i += x)
      init(op, i, i + x), ins(op);
  
  bool Fl = true;
  // Check if both strings have the same rank
  if (tot[0] != tot[1])
    Fl = false;
  // Try to express the basis of first string in terms of the second
  for (int i = x - 1; ~i && Fl; i--)
    if (pos[0][i]) {
      tmp = bt[0][pos[0][i]];
      if (tryins(1)) {
        Fl = false;
        break;
      }
    }
  // Clear memory
  for (int i = x - 1; ~i; i--)
    if (pos[0][i])
      bt[0][pos[0][i]].clear(), pos[0][i] = 0;
  for (int i = x - 1; ~i; i--)
    if (pos[1][i])
      bt[1][pos[1][i]].clear(), pos[1][i] = 0;
  cout << (Fl ? "Yes\n" : "No\n");
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/