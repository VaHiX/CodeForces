// Problem: CF 931 C - Laboratory Work
// https://codeforces.com/contest/931/problem/C

/*
 * Problem: Laboratory Work
 * 
 * Purpose: 
 *   The task is to generate a set of n integer measurements for Anya such that:
 *   1. The average of her measurements equals the average of Kirill's measurements.
 *   2. All her measurements are within the same bounds as Kirill's.
 *   3. The number of equal measurements between Anya and Kirill is minimized.
 * 
 * Algorithm:
 *   - Count frequencies of each value in Kirill's data.
 *   - Handle special case where there are only two distinct values and the gap is > 1.
 *   - Adjust the frequency distribution to minimize overlapping measurements, especially when there are 3 or more distinct values.
 *   - Output the final adjusted distribution.
 * 
 * Time Complexity: O(n)
 *   - Reading input: O(n)
 *   - Building map and vectors: O(n)
 *   - Computing overlaps: O(1)
 *   - Printing result: O(n)
 * 
 * Space Complexity: O(n)
 *   - Map and vectors store at most n elements.
 * 
 * Techniques:
 *   - Frequency counting
 *   - Special handling for small number of distinct values
 *   - Greedy adjustment of frequencies
 */

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n);
  std::map<long, long> m;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++m[x]; // Count frequency of each value
  }
  std::vector<long> keys, values;
  for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
    keys.push_back(it->first); // Collect unique values
    values.push_back(it->second); // Collect their frequencies
  }
  
  // Special case: If there are exactly two distinct values and their difference is more than 1
  if (keys.size() == 2 && keys[1] - keys[0] > 1) {
    --keys.back(); // Change last key to be one less than it was
    keys.push_back(1 + keys.back()); // Add next value to the sequence
    long x = values.back(); // Save the frequency of the last value
    values.back() = 0; // Set its frequency to 0
    values.push_back(x); // Add it to the end with new key
  }
  
  long same(n); // Initialize count of same elements as total
  if (keys.size() > 2) { // If there are more than 2 distinct values
    // Calculate the minimum overlaps that can occur
    long ta = (values[0] < values[2]) ? values[0] : values[2];
    long tb = values[1] / 2; 
    
    if (ta > tb) {
      // Adjust frequencies to reduce overlaps
      values[0] -= ta;
      values[1] += 2 * ta;
      values[2] -= ta;
    } else {
      values[0] += tb;
      values[1] -= 2 * tb;
      values[2] += tb;
    }
    same = n - 2 * ((ta > tb) ? ta : tb); // Minimize number of matches
  }
  
  printf("%ld\n", same); // Print minimum number of matches

  // Output the final set of values
  for (long p = 0; p < keys.size(); p++) {
    while (values[p]--) {
      printf("%ld ", keys[p]); // Print out all values based on adjusted frequencies
    }
  }
  puts(""); // Print newline at the end
  return 0;
}


// https://github.com/VaHiX/CodeForces/