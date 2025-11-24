// Problem: CF 834 B - The Festive Evening
// https://codeforces.com/contest/834/problem/B

/*
Algorithm/Techniques: 
  - Preprocessing: For each entrance (A-Z), store the first and last time it is used.
  - Simulation: For each guest arrival time, count how many doors are open at that moment.
  - Greedy Check: If at any point more than k doors are open, return "YES".

Time Complexity: O(n^2) 
  - Outer loop: O(n)
  - Inner loop: O(26) = O(1) 
  - Overall: O(n * 26) = O(n)

Space Complexity: O(1) 
  - The vector `a` is fixed size (26 elements), so space is constant.
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  const int N = 26;  // Number of entrances (A-Z)
  // a[i] stores {first_occurrence, last_occurrence} of entrance i
  std::vector<std::pair<long, long>> a(N, std::pair<long, long>(-1, -1));
  long n;  // Number of guests
  int k;   // Number of guards
  std::cin >> n >> k;
  std::string s;  // Sequence of entrances
  std::cin >> s;
  
  // Step 1: Record last occurrence of each entrance
  for (long p = 0; p < s.size(); p++) {
    a[s[p] - 'A'].second = p;  // Update last occurrence
  }

  // Step 2: Record first occurrence of each entrance
  for (long p = s.size() - 1; p >= 0; p--) {
    a[s[p] - 'A'].first = p;   // Update first occurrence
  }

  bool unguarded(false);  // Flag to track if any door is unguarded

  // Step 3: For each guest arrival, check how many doors are open
  for (long p = 0; p < s.size(); p++) {
    int count = 0;  // Count of open doors at time p
    for (int u = 0; u < N; u++) {
      // Check if entrance u is open at time p
      count += (a[u].first <= p) && (p <= a[u].second);
    }
    if (count > k) {  // If more doors are open than guards, then unguarded
      unguarded = true;
      break;
    }
  }

  // Output result
  std::cout << (unguarded ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/