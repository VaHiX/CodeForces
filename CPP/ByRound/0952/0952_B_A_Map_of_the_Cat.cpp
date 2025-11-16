// Problem: CF 952 B - A Map of the Cat
// https://codeforces.com/contest/952/problem/B

/*
 * Problem: Determine if a cat is normal or grumpy based on responses to petting areas.
 * 
 * Approach:
 * - Iterate through all 10 petting areas (0 to 9).
 * - For each area, query the cat's response.
 * - If the response is "no", continue to the next area.
 * - If the response is one of the grumpy phrases, output "grumpy" and terminate.
 * - Otherwise, assume the cat is normal and output "normal".
 * 
 * Time Complexity: O(1) - We loop at most 10 times, which is constant.
 * Space Complexity: O(1) - Only a fixed amount of extra space is used.
 */

#include <iostream>
#include <string>

int main() {
  for (int p = 0; p < 10; p++) {
    std::cout << p << std::endl;          // Query petting area p
    std::string s;
    getline(std::cin, s);                 // Read the cat's response
    if (s == "no") {
      continue;                           // Skip if response is "no"
    }
    if (s == "no way" || s == "don't even" || s == "worse" ||
        s == "go die in a hole" || s == "terrible" || s == "are you serious") {
      std::cout << "grumpy" << std::endl; // Output grumpy if response matches any of the negative phrases
    } else {
      std::cout << "normal" << std::endl; // Otherwise assume normal
    }
    break;                                // Exit after determining the cat's nature
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/