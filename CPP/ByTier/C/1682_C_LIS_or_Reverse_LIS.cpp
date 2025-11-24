// Problem: CF 1682 C - LIS or Reverse LIS?
// https://codeforces.com/contest/1682/problem/C

/*
 * Problem: C. LIS or Reverse LIS?
 * Purpose: Find the maximum possible beauty of an array after rearranging its elements,
 *          where beauty is defined as min(LIS(a), LIS(a')) and a' is the reverse of a.
 * 
 * Approach:
 * - The key insight is that the maximum beauty is determined by how we can distribute
 *   elements to maximize the minimum of LIS(a) and LIS(a').
 * - If we have a frequency map of elements, we want to arrange elements such that
 *   both the original and reversed array have high LIS values.
 * - The optimal arrangement can be approximated using the formula:
 *   max_beauty = (total_elements + count_of_unique_elements_with_frequency <= 2) / 2
 *   But simplified as (number of elements + number of elements that appeared 1 or 2 times) / 2
 * 
 * Time Complexity: O(n log n) due to map operations (insertion and access), where n is the size of array.
 * Space Complexity: O(n) for storing the frequency map.
 */

#include <iostream>
#include <map>

using namespace std;

int main() {
  int t, n, k, a; // t: number of test cases, n: array size, k: current element, a: counter for elements with freq <= 2
  map<int, int> m; // map to store frequency of each element
  cin >> t;
  while (t--) {
    a = 1; // Initialize counter for elements with frequency <= 2
    m.clear(); // Clear the frequency map for new test case
    cin >> n; // Read array size
    while (n--) {
      cin >> k; // Read the next element
      m[k]++; // Increment frequency of k
      a += (m[k] <= 2); // If frequency of k is <= 2, increment a
    }
    cout << a / 2 << endl; // Output the maximum possible beauty
  }
}


// https://github.com/VaHiX/CodeForces/