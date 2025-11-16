// Problem: CF 1185 C2 - Exam in BerSU (hard version)
// https://codeforces.com/contest/1185/problem/C2

/*
C2. Exam in BerSU (hard version)
Purpose: For each student, determine the minimum number of students that must fail 
         so that this student can complete their exam within the given time limit M.
Algorithms/Techniques: 
    - Greedy approach with histogram tracking of exam times
    - Use a histogram (vector h) to efficiently manage the removal of largest times
Time Complexity: O(n * B) where B = 101 (max possible time value)
Space Complexity: O(B) for the histogram vector

The solution processes students one by one, maintaining running sum and 
using a histogram to find the minimal number of students to remove 
to ensure enough time for the current student.
*/

#include <cstdio>
#include <vector>
int main() {
  const int B = 101; // Maximum possible exam time (given in constraints)
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> h(B, 0); // Histogram to count how many students have each exam time
  long s(0); // Running sum of times processed so far
  for (long p = 0; p < n; p++) {
    const long t = a[p]; // Current student's exam time
    long cur(s), rem(0); // cur: current sum, rem: number of students to remove
    // Greedily try to remove largest times first to free up time
    for (long u = B - 1; (cur + t > m) && u > 0; u--) {
      long diff = cur + t - m; // How much time we're over the limit
      if (diff > u * h[u]) { // If removing all students with time u isn't enough
        rem += h[u]; // Remove all students with this time
        cur -= u * h[u]; // Reduce current sum accordingly
      } else {
        const long x = (diff + u - 1) / u; // Number of students to remove using division ceiling
        rem += x; 
        cur -= x * u; // Reduce sum by removing x students of time u
        break;
      }
    }
    printf("%ld ", rem); // Print the number of students that must leave before this student
    ++h[t]; // Add current student's time to histogram
    s += t; // Add to running sum
  }
  puts(""); // Newline after output
  return 0;
}


// https://github.com/VaHiX/codeForces/