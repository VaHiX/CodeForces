// Problem: CF 2091 D - Place of the Olympiad
// https://codeforces.com/contest/2091/problem/D

/*
D. Place of the Olympiad

Purpose:
This program determines the minimum possible length of the longest bench when placing k participants 
on an n×m venue such that each participant gets one desk and benches consist of consecutive desks in a row.

Algorithms/Techniques:
Binary search on the answer combined with greedy placement logic to determine if a given maximum bench length is feasible.

Time Complexity: O(t * log(min(n,m))) where t is number of test cases
Space Complexity: O(1)

Input:
- t: number of test cases
- For each test case: n (rows), m (columns), k (number of participants)

Output:
- Minimum possible length of the longest bench
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    
    // Calculate which row the k-th participant will be placed in (1-indexed)
    long rownum = (k + n - 1) / n;
    
    // Compute minimum bench length required to place all participants
    // by dividing total participants by available spots per row, accounting 
    // for how many participants are already placed in previous rows.
    long res = m / (m - rownum + 1);
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/