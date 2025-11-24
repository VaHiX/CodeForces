// Problem: CF 637 A - Voting for Photos
// https://codeforces.com/contest/637/problem/A

/*
 * Purpose: Determine the winning photo in a voting system based on the number of likes.
 *          If multiple photos have the same maximum number of likes, the one that reached
 *          this count first wins.
 *
 * Algorithm: 
 *   - Use a map to keep track of the count of likes for each photo.
 *   - As each like is processed, increment the count for that photo.
 *   - If the current photo's like count becomes greater than the maximum seen so far,
 *     update the maximum and set the current photo as the leader.
 *   - Since input is processed in order, the first photo to reach a new maximum will be chosen.
 *
 * Time Complexity: O(n log n) due to map operations (insert/update) taking O(log n) time each.
 * Space Complexity: O(k) where k is the number of unique photo IDs, as we store counts in a map.
 */

#include <iostream>
#include <map>
int main() {
  std::ios_base::sync_with_stdio(false);
  std::map<long, long> counts;  // Maps photo ID to its like count
  long n;
  std::cin >> n;
  long best(-1), maxCount(-1);  // Track the best photo and its max count
  while (n--) {
    long x;
    std::cin >> x;
    if (counts.count(x)) {
      ++counts[x];  // Increment like count if photo exists
    } else {
      counts[x] = 1;  // Initialize like count for new photo
    }
    if (counts[x] > maxCount) {
      maxCount = counts[x];  // Update maximum like count
      best = x;              // Update the leading photo
    }
  }
  std::cout << best << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/