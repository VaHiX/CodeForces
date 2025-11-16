// Problem: CF 753 A - Santa Claus and Candies
// https://codeforces.com/contest/753/problem/A

/*
Purpose: This program determines the maximum number of children Santa Claus can give candies to such that each child receives a distinct positive integer number of candies, and all n candies are distributed.

Algorithm:
- Start by giving 1 candy to the first child, 2 to the second, 3 to the third, etc., until we run out of candies.
- If there are remaining candies after this process, distribute them one by one to the children starting from the last child to maintain distinctness and avoid giving zero candies.

Time Complexity: O(√n) - In the worst case, we iterate up to sqrt(n) times in the first loop.
Space Complexity: O(√n) - The vector stores at most √n elements.

Techniques:
- Greedy approach to distribute candies
- Efficient distribution of leftover candies
*/

#include <iostream>
#include <vector>
int main() {
  long n;
  std::cin >> n;
  std::vector<long> a;
  // First loop: assign increasing number of candies to children
  // until we run out of candies
  for (long p = 1; p <= n; p++) {
    a.push_back(p); // Give p candies to current child
    n -= p;         // Reduce remaining candies
  }
  // Second loop: redistribute remaining candies to last children
  // to ensure all n candies are used and still keep distinct values
  for (long p = a.size() - 1; p >= 0 && n > 0; p--) {
    ++a[p];  // Add one more candy to child at index p
    --n;     // Decrease remaining candy count
  }
  // Output the result
  std::cout << a.size() << std::endl; // Print number of children
  for (long p = 0; p < a.size(); p++) {
    std::cout << a[p] << " "; // Print candies per child
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/