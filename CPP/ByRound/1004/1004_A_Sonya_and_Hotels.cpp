// Problem: CF 1004 A - Sonya and Hotels
// https://codeforces.com/contest/1004/problem/A

/*
 * Problem: Sonya and Hotels
 * Algorithm: Greedy interval analysis
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * The task is to find the number of positions where a new hotel can be built such
 * that the minimum distance from this new hotel to any existing hotel is exactly d.
 * 
 * Key insight:
 * - For each pair of adjacent hotels, we examine the gap between them.
 * - If the gap is larger than 2*d, then we can place multiple new hotels in that gap.
 * - If the gap equals 2*d, we can place exactly one new hotel.
 * - If the gap is less than 2*d, we cannot place any new hotel.
 * 
 * We process the input to compute how many valid positions exist within the gaps,
 * and also consider the edges of the line (before the first hotel and after the last).
 * 
 * The variable 's' accumulates the number of valid new positions.
 * 
 * Input format:
 * - First line: n (number of hotels), d (required minimum distance)
 * - Second line: n integers representing hotel coordinates in strictly increasing order
 * 
 * Output:
 * - The number of possible positions for the new hotel
 */

#include <iostream>
int n, m, k, l, s = 2;  // 's' initialized to 2 for edge cases (before and after first/last hotel)
int main() {
  // Read n and d, and set n to the first hotel coordinate
  for (std::cin >> n >> m >> n; std::cin >> k;)
    // Calculate the number of positions based on the gap between current and previous hotel
    s += k - n == 2 * m ? 1 : k - n > 2 * m ? 2 : 0, n = k;
  std::cout << s;
}


// https://github.com/VaHiX/CodeForces/