// Problem: CF 1185 C1 - Exam in BerSU (easy version)
// https://codeforces.com/contest/1185/problem/C1

#include <cstdio>
#include <vector>
// Problem: C1. Exam in BerSU (easy version)
// Purpose: For each student, find the minimum number of students who must fail 
//          so that this student can finish their exam within M minutes.
// Algorithm: Greedy approach using a histogram of ticket times.
//            For each student, we simulate removing the heaviest students
//            until the cumulative time fits within M.
// Time Complexity: O(n * B) where n is number of students and B is max ticket time (101)
// Space Complexity: O(B) for histogram vector h
int main() {
  const int B = 101; // Maximum possible ticket time + 1
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> h(B, 0); // Histogram to count frequency of each ticket time
  long s(0);                 // Current total time used
  for (long p = 0; p < n; p++) {
    const long t = a[p];     // Time needed by current student
    long cur(s), rem(0);     // cur: current sum, rem: number of students to remove
    // Greedily remove largest ticket times first until we fit within M
    for (long u = B - 1; (cur + t > m) && u > 0; u--) {
      long diff = cur + t - m;
      if (diff > u * h[u]) {     // Not enough removals from time u
        rem += h[u];             // Remove all students with time u
        cur -= u * h[u];         // Decrease total time accordingly
      } else {
        const long x = (diff + u - 1) / u;  // Ceiling division to find min removals needed
        rem += x;
        cur -= x * u;
        break;
      }
    }
    printf("%ld ", rem);
    ++h[t];     // Update histogram with current student's time
    s += t;     // Update total time
  }
  puts("");
  return 0;
}

// https://github.com/VaHiX/codeForces/