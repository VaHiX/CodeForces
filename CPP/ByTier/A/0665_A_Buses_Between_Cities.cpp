// Problem: CF 665 A - Buses Between Cities
// https://codeforces.com/contest/665/problem/A

/*
 * Problem: Buses Between Cities
 * 
 * Purpose:
 *   This program calculates the number of buses traveling from city B to city A
 *   that a driver departing from city A at a given time will meet on his journey.
 *   The bus schedules are fixed and the driver's travel time is known.
 * 
 * Algorithms/Techniques:
 *   - Simulation approach over time intervals
 *   - Linear iteration through bus departure times from city B
 *   - Interval overlap detection to determine if a bus is encountered
 * 
 * Time Complexity: O((F - S) / b) where S=300 (5:00 AM), F=1439 (11:59 PM), b is the interval for buses from B
 *   - In worst case, this is approximately O(1439 / b), which simplifies to O(1) for constant b
 * 
 * Space Complexity: O(1)
 *   - Only a constant amount of extra space used (variables like start, count, etc.)
 * 
 * Input Format:
 *   - First line: a, ta (frequency and travel time for A->B buses)
 *   - Second line: b, tb (frequency and travel time for B->A buses)
 *   - Third line: hh:mm (departure time of Simion from city A)
 * 
 * Output:
 *   - Number of buses encountered on the way (excluding start and end points)
 */

#include <cstdio>

const int H = 60;
int main() {
  int a, ta;
  scanf("%d %d\n", &a, &ta);  // Read frequency and travel time for A->B buses
  int b, tb;
  scanf("%d %d\n", &b, &tb);  // Read frequency and travel time for B->A buses
  int hh, mm;
  scanf("%d:%d\n", &hh, &mm);  // Read Simion's departure time
  int start = hh * H + mm;  // Convert departure time to minutes since 00:00
  const int S = 5 * H + 0;  // Start time in minutes (05:00 AM)
  const int F = 23 * H + 59;  // End time in minutes (11:59 PM)
  int count(0);  // Counter for encountered buses
  for (int p = S; p <= F; p += b) {  // Iterate over all B->A bus departures
    // Check if the bus from B is on the road during Simion's travel
    // p < start + ta: bus departs before Simion arrives at B
    // p + tb > start: bus arrives after Simion departs from A
    if ((p < start + ta) && (p + tb > start)) {
      ++count;
    }
  }
  printf("%d\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/