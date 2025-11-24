// Problem: CF 659 C - Tanya and Toys
// https://codeforces.com/contest/659/problem/C

/*
 * Problem: Tanya and Toys
 * Purpose: To determine the maximum number of new toy types Tanya can buy
 *          with a given budget, avoiding duplicates with her existing toys.
 * 
 * Algorithm:
 * - Use a set to store existing toy types for O(log n) lookup.
 * - Iterate through toy types from 1 to 10^9.
 * - For each type not already owned, check if it fits in the remaining budget.
 * - Greedily select the cheapest available toys first to maximize count.
 * 
 * Time Complexity: O(n + k * log n) where k is the number of new toys to buy,
 *                  and n is the number of existing toys.
 * Space Complexity: O(n) for storing existing toys in a set.
 */

#include <iostream>
#include <set>
#include <vector>
int main() {
  const long N = 1000000000;
  long n, m;
  std::cin >> n >> m;
  std::set<long> existing; // Store existing toy types for quick lookup
  for (long p = 0; p < n; p++) {
    long x;
    std::cin >> x;
    existing.insert(x); // Insert existing toy types into set
  }
  std::vector<long> tobuy; // Vector to store toy types to buy
  for (long p = 1; p <= N; p++) {
    if (existing.count(p) > 0) {
      continue; // Skip if toy type already exists
    }
    if (p <= m) {
      tobuy.push_back(p); // Buy this toy if within budget
      m -= p; // Deduct cost from remaining budget
    } else {
      break; // No more toys can be bought due to budget constraints
    }
  }
  std::cout << tobuy.size() << std::endl; // Output number of toys to buy
  for (long p = 0; p < tobuy.size(); p++) {
    std::cout << tobuy[p] << " "; // Output toy types to buy
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/