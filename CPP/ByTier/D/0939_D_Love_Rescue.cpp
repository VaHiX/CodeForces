// Problem: CF 939 D - Love Rescue
// https://codeforces.com/contest/939/problem/D

#include <iostream>
#include <vector>
#include <string>

/*
 * Problem: Love Rescue
 * 
 * Purpose: To make two strings (Valya's pullover and Tolya's t-shirt) identical
 *          by using minimum mana to buy spells that allow swapping characters.
 *          Each spell allows swapping any occurrence of two characters in both strings.
 * 
 * Algorithm: Union-Find (Disjoint Set Union)
 * 
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function, nearly constant
 * Space Complexity: O(1) since we use fixed size array of 26 elements
 * 
 * Approach:
 * 1. For each position, we check if characters in both strings are different.
 * 2. If they are, we union the characters' indices in the Union-Find structure.
 * 3. After processing all positions, we count how many disjoint groups there are.
 * 4. The number of unions needed gives us the minimum mana.
 * 5. Output the required spell pairs from the Union-Find structure.
 */

long find(std::vector<long> &f, long x) {
  return (x == f[x]) ? x : (f[x] = find(f, f[x])); // Path compression
}

int main() {
  const long N = 26;
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s, t;
  std::cin >> s >> t;
  
  // Union-Find structure to group characters that need to be swapped
  std::vector<long> h(N);
  for (long p = 0; p < N; p++) {
    h[p] = p; // Initialize each character as its own parent
  }
  
  long cnt(0);
  // For each position, union characters from both strings if they differ
  for (long p = 0; p < n; p++) {
    long x(s[p] - 'a'), y(t[p] - 'a'); // Convert to 0-25 index
    long rx(find(h, x)), ry(find(h, y)); // Find root parents
    
    if (rx != ry) {
      h[rx] = ry; // Union the sets
      ++cnt; // Increment counter for number of unions
    }
  }
  
  std::cout << cnt << std::endl;
  
  // Output the required spell pairs
  for (long p = 0; p < N; p++) {
    if (h[p] == p) {
      continue; // Skip if p is the root of its set
    }
    std::cout << (char)('a' + p) << " " << (char)('a' + find(h, p))
              << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/