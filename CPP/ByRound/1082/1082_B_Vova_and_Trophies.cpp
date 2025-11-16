// Problem: CF 1082 B - Vova and Trophies
// https://codeforces.com/contest/1082/problem/B

/*
Problem: B. Vova and Trophies

Purpose:
This code determines the maximum possible length of a consecutive subsegment of 'G' characters (golden trophies) 
after performing at most one swap between any two trophies in the given string.

Algorithms/Techniques:
- Sliding window technique with simulation of swaps
- Two-pass processing to evaluate possible maximum gains from one swap
- Tracking previous and current counts of consecutive golden trophies

Time Complexity: O(n)
Space Complexity: O(1)

Input Format:
First line: integer n (number of trophies)
Second line: string of n characters ('G' or 'S')

Output Format:
Maximum length of consecutive 'G's achievable after at most one swap
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  s += 'S'; // Add sentinel to simplify loop termination logic
  long mx(0), cnt(0), prev(0), sum(0), num(0), single(0);
  for (long p = 0; p <= n; p++) {
    if (cnt == 0 && s[p] == 'S') {
      // Start of a new segment, no golden trophies seen yet
      prev = 0;
    } else if (s[p] == 'S') {
      // Encounter end of a golden segment
      ++num;
      single = (single > cnt) ? single : cnt;  // Track max single segment
      long total = cnt + prev + (prev > 0);    // Calculate combined length with previous segment
      mx = (mx > total) ? mx : total;          // Update global maximum
      prev = cnt;
      cnt = 0;
    } else if (s[p] == 'G') {
      // Continue counting golden trophies
      ++cnt;
      ++sum;
    }
  }
  mx += (single == mx && num > 1);  // Adjust for special case: if we can join two segments
  mx = (mx < sum) ? mx : sum;       // Ensure final answer doesn't exceed total G count
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/