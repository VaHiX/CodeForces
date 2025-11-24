// Problem: CF 549 B - Looksery Party
// https://codeforces.com/contest/549/problem/B

// # Looksery Party
// ## Problem Description
// We are given a company with `n` employees, each having a contact list
// represented as a binary matrix. When an employee comes to a party, they send
// messages to all their contacts (including themselves). Igor predicts how many
// messages each employee will receive. We need to determine if there's a way to
// choose which employees attend the party so that Igor's predictions are all
// wrong.

// ## Approach
// The key insight is to systematically process employees who Igor predicts
// should receive 0 messages. For each such employee, we force them to attend
// the party, which ensures they receive exactly 1 message (from themselves),
// making Igor's prediction incorrect. Then we adjust predictions for other
// employees based on who sent messages.

// ## Time and Space Complexity
// - **Time Complexity**: O(n^3) - The nested loops for processing, and
// potentially up to n iterations where each iteration processes all n elements.
// - **Space Complexity**: O(n^2) - For storing the contact matrix.

#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  // Create adjacency matrix to represent contact lists
  std::vector<std::vector<bool>> g(n, std::vector<bool>(n, 0));
  for (int row = 0; row < n; row++) {
    std::string s;
    std::cin >> s;
    for (int col = 0; col < s.size(); col++) {
      g[row][col] = s[col] - '0'; // Convert char '0'/'1' to bool
    }
  }
  // Read Igor's predictions
  std::vector<int> a(n);
  for (int p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  // Flag to indicate when we're done with adjustments
  bool done(false);
  // Vector to store which employees attend the party
  std::vector<int> guests;

  // Continue until all predictions that are 0 can be corrected
  while (!done) {
    done = true;
    // Process each employee
    for (int p = 0; p < n; p++) {
      // If Igor predicted 0 messages for employee p
      if (a[p] != 0) {
        continue; // Skip this employee
      }
      // If we get here, Igor predicted 0 but the actual count must be > 0
      done = false; // Need to make adjustments
      // Force employee p to attend party
      guests.push_back(p);
      // Adjust predictions for all employees based on p's messages
      for (int q = 0; q < n; q++) {
        a[q] -= g[p][q]; // Reduce predicted count by 1 if employee q is in p's
                         // contact list
      }
      break; // Process one employee at a time and restart
    }
  }

  // Output number of guests and their indices (1-indexed)
  std::cout << guests.size() << std::endl;
  for (int p = 0; p < guests.size(); p++) {
    std::cout << (1 + guests[p]) << std::endl; // Convert to 1-indexed
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/