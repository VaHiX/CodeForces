// Problem: CF 750 C - New Year and Rating
// https://codeforces.com/contest/750/problem/C

/*
C. New Year and Rating
Algorithm: Greedy + Range Tracking
Time Complexity: O(n)
Space Complexity: O(1)

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating 1900 or higher. Those with rating 1899 or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in n contests in the year 2016. He remembers that in the i-th contest he competed in the division d_i (i.e. he belonged to this division just before the start of this contest) and his rating changed by c_i just after the contest. Note that negative c_i denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all n contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

Input:
The first line of the input contains a single integer n (1 ≤ n ≤ 200 000).
The i-th of next n lines contains two integers c_i and d_i (-100 ≤ c_i ≤ 100, 1 ≤ d_i ≤ 2), describing Limak's rating change after the i-th contest and his division during the i-th contest contest.

Output:
If Limak's current rating can be arbitrarily big, print "Infinity" (without quotes). If the situation is impossible, print "Impossible" (without quotes). Otherwise print one integer, denoting the maximum possible value of Limak's current rating, i.e. rating after the n contests.
*/

#include <cstdio>
int main() {
  const long M = 1e9; // A large number to represent infinity for checking limits
  const long B = 1900; // Boundary between divisions (1900 and below is division 2, 1900+ is division 1)
  long n;
  scanf("%ld", &n);
  long startMin(-M), startMax(M), totalDiff(0); // startMin: minimum possible starting rating, startMax: maximum possible starting rating, totalDiff: cumulative change in rating
  while (n--) {
    long c, d;
    scanf("%ld %ld", &c, &d);
    if ((d == 1) && (startMin + totalDiff < B)) { // If the user was in division 1 but now the lower bound would put them in division 2, adjust startMin
      startMin = B - totalDiff; // Adjust startMin to be just enough to remain in division 1
    }
    if ((d == 2) && (startMax + totalDiff >= B)) { // If the user was in division 2 but now the upper bound would put them in division 1, adjust startMax
      startMax = B - 1 - totalDiff; // Adjust startMax to be just below B to remain in division 2
    }
    totalDiff += c; // Update cumulative rating change
  }
  if (startMin > startMax) { // If there is no valid range left for the starting rating, it's impossible
    puts("Impossible");
  } else if (startMax >= M) { // If the max possible value exceeds M, we can go up to infinity
    puts("Infinity");
  } else {
    printf("%ld\n", startMax + totalDiff); // Otherwise, output the maximum final rating
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/