// Problem: CF 776 A - A Serial Killer
// https://codeforces.com/contest/776/problem/A

/*
 * Problem: A Serial Killer
 * 
 * Purpose: To simulate the serial killer's selection process of victims over n days,
 *          where each day one victim is killed and replaced by a new person. 
 *          The goal is to output the pair of potential victims available at the start of each day.
 * 
 * Algorithm:
 * - Use a set data structure to maintain the two current potential victims.
 * - Initially, insert the two starting victims into the set.
 * - For each day:
 *   - Read the victim killed and the new person replacing them.
 *   - Remove the killed victim from the set.
 *   - Insert the new person into the set.
 *   - Output the two remaining victims in the set.
 * 
 * Time Complexity: O(n * log(2)) = O(n), where n is the number of days.
 *                    Each insert and erase operation on a set with at most 2 elements is O(log(2)) = O(1).
 * 
 * Space Complexity: O(1), since the set always contains at most 2 elements regardless of the input size.
 */

#include <iostream>
#include <set>
#include <string>

int main() {
  std::set<std::string> a;  // Set to store current two potential victims
  std::string x, y;
  std::cin >> x >> y;
  a.insert(x);  // Insert first initial victim
  a.insert(y);  // Insert second initial victim
  std::cout << (*a.begin()) << " " << (*(++a.begin())) << std::endl;  // Output initial pair
  int n;
  std::cin >> n;
  while (n--) {
    std::cin >> x >> y;
    a.erase(x);  // Remove the victim who was killed
    a.insert(y);  // Add the new person who replaced the victim
    std::cout << (*a.begin()) << " " << (*(++a.begin())) << std::endl;  // Output current pair
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/