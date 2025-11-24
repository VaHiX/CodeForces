// Problem: CF 704 A - Thor
// https://codeforces.com/contest/704/problem/A

/*
 * Code Purpose:
 * This program simulates a notification system on a smartphone where Thor can:
 * 1. Generate a notification for an app (notification is unread).
 * 2. Read all notifications from a specific app (marks them as read).
 * 3. Read the first 't' notifications generated so far (regardless of app).
 * 
 * Data Structures Used:
 * - 'a' vector: stores timestamps of all notifications generated.
 * - 'b' 2D vector: for each application, stores the timestamps of its notifications.
 * - 'st' set: keeps track of unread notification timestamps.
 *
 * Time Complexity: O(q * log(q)) due to set operations (insert, erase) and loop over app notifications.
 * Space Complexity: O(q) for storing the notification timestamps and vectors.
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  std::set<long> st;                   // Set to keep track of unread notification timestamps
  std::vector<long> a;                 // Vector to store all generated notification timestamps
  std::vector<std::vector<long>> b(n + 1); // Vector of vectors to store notification timestamps per app
  long last(0);                        // Pointer to track how many of the first notifications have been read
  for (long t = 0; t < q; t++) {
    long w, x;
    scanf("%ld %ld", &w, &x);
    if (w == 1) {
      a.push_back(t);                  // Record timestamp of notification
      b[x].push_back(t);               // Record timestamp for respective app
      st.insert(t);                    // Insert into set of unread notifications
    } else if (w == 2) {
      for (int u = 0; u < b[x].size(); ++u) {
        st.erase(b[x][u]);             // Remove notifications of app x from unread set
      }
      b[x].clear();                    // Clear notifications of app x
    } else if (w == 3) {
      while (last < x) {               // Read first x notifications
        st.erase(a[last]);             // Remove from unread set
        last++;                        // Move pointer forward
      }
    }
    printf("%ld\n", st.size());        // Print current number of unread notifications
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/