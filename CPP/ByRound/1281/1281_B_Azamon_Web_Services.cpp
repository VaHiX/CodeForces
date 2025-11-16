// Problem: CF 1281 B - Azamon Web Services
// https://codeforces.com/contest/1281/problem/B

/*
 * Problem: Azamon Web Services
 * 
 * Algorithms/Techniques: 
 *   - Greedy approach to find the best swap to make string lexicographically smaller
 *   - For each position from left to right, find the smallest character to the right and swap
 *   - Check if the resulting string is strictly lexicographically smaller than the competitor's string
 * 
 * Time Complexity: O(n^2) where n is the length of string s
 *   - Outer loop runs n times
 *   - Inner loop runs up to n times in worst case
 *   - Overall complexity is O(n^2)
 * 
 * Space Complexity: O(1) 
 *   - Only using a constant amount of extra space (variables i, x, j)
 *   - No additional data structures that grow with input size
 */

#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    string a, b;
    cin >> a >> b;
    
    // Try to find the best swap to make the string lexicographically smaller
    for (int i = 0; i < a.size(); i++) {
      int x = i; // index of the smallest character found so far to the right
      
      // Look from the end of string towards current position to find smallest character
      for (int j = a.size() - 1; j > i; j--)
        if (a[j] < a[x])
          x = j; // update index if a smaller character is found
      
      // If we found a smaller character to the right, perform the swap
      if (x == i)
        continue; // No improvement possible from this position
      
      swap(a[x], a[i]); // Perform the swap
      break; // We are allowed to make only one swap
    }
    
    // Output result if a is strictly lexicographically smaller than b, otherwise "---"
    cout << ((a < b) ? a : "---") << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/