// Problem: CF 1234 B2 - Social Network (hard version)
// https://codeforces.com/contest/1234/problem/B2

/*
B2. Social Network (hard version)
Algorithm: Simulate a sliding window with a set to maintain recent conversations.
Time Complexity: O(n * log k) - Each insertion and deletion in the set takes O(log k) time.
Space Complexity: O(k) - Space used by the set and vector to store up to k conversations.

The problem simulates a social network conversation list where:
- At most k conversations are displayed.
- When a new message comes from a friend not currently shown, it moves to front.
- If already shown, no change.
- When full and new message arrives, the last conversation is removed.
*/
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::set<long> s; // Set to store active conversation IDs for O(log k) lookup
  std::vector<long> v(k, 0); // Vector to maintain order of conversations
  long idx(0); // Index to track position in vector (circular buffer)
  for (long p = 0; p < n; p++) {
    long w;
    scanf("%ld", &w);
    if (s.count(w)) { // If conversation already exists, do nothing
      continue;
    }
    s.erase(v[idx]); // Remove the conversation that will be replaced
    s.insert(w); // Add new conversation
    v[idx++] = w; // Store it in vector
    idx %= k; // Circular indexing
  }
  printf("%ld\n", s.size()); // Print number of active conversations
  long start = (idx - 1 + k) % k; // Find last inserted index to print correctly
  for (long p = 0; p < k; p++) {
    long id = v[(k + start - p) % k]; // Traverse in reverse order
    if (id <= 0) { // Skip empty slots
      continue;
    }
    printf("%ld ", id);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/