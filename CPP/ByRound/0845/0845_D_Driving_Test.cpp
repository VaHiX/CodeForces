// Problem: CF 845 D - Driving Test
// https://codeforces.com/contest/845/problem/D

#include <cstdio>
#include <stack>
/*
Code purpose:
This program determines the minimum number of road signs Polycarp needs to claim he didn't notice 
in order to avoid any rule violations during his driving test. It processes a sequence of events 
related to speed, overtaking, and road signs, maintaining state of current speed limit and overtaking 
permissions. It uses a stack to track speed limits and counts violations based on how many signs 
need to be ignored.

Algorithms/Techniques:
- Simulation with stack for managing speed limits
- Greedy approach to count necessary sign ignorances

Time Complexity: O(n), where n is the number of events. Each event is processed once, and stack operations 
are amortized O(1).

Space Complexity: O(n), due to the stack usage which can grow up to the number of speed limit signs.
*/
int main() {
  std::stack<long> s; // Stack to keep track of speed limits
  long n;
  scanf("%ld", &n);
  long speed(0), cnt(0), noOvertake(0), speedLimit(0); // Variables to track current state
  while (n--) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%ld", &speed); // Update current speed
    } else if (t == 2) {
      // Overtake event: check if overtaking is allowed
      cnt += noOvertake;
      noOvertake = 0; // Reset overtaking flag
    } else if (t == 3) {
      // Speed limit sign: push new limit to stack
      scanf("%ld", &speedLimit);
      s.push(speedLimit);
    } else if (t == 4) {
      // Overtake allowed sign: reset overtaking restriction
      noOvertake = 0;
    } else if (t == 5) {
      // No speed limit sign: clear all speed limits from stack
      while (!s.empty())
        s.pop();
    } else if (t == 6) {
      // No overtake allowed sign: increment overtaking restriction counter
      ++noOvertake;
    }
    // Check if current speed exceeds any speed limit on stack
    while (!s.empty() && s.top() < speed) {
      s.pop();
      ++cnt; // Count the sign that was violated
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/