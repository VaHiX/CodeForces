// Problem: CF 1225 B2 - TV Subscriptions (Hard Version)
// https://codeforces.com/contest/1225/problem/B2

/*
B2. TV Subscriptions (Hard Version)
Algorithm: Sliding window with map to track show occurrences in current window
Time Complexity: O(n * log k) per test case due to map operations
Space Complexity: O(k) for the map storing show indices

The problem asks us to find the minimum number of TV shows to subscribe to,
such that there exists a segment of d consecutive days where all episodes belong
to the subscribed shows. This is solved using a sliding window approach:
- Maintain a window of size d
- Use a map to store the last occurrence index of each show in the current window
- When moving the window, remove the element that's no longer in the window
- The number of unique shows in the window is the count of subscriptions needed

*/

#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, d;
    scanf("%ld %ld %ld", &n, &k, &d);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::map<long, long> s; // Map to store last index of each show in current window
    for (long p = 0; p < d; p++) {
      s[a[p]] = p; // Initialize the first window
    }
    long mn(s.size()); // Minimum subscriptions needed so far
    for (long p = d; p < n; p++) {
      long rem = a[p - d]; // Show that's leaving the window
      long nxt = a[p];     // Show that's entering the window
      if (s[rem] == p - d) {
        s.erase(rem); // Remove show from map if this is its last occurrence in current window
      }
      s[nxt] = p; // Add new show to map with its index
      mn = (mn < s.size()) ? mn : s.size(); // Update minimum subscriptions needed
    }
    printf("%ld\n", mn);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/