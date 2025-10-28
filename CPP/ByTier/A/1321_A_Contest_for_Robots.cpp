// Problem: CF 1321 A - Contest for Robots
// https://codeforces.com/contest/1321/problem/A

/*
A. Contest for Robots
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Polycarp is preparing the first programming contest for robots. There are n problems in it, and a lot of robots are going to participate in it. Each robot solving the problem i gets p_i points, and the score of each robot in the competition is calculated as the sum of p_i over all problems i solved by it. For each problem, p_i is an integer not less than 1.
Two corporations specializing in problem-solving robot manufacturing, "Robo-Coder Inc." and "BionicSolver Industries", are going to register two robots (one for each corporation) for participation as well. Polycarp knows the advantages and flaws of robots produced by these companies, so, for each problem, he knows precisely whether each robot will solve it during the competition. Knowing this, he can try predicting the results — or manipulating them. 
For some reason (which absolutely cannot involve bribing), Polycarp wants the "Robo-Coder Inc." robot to outperform the "BionicSolver Industries" robot in the competition. Polycarp wants to set the values of p_i in such a way that the "Robo-Coder Inc." robot gets 
strictly more
 points than the "BionicSolver Industries" robot. However, if the values of p_i will be large, it may look very suspicious — so Polycarp wants to minimize the maximum value of p_i over all problems. Can you help Polycarp to determine the minimum possible upper bound on the number of points given for solving the problems?

Algorithms/Techniques: Greedy approach with binary search on the answer.
Time complexity: O(n log n)
Space complexity: O(n)
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);         // a[i] = 1 if Robo-Coder solves problem i, else 0
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(n);         // b[i] = 1 if BionicSolver solves problem i, else 0
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  long pts(0), cnt(0);
  for (long p = 0; p < n; p++) {
    if (a[p] == b[p]) {           // If both robots solve or do not solve the same problem
      continue;                   // No point difference can be made here
    } else if (a[p]) {            // Robo-Coder solves, BionicSolver does not
      ++cnt;                      // Count how many such positions there are 
    } else if (b[p]) {            // BionicSolver solves, Robo-Coder does not
      ++pts;                      // Count how many such positions there are
    }
  }
  printf("%ld\n", cnt ? (1 + pts / cnt) : -1);  // If no positions where Robo-Coder gains advantage, return -1.
                                                // Otherwise compute minimum max points needed.
  return 0;
}


// https://github.com/VaHiX/codeForces/