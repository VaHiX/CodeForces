// Problem: CF 610 C - Harmony Analysis
// https://codeforces.com/contest/610/problem/C

/*
 * Problem: Harmony Analysis
 * 
 * Description:
 * Given an integer k, construct 2^k vectors in 2^k-dimensional space such that:
 * - Each vector has coordinates of either +1 or -1
 * - Any two distinct vectors are orthogonal (their dot product is 0)
 * 
 * This problem is a classic application of constructing Hadamard matrices.
 * 
 * Algorithm:
 * - Start with a single vector "+"
 * - Iteratively double the number of vectors using a construction method:
 *   For each existing vector v, create two new vectors:
 *   1. v + v (append v to itself)
 *   2. v + complement(v) (append v with its complement where + becomes * and * becomes +)
 * - The process builds a Hadamard matrix in terms of + and * representations
 * 
 * Time Complexity: O(2^(2*k)) - since we construct 2^k vectors of length 2^k each
 * Space Complexity: O(2^(2*k)) - for storing the vectors
 */

#include <iostream>
#include <vector>
#include <string>

// Function to return complement of a string, replacing x with y and vice versa
std::string complement(std::string s, char x, char y) {
  std::string res(s);
  for (int p = 0; p < s.size(); p++) {
    res[p] = ((s[p] == x) ? y : x);
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  const char a = '+';  // represent +1
  const char b = '*';  // represent -1
  long n;
  std::cin >> n;
  std::vector<std::string> ans;
  std::string initial(1, a);  // Start with one vector "+"
  ans.push_back(initial);
  
  // Iteratively build up the Hadamard matrix
  for (int p = 0; p < n; p++) {
    long len = ans.size();  // Current number of vectors
    for (long p = 0; p < len; p++) {
      std::string prev = ans[p];  // Store previous vector
      ans[p] += ans[p];           // Append the vector to itself (v + v)
      ans.push_back(prev + complement(prev, a, b));  // Append complement (v + complement(v))
    }
  }
  
  // Output all constructed vectors
  for (long p = 0; p < ans.size(); p++) {
    std::cout << ans[p] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/