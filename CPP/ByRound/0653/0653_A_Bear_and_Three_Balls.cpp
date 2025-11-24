// Problem: CF 653 A - Bear and Three Balls
// https://codeforces.com/contest/653/problem/A

/*
Purpose: To determine if Limak can choose three distinct ball sizes such that 
         no two sizes differ by more than 2. This is achieved by checking all 
         combinations of three consecutive sizes in a sorted list of unique sizes.

Algorithms/Techniques: 
- Use a set to store unique ball sizes.
- Sort the unique sizes.
- Check for any three consecutive elements in the sorted list where the difference 
  between the largest and smallest is at most 2.

Time Complexity: O(n log n) due to sorting the unique elements.
Space Complexity: O(n) for storing unique sizes in a vector and a set.

*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
int main() {
  int n;
  std::cin >> n;
  std::set<int> sizeSet; // Store unique ball sizes
  std::vector<int> sizeVec; // Vector to hold sorted unique sizes
  for (int p = 0; p < n; p++) {
    int x;
    std::cin >> x;
    if (sizeSet.count(x) > 0) {
      continue; // Skip if size already exists
    }
    sizeSet.insert(x);
    sizeVec.push_back(x);
  }
  sort(sizeVec.begin(), sizeVec.end()); // Sort unique sizes
  bool possible(0); // Flag to indicate if valid triplet exists
  for (int p = 2; p < sizeVec.size(); p++) {
    // Check if three consecutive sizes form a valid triplet
    if (sizeVec[p - 1] == sizeVec[p] - 1 && sizeVec[p - 2] == sizeVec[p] - 2) {
      possible = 1;
      break;
    }
  }
  puts(possible ? "YES" : "NO"); // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/