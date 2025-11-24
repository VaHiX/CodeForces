// Problem: CF 447 B - DZY Loves Strings
// https://codeforces.com/contest/447/problem/B

/*
Purpose: Calculate the maximum possible value of a string after inserting k lowercase letters.
         The value of a string is calculated as the sum of (position * value_of_character_at_position).
         We insert k characters optimally to maximize the total value.

Algorithms/Techniques: Greedy algorithm
                       - For each character in the original string, we calculate its contribution to the total value
                       - For the k inserted characters, we insert the highest valued character at the end to maximize contribution

Time Complexity: O(n + k) where n is the length of the initial string and k is the number of characters to insert
Space Complexity: O(1) as we use only a fixed-size vector (26 elements) and a few variables

*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string initial; // Read the initial string
  getline(std::cin, initial);
  long k; // Read the number of characters to insert
  scanf("%ld\n", &k);
  const int N = 26; // Number of lowercase letters
  std::vector<long> valueVec(N); // Store the values of each letter a-z
  long highest(0); // Track the highest value among all letters
  for (int p = 0; p < N; p++) {
    scanf("%ld", &valueVec[p]); // Read the value for each letter
    if (valueVec[p] > highest) { // Keep track of highest value
      highest = valueVec[p];
    }
  }
  long output(0); // Initialize the result value
  for (int p = 0; p < initial.size(); p++) {
    // Calculate contribution of each character in the initial string to the total value
    output += (p + 1) * valueVec[initial[p] - 'a'];
  }
  for (int p = 0; p < k; p++) {
    // Add contributions from k inserted characters
    // Since we want maximum value, we insert the highest valued character
    // at the end to maximize its position contribution (p + 1 + initial.size())
    output += (p + 1 + initial.size()) * highest;
  }
  printf("%ld\n", output); // Print the final result
  return 0;
}


// https://github.com/VaHiX/CodeForces/