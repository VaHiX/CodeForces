// Problem: CF 1862 B - Sequence Game
// https://codeforces.com/contest/1862/problem/B

/*
 * Code Purpose:
 * This program reconstructs a sequence 'a' from a given sequence 'b', where 'b' is 
 * formed by taking elements from 'a' that are greater than or equal to the previous 
 * element in 'a'. The process starts with the first element of 'a'.
 * 
 * Algorithm:
 * - For each element in the input sequence 'b', we simulate the reverse process.
 * - We append the current element to the result sequence 'v'.
 * - If the last element in the result sequence is greater than the current element,
 *   we insert the current element again to maintain the rule that only elements 
 *   greater than or equal to the previous one are kept in 'b'.
 * 
 * Time Complexity: O(n) per test case, where n is the length of sequence b.
 * Space Complexity: O(n) for storing the reconstructed sequence 'a'.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (!v.empty() && v.back() > x) {
        // If the last element in the sequence is greater than current,
        // insert the current element to ensure it's included in the valid sequence.
        v.push_back(x);
      }
      // Always append the current element to the result.
      v.push_back(x);
    }
    printf("%ld\n", v.size());
    for (long p = 0; p < v.size(); p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/