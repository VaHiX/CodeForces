// Problem: CF 1154 D - Walking Robot
// https://codeforces.com/contest/1154/problem/D

/*
D. Walking Robot
Algorithm: Greedy
Time Complexity: O(n)
Space Complexity: O(n)

There is a robot staying at X=0 on the Ox axis. He has to walk to X=n. 
You are controlling this robot and controlling how he goes. The robot has a battery and an accumulator with a solar panel.

The i-th segment of the path (from X=i-1 to X=i) can be exposed to sunlight or not. 
The array s denotes which segments are exposed to sunlight: if segment i is exposed, then s_i = 1, otherwise s_i = 0.

The robot has one battery of capacity b and one accumulator of capacity a. 
For each segment, you should choose which type of energy storage robot will use to go to the next point (it can be either battery or accumulator). 
If the robot goes using the battery, the current charge of the battery is decreased by one (the robot can't use the battery if its charge is zero). 
And if the robot goes using the accumulator, the current charge of the accumulator is decreased by one (and the robot also can't use the accumulator if its charge is zero).

If the current segment is exposed to sunlight and the robot goes through it using the battery, the charge of the accumulator increases by one (of course, its charge can't become higher than it's maximum capacity).
If accumulator is used to pass some segment, its charge decreases by 1 no matter if the segment is exposed or not.

You understand that it is not always possible to walk to X=n. You want your robot to go as far as possible. 
Find the maximum number of segments of distance the robot can pass if you control him optimally.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, b, a;
  scanf("%ld %ld %ld", &n, &b, &a);
  std::vector<int> s(n);
  for (long p = 0; p < n; p++) {
    scanf("%d", &s[p]);
  }
  long x(a), pos(0); // x is current accumulator charge, pos tracks the farthest position reached
  for (long p = 0; p < n; p++) {
    if (s[p]) { // if segment is exposed to sunlight
      if (b > 0 && x < a) { // use battery if we have battery and accumulator is not full
        --b;
        ++x;
      } else if (x > 0) { // otherwise use accumulator if available
        --x;
      } else if (b > 0) { // otherwise use battery if available
        --b;
      } else {
        break; // no power left
      }
    } else { // if segment is not exposed to sunlight
      if (x > 0) { // use accumulator if available
        --x;
      } else if (b > 0) { // otherwise use battery if available
        --b;
      } else {
        break; // no power left
      }
    }
    pos = p + 1; // update position tracker
  }
  printf("%ld\n", pos);
  return 0;
}


// https://github.com/VaHiX/codeForces/