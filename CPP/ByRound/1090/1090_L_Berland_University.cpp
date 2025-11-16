// Problem: CF 1090 L - Berland University
// https://codeforces.com/contest/1090/problem/L

/*
 * Problem: Berland University
 * Purpose: Given n lectures, auditorium sizes a and b, and minimum k lectures required to pass,
 *          find the maximum number of students that can attend at least k lectures.
 * 
 * Approach:
 *   - Use binary search on the answer (number of students).
 *   - For a given number of students 'mid', compute how many lectures they can attend
 *     based on alternating auditorium usage.
 *   - In each week, odd weeks use first auditorium (size a), even weeks use second (size b).
 *   - Total possible lecture attendance is calculated by summing:
 *     - Odd weeks: min(a, mid) students per lecture for floor(n/2) + n%2 lectures
 *     - Even weeks: min(b, mid) students per lecture for floor(n/2) lectures
 *     - Then divided by mid to get average per student.
 * 
 * Time Complexity: O(log(max_n)) due to binary search over possible number of students.
 * Space Complexity: O(1) - only constant extra space used.
 */

#include <algorithm>
#include <iostream>

using namespace std;
long long n, m, a, b, k, l, r, ans;

int main() {
  cin >> n >> m >> a >> b >> k;
  l = 1;                        // Lower bound for binary search
  r = n;                        // Upper bound for binary search
  while (l <= r) {
    long long mid = (l + r) / 2; // Midpoint - current number of students being tested
    // Calculate total possible lecture attendance for 'mid' students
    long long sum =
        ((m / 2 + m % 2) * min(a, mid) + (m / 2) * min(b, mid)) / mid;
    if (sum >= k) {
      ans = mid;     // This number of students is feasible, try higher
      l = mid + 1;
    } else
      r = mid - 1;   // Not enough, must reduce number of students
  }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/codeForces/