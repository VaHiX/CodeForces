// Problem: CF 1382 C1 - Prefix Flip (Easy Version)
// https://codeforces.com/contest/1382/problem/C1

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a;
    std::cin >> a;
    std::string b;
    std::cin >> b;
    std::vector<long> moves;
    for (long p = 0; p < a.size(); p++) {
      if (a[p] == b[p]) {
        // If the bits at position p are already equal, no action needed
        continue;
      }
      // To fix the bit at position p, we perform three operations:
      // 1. Flip prefix of length (p+1) to align the current bit
      // 2. Flip prefix of length 1 to toggle the bit at position 0
      // 3. Flip prefix of length (p+1) again to restore alignment
      moves.push_back(p + 1);
      moves.push_back(1);
      moves.push_back(p + 1);
    }
    std::cout << moves.size() << " ";
    for (long p = 0; p < moves.size(); p++) {
      std::cout << moves[p] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}

/*
Algorithm: 
The algorithm uses a greedy approach to align string a with string b by fixing bits one by one from left to right. 
For each bit that does not match, it performs three specific flip operations to correct the mismatch while maintaining correctness of previously fixed bits.

Time Complexity: O(n^2)
- Outer loop iterates over n characters.
- For each character, in the worst case we push up to 3 elements into the moves vector.
- In the worst case (for n=1000), total operations are bounded by 3*n = 3000, so the time complexity depends on both n and number of mismatches.

Space Complexity: O(n)
- The moves vector stores at most 3*n operations.
- Additional space usage is constant.
*/

// https://github.com/VaHiX/CodeForces/