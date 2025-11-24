// Problem: CF 534 D - Handshakes
// https://codeforces.com/contest/534/problem/D

/*
D. Handshakes
Algorithms/Techniques: Greedy algorithm with simulation
Time Complexity: O(n)
Space Complexity: O(n)

The problem is about reconstructing the order in which students entered a room, 
given how many handshakes each student had. Each new student shakes hands only 
with those already present. Teams of 3 students form and stop shaking hands with others.

The approach:
1. Process students in order of their arrival.
2. For each arriving student, determine who they shook hands with based on the count.
3. Use a greedy strategy to assign students to teams when possible.
4. Track available students using a vector of vectors indexed by handshakes count.
5. The count variable represents the current number of handshakes for the next student 
   we try to assign or form a team with.
*/

#include <cstdio>
#include <vector>
int main() {
  const long M = 3; // Team size
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> a(n); // a[i] stores indices of students who need i handshakes
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a[x].push_back(p); // Group students by required number of handshakes
  }
  std::vector<long> order; // Stores the final order of student arrivals
  long count(0); // Current index tracking handshake count for next student
  bool possible(true); // Flag to check if solution exists
  for (long p = 0; p < n; p++) {
    // Adjust count so it points to a valid group of students
    while (count >= 0 && a[count].size() == 0) {
      count -= M; // Move back by team size (M=3)
    }
    if (count < 0) {
      possible = false;
      break;
    }
    order.push_back(a[count].back()); // Add last student from current group to order
    a[count].pop_back(); // Remove that student from the group
    ++count; // Increment count for next iteration
  }
  puts(possible ? "Possible" : "Impossible");
  if (possible) {
    for (long p = 0; p < order.size(); p++) {
      printf("%ld ", 1 + order[p]); // Output indices starting from 1
    };
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/