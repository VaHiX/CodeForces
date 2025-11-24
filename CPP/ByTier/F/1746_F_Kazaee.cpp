// Problem: CF 1746 F - Kazaee
// https://codeforces.com/contest/1746/problem/F

/*
 * Problem: F. Kazaee
 * Algorithm: Binary Indexed Tree (Fenwick Tree) with Bitmaps for frequency checking
 * Time Complexity: O((n + q) * log(n) * 31) 
 * Space Complexity: O(n * 31 + unique_elements)
 * 
 * The solution uses a technique where each number is mapped to a random 64-bit 
 * integer. Using bitwise operations on these integers, we can efficiently check 
 * the parity of occurrences of elements in a given range.
 * 
 * For each query of type 1 (update), we update the BITs accordingly.
 * For each query of type 2 (check), we use BITs to compute the sum of bits 
 * for each of the 31 bits across the range. If all sums are divisible by k, 
 * then every element's count is divisible by k.
 */

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <random>

using namespace std;
int t[64][300005]; // BITs for 31 bits of each number
map<int, unsigned long long> b; // Maps numbers to random 64-bit integers
int n, q, k;
int a[300005], c[300005]; // a stores the array, c unused but declared

// Function to update BIT at position x with value y
void add(int o, int x, int y) {
  while (x <= n)
    t[o][x] += y, x += x & -x; // Add y to BIT at x and all its ancestors
}

// Function to add or remove a number's contribution to BITs
void Add(int x, int y) {
  for (int i = 0; i < 31; i++)
    if ((b[a[x]] >> i) & 1) // Check if i-th bit is set in b[a[x]]
      add(i, x, y); // Update the corresponding BIT
}

// Query BIT at position x for a specific bit
int query(int o, int x) {
  if (x == 0)
    return 0;
  int res = 0;
  while (x)
    res += t[o][x], x -= x & -x; // Sum up the values from x to root
  return res;
}

// Checks if all element frequencies in range [l,r] are multiples of k
bool Query(int l, int r) {
  for (int i = 0; i < 31; i++)
    if ((query(i, r) - query(i, l - 1)) % k != 0) // Check if sum of bits in range is divisible by k
      return 0;
  return 1;
}

mt19937 fsb(time(NULL)); // Random number generator

// Function to ensure a number has an associated random 64-bit integer
void fsbb(int x) {
  if (!b.count(x))
    b[x] = fsb(); // Assign a random number to x if not already present
}

int main() {
  std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i], fsbb(a[i]), Add(i, 1); // Initialize array and BITs
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int i, x;
      cin >> i >> x;
      fsbb(x); // Ensure x has a random number
      Add(i, -1); // Remove old value
      a[i] = x; // Update array
      Add(i, 1); // Add new value
    } else {
      int l, r;
      cin >> l >> r;
      cin >> k;
      puts(Query(l, r) ? "YES" : "NO"); // Output result of query
    }
  }
}


// https://github.com/VaHiX/CodeForces/