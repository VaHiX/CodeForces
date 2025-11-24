// Problem: CF 491 B - New York Hotel
// https://codeforces.com/contest/491/problem/B

/*
Algorithm: 
  This solution uses the concept of minimizing the maximum Manhattan distance 
  from any hotel to a chosen restaurant. The key insight is to use the fact that 
  Manhattan distance between two points (x1, y1) and (x2, y2) can be expressed as:
    max((x1 + y1) - (x2 + y2), (x2 + y2) - (x1 + y1), (x1 - y1) - (x2 - y2), (x2 - y2) - (x1 - y1))
  
  We compute:
    - For all hotels: min and max values of (x + y) and (x - y)
    - For each restaurant: compute the maximum of the four differences
    - Choose the restaurant that minimizes this maximum distance
    
Time Complexity: O(C + H)
Space Complexity: O(1)

The algorithm works by:
1. Preprocessing all hotel coordinates to find min/max of (x+y) and (x-y)
2. For each restaurant, compute the distance to the "nearest" hotel in terms of 
   this transformed coordinate space
3. Select the restaurant that minimizes the maximum of all such distances
*/

#include <algorithm>
#include <cstdio>
int main() {
  long N, M;
  scanf("%ld %ld", &N, &M);
  long C;
  scanf("%ld", &C);
  long minSum(M + N), maxSum(0), minDiff(N), maxDiff(-M); // Initialize with extreme values
  for (long p = 0; p < C; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    if (x + y < minSum) {        // Track minimum sum (x + y)
      minSum = x + y;
    }
    if (x + y > maxSum) {        // Track maximum sum (x + y)
      maxSum = x + y;
    }
    if (x - y < minDiff) {       // Track minimum difference (x - y)
      minDiff = x - y;
    }
    if (x - y > maxDiff) {       // Track maximum difference (x - y)
      maxDiff = x - y;
    }
  }
  long H;
  scanf("%ld", &H);
  long bestHotel(0), bestDist(M + N); // Initialize with largest possible distance
  for (long p = 0; p < H; p++) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    long sum = x + y;
    long diff = x - y;
    // Compute the max Manhattan distance from this restaurant to any hotel
    long dist = std::max(std::max(sum - minSum, maxSum - sum),
                         std::max(diff - minDiff, maxDiff - diff));
    if (dist < bestDist) {       // Update if this is a better restaurant
      bestHotel = p + 1;
      bestDist = dist;
    }
  }
  printf("%ld\n%ld\n", bestDist, bestHotel);
  return 0;
}


// https://github.com/VaHiX/CodeForces/