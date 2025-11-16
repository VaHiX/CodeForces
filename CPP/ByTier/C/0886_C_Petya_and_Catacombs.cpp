// Problem: CF 886 C - Petya and Catacombs
// https://codeforces.com/contest/886/problem/C

/*
 * Problem: C. Petya and Catacombs
 * 
 * Purpose: 
 *   Determine the minimum number of rooms in the catacombs based on Petya's logbook.
 *   Each entry t_i in the logbook represents the last time Petya was in the room he is currently in.
 *   If the room was visited before, t_i is the previous visit time; otherwise, it's an arbitrary value < current time.
 * 
 * Approach:
 *   - For each note in the logbook, we track the set of "last visit times" seen so far.
 *   - The minimum number of rooms is determined by how many distinct "last visit times" 
 *     we see in the logbook. Because each unique t_i corresponds to a unique room.
 *   - We compute (n + 1 - number_of_unique_times) to get the minimum number of rooms.
 *   - Why? When Petya visits room x at time i, and the note in the log is t_i:
 *     - If t_i is 0, it means this is the first time visiting the room (and not a repeat of any previous room).
 *     - If t_i was seen before, it represents a repeat of a previously visited room.
 *     - So the number of unique previous times tells us how many rooms were needed to account for all these notes.
 * 
 * Time Complexity: O(n log n)
 *   - We iterate through the logbook once: O(n)
 *   - Each insertion into the set takes O(log n) time in the worst case
 *   - Therefore total time is O(n log n)
 * 
 * Space Complexity: O(n)
 *   - We store at most n elements in the set in the worst case
 * 
 * Algorithms/Techniques:
 *   - Set data structure to maintain unique values
 *   - Greedy approach to minimize room count based on last visit times
 */

#include <cstdio>
#include <set>
int main() {
  long n;
  scanf("%ld", &n);
  std::set<long> s;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    s.insert(x);  // Insert each note value into the set to count unique values
  }
  printf("%ld\n", n + 1 - s.size());  // Minimum rooms = total notes + 1 - unique last visit times
  return 0;
}


// https://github.com/VaHiX/CodeForces/