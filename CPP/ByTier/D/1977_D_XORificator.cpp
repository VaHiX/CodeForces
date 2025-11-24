// Problem: CF 1977 D - XORificator
// https://codeforces.com/contest/1977/problem/D

/*
 * Problem: D. XORificator
 *
 * Algorithm/Technique: Hashing with XOR, Greedy approach
 *
 * Time Complexity: O(n * m * log(n * m)) due to sorting
 * Space Complexity: O(n * m) for storing hash values and pairs
 *
 * Approach:
 * 1. For each column, compute a hash value that represents the "signature" of that column.
 *    This signature is computed by XORing the hash values of all rows where the column has '1'.
 * 2. For each cell (i, j), we compute the new signature if we flip row i (inverting all values in that row).
 *    This gives us the potential new signature for column j after flipping row i.
 * 3. Sort all such (signature, column_index) pairs and find the maximum number of columns
 *    with the same signature, which indicates how many columns would be made special.
 * 4. Choose the best row flip configuration and output the result.
 */

#include <algorithm>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>

template <typename T>
std::istream &operator>>(std::istream &input, std::vector<T> &v) {
  for (T &a : v)
    input >> a;
  return input;
}
void answer(unsigned x, const std::string &y) {
  std::cout << x << '\n';
  std::cout << y << '\n';
}
uint64_t h[300000]; // Precomputed hash values for rows
void initialize() {
  std::mt19937_64 g(time(nullptr));
  for (size_t i = 0; i < 300000; ++i)
    h[i] = g(); // Initialize random hashes
}
void solve(std::vector<std::string> &a) {
  const size_t n = a.size(), m = a[0].size();
  std::vector<std::pair<uint64_t, size_t>> s; // Store <signature, column_index> pairs
  
  // Generate the signature for each column without flipping any rows
  for (size_t j = 0; j < m; ++j) {
    uint64_t v = 0;
    for (size_t i = 0; i < n; ++i) {
      if (a[i][j] == '1')
        v ^= h[i]; // XOR the hash of row i if the cell is '1'
    }
    // For each cell (i, j), calculate what the new signature would be if we flip row i
    for (size_t i = 0; i < n; ++i)
      s.emplace_back(v ^ h[i], i * m + j); // Store the signature and column index
  }
  
  std::sort(s.begin(), s.end()); // Sort by signature to group same signatures together
  
  std::pair<unsigned, uint64_t> x = {0, 0}; // <max_count, index_of_best_column>
  
  // Iterate through sorted signatures to find maximum count of same signatures
  for (size_t i = 0, j = 0; i < s.size(); i = j) {
    while (j < s.size() && s[j].first == s[i].first)
      ++j; // Count all elements with the same signature
      
    if (j - i > x.first) {
      x.first = j - i; // Update max count
      x.second = s[i].second; // Store index of column that caused this count
    }
  }
  
  // Flip the row that makes the maximum number of columns special
  a[x.second / m][x.second % m] ^= 1; // Flip the row represented by x.second / m
  
  // Construct the result string indicating which rows were flipped
  std::string w;
  for (size_t i = 0; i < n; ++i)
    w.push_back(a[i][x.second % m]); // Since all columns are flipped, we need to check if we flipped row i
  
  answer(x.first, w);
}
void test_case() {
  size_t n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  std::cin >> a;
  solve(a);
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  initialize();
  size_t t;
  std::cin >> t;
  while (t-- > 0)
    test_case();
  return 0;
}


// https://github.com/VaHiX/CodeForces/