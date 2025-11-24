// Problem: CF 460 B - Little Dima and Equation
// https://codeforces.com/contest/460/problem/B

/*
B. Little Dima and Equation
time limit per test
1 second
memory limit per test
256 megabytes
input
stdin
output
stdout
Little Dima misbehaved during a math lesson a lot and the nasty teacher Mr. Pickles gave him the following problem as a punishment. 
Find all integer solutions 
x
 
(0 < 
x
 < 10
9
)
 of the equation:
x
 = 
b
·
s
(
x
)
a
 + 
c
, 
 
where 
a
, 
b
, 
c
 are some predetermined constant values and function 
s
(
x
)
 determines the sum of all digits in the decimal representation of number 
x
.
The teacher gives this problem to Dima for each lesson. He changes only the parameters of the equation: 
a
, 
b
, 
c
. Dima got sick of getting bad marks and he asks you to help him solve this challenging problem.

Algorithms/Techniques:
- Brute force approach over possible digit sums (from 1 to 81)
- Precompute powers for efficiency
- Use digit sum function to verify candidate solutions

Time Complexity: O(81 * a * log(M)) where M = 1e9
Space Complexity: O(k) where k is the number of valid solutions, at most ~10^6 in worst case
*/

#include <cstdio>
#include <vector>
int digitSum(long input) {
  int output(0);
  while (input > 0) {
    output += (input % 10); // Extract last digit and add to sum
    input /= 10;            // Remove last digit from number
  }
  return output;
}
long long myPower(long base, long exponent) {
  long long output(1);
  for (int p = 0; p < exponent; p++) {
    output *= base; // Multiply by base 'exponent' times
  }
  return output;
}
int main() {
  const int M = 1e9;
  const int N = 81;
  long a, b, c;
  scanf("%ld %ld %ld", &a, &b, &c);
  std::vector<long long> solutionVec;
  for (int p = 1; p < N; p++) { // Iterate over possible digit sums from 1 to 80
    long long candidate = b * myPower(p, a) + c; // Compute x = b * (digit_sum)^a + c
    if (digitSum(candidate) == p && candidate < M && candidate > 0) { // Check validity of candidate
      solutionVec.push_back(candidate);
    }
  }
  printf("%ld\n", solutionVec.size());
  for (int p = 0; p < solutionVec.size(); p++) {
    printf("%lld ", solutionVec[p]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/