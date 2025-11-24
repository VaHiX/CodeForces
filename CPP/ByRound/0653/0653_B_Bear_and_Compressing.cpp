// Problem: CF 653 B - Bear and Compressing
// https://codeforces.com/contest/653/problem/B

/*
Algorithm/Techniques: Backtracking with brute force
- The problem requires counting all possible strings of length n that can be reduced to a single character 'a' using given operations.
- We use a brute-force approach to generate all possible strings of length n (using base-6 representation).
- For each generated string, we simulate the compression process using a transition matrix.
- Time Complexity: O(6^n * n), where n is the length of the string. In worst case, we iterate through all 6^n strings and for each, we may perform up to n operations.
- Space Complexity: O(1) - The transition matrix is fixed size (6x6) and the vectors used are proportional to input size but bounded.

*/

#include <iostream>
#include <vector>
#include <string>

// Converts a number into a vector of digits in base B with specified length
std::vector<int> getVec(int x, int len, int B) {
  std::vector<int> v(len, 0);
  for (int p = 0; p < len; p++) {
    v[p] = x % B;
    x /= B;
  }
  return v;
}

// Simulates compression process from a list of characters
bool convert(std::vector<int> v, const std::vector<std::vector<int>> &m,
             int target) {
  bool done(v.size() <= 1);
  while (!done) {
    if (v.size() <= 1) {
      break;
    }
    int a = v.size() - 1;
    int b = m[v[a]][v[a - 1]]; // Get operation result for last two characters
    if (b < 0) {
      break; // No valid operation found
    }
    v.pop_back();
    v.pop_back();
    v.push_back(b);
  }
  if (v.size() == 1 && v[0] == target) { // Check if result is 'a'
    return true;
  }
  return false;
}

int main() {
  const int L = 6; // Number of possible characters (a-f)
  int n, q;
  std::cin >> n >> q;
  
  // Transition matrix: m[i][j] = result of applying operation on characters i,j
  std::vector<std::vector<int>> m(L, std::vector<int>(L, -1));
  
  // Read operations and populate the transition matrix
  while (q--) {
    std::string key;
    char c;
    std::cin >> key >> c;
    m[key[0] - 'a'][key[1] - 'a'] = c - 'a';
  }
  
  // Generate all possible strings of length n using base-6
  long total(1);
  for (int p = 0; p < n; p++) {
    total *= L;
  }
  
  long count(0);
  for (long p = 0; p < total; p++) {
    std::vector<int> v = getVec(p, n, L);
    count += convert(v, m, 0); // 0 represents 'a'
  }
  
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/