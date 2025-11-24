// Problem: CF 650 B - Image Preview
// https://codeforces.com/contest/650/problem/B

/*
Algorithm/Techniques: Sliding window with rotation cost optimization
Time Complexity: O(n)
Space Complexity: O(n)

The solution uses a sliding window technique to find the maximum number of photos
that can be viewed within the time limit T. It considers both the cost of moving
between photos (a seconds) and the cost of rotating photos (b seconds if orientation
doesn't match). The key idea is to simulate viewing photos in a circular manner,
duplicating the array to handle wraparound (left from 1st photo goes to last, etc.).
For each possible window of photos, we calculate the total time needed (including
rotations and movements) and keep track of the maximum number of photos that fit
within T seconds.
*/

#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
  int64_t n, a, b, t;
  std::cin >> n >> a >> b >> t;
  std::string s;
  std::cin >> s;
  int64_t pictime(0);  // Total time for viewing photos in current window
  std::vector<int64_t> c(2 * n);  // Cost array duplicated for circular simulation
  for (int64_t p = 0; p < n; p++) {
    // Cost to view photo p: 1 second + b seconds if rotation needed (w = horizontal)
    c[p] = c[p + n] = 1 + b * (s[p] == 'w');
    pictime += c[p];  // Sum up costs for initial setup
  }
  int64_t l(0), count(0);  // l: left pointer, count: max photos viewed
  for (int64_t r = n; r < 2 * n; r++) {  // r: right pointer, start from n to simulate wraparound
    pictime += c[r];  // Add cost of new photo at right end of window
    // Shrink window from left while total time exceeds T or window size is too large
    while ((r - l + 1 > n) ||  // Window size exceeds number of photos
           (pictime + (a * ((r - l) + std::min(r - n, n - l))) > t)) {  // Time exceeds limit
      pictime -= c[l];  // Remove leftmost photo cost
      ++l;  // Move left pointer forward
    }
    if (l > n) {  // Break if left pointer went past original array size
      break;
    }
    // Update maximum number of photos that can be viewed
    count = (count > (r - l + 1)) ? count : (r - l + 1);
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/