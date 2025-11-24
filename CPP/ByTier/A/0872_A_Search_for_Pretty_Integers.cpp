// Problem: CF 872 A - Search for Pretty Integers
// https://codeforces.com/contest/872/problem/A

/*
 * Problem: Search for Pretty Integers
 * 
 * Algorithm/Techniques: 
 *   - Use a frequency array to track which digits appear in both lists.
 *   - Find the minimum digit in each list.
 *   - If a digit exists in both lists, output that single digit (smallest possible).
 *   - Otherwise, form the smallest two-digit number using the minimum digits from each list.
 * 
 * Time Complexity: O(n + m + 1) = O(n + m), where n and m are the sizes of the two lists.
 * Space Complexity: O(1), since we use a fixed-size array of size 15 (0 to 14), which is constant.
 */

#include <iostream>
#include <algorithm>

using namespace std;

int n, m, a, x = 9, y = 9, v[15]; // v[15] is used to count occurrences of digits (0-9), x and y track min digits

int main() {
  cin >> n >> m; // Read the sizes of two lists

  // Process first list
  while (n--) {
    cin >> a; // Read a digit from first list
    x = min(x, a); // Track minimum digit in first list
    v[a]++; // Increment frequency count for this digit
  }

  // Process second list
  while (m--) {
    cin >> a; // Read a digit from second list
    y = min(y, a); // Track minimum digit in second list
    v[a]++; // Increment frequency count for this digit
  }

  // Check if there's a digit common to both lists
  for (int i = 1; i <= 9; i++) // Loop through digits 1 to 9
    if (v[i] == 2) { // If digit i appears in both lists
      cout << i; // Output this digit
      return 0; // Exit program
    }

  // If no common digit, create smallest 2-digit number with min from each list
  cout << min(x, y) << max(x, y); // Output smaller min followed by larger min

  return 0;
}


// https://github.com/VaHiX/CodeForces/