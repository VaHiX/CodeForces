// Problem: CF 732 D - Exams
// https://codeforces.com/contest/732/problem/D

/*
Purpose: Determine the minimum number of days needed for Vasiliy to pass all exams,
         considering preparation time and available exam days.

Algorithms/Techniques:
- Binary search on the answer (number of days)
- Greedy assignment of exam days to subjects
- Queue to simulate preparation and exam scheduling

Time Complexity: O(n * log(n)) where n is the number of days
Space Complexity: O(n + m) for storing day assignments and preparation times

*/
#include <cstdio>
#include <queue>
#include <vector>

// Function to check if it's possible to pass all exams within 'upper' days
bool check(const std::vector<long> &avail, std::vector<long> prep, long ns,
           long upper) {
  std::vector<long> lastDay(ns + 1, -1); // Track last day each subject's exam can be taken
  long count(0);
  for (long day = upper; day >= 0; day--) {
    long subject = avail[day]; // Get subject available on this day
    if (subject <= 0) {
      continue; // Skip if no exam is available on this day
    }
    if (lastDay[subject] <= 0) {
      ++count; // Count unique subjects that have exam day
      lastDay[subject] = day;
    }
  }
  if (count < ns) {
    return false; // Not enough exam days available for all subjects
  }
  std::queue<long> q; // Queue to track which subjects are being prepared
  for (long day = upper; day >= 0; day--) {
    long subject = avail[day];
    if (lastDay[subject] == day) {
      // If this is the last day this subject's exam can be taken, push it to queue
      q.push(subject);
    } else if (q.size() > 0) {
      // Otherwise, we're not at last day of exam, so start preparing subject
      long current = q.front();
      --prep[current]; // Decrease preparation time needed
      if (prep[current] <= 0) {
        q.pop(); // Finished preparing, remove from queue
      }
    }
  }
  return q.empty(); // Return true if all subjects are prepared (queue is empty)
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> d(n, 0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &d[p]);
  }
  std::vector<long> a(m + 1, 0);
  for (long p = 1; p <= m; p++) {
    scanf("%ld", &a[p]);
  }
  bool possible(false);
  long left(0), right(n - 1);
  while (left <= right) {
    long mid = (left + right) / 2;
    if (check(d, a, m, mid)) {
      right = mid - 1;  // Try for smaller number of days
      possible = true;
    } else {
      left = mid + 1;   // Try for more days
    }
  }
  printf("%ld\n", possible ? (left + 1) : (-1)); // Output result or -1 if impossible
  return 0;
}


// https://github.com/VaHiX/CodeForces/