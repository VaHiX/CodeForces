// Problem: CF 879 A - Borya's Diagnosis
// https://codeforces.com/contest/879/problem/A

/*
Purpose: This code determines the minimum day on which Borya can visit all doctors,
         given their working schedules. Each doctor works every 'd' days starting from 's'.
         Borya must visit doctors in order, and cannot visit more than one doctor per day.

Algorithms/Techniques: 
    - Greedy approach to find earliest possible day for each doctor visit
    - For each doctor, calculate the next available day after the previous visit

Time Complexity: O(n), where n is the number of doctors. Each iteration processes one doctor.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long t(0); // t represents the day of the last visit; initially 0 (before any visit)
  for (long p = 0; p < n; p++) {
    long s, d;
    scanf("%ld %ld", &s, &d);
    if (t < s) {
      // If the current day is earlier than the doctor's start day,
      // Borya can visit on the doctor's start day
      t = s;
    } else {
      // Otherwise, find the next working day for this doctor after the last visit
      // (t - s) / d gives number of full cycles since start
      // Adding 1 gives number of next cycle
      // Multiply by d to get offset, add s to get actual day
      t = d * ((t - s) / d + 1) + s;
    }
  }
  printf("%ld\n", t);
  return 0;
}


// https://github.com/VaHiX/CodeForces/