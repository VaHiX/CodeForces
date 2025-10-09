// Problem: CF 2094 B - Bobritto Bandito
// https://codeforces.com/contest/2094/problem/B

/*
B. Bobritto Bandito
Algorithm: Simulation of plague spreading on infinite line.
Time Complexity: O(n * p) where n is the number of days and p is the number of steps to simulate.
Space Complexity: O(1) - only using a few variables for simulation.

In Bobritto Bandito's home town of residence, there are an infinite number of houses on an infinite number line, with houses at
…,−2,−1,0,1,2,…
. On day
0
, he started a plague by giving an infection to the unfortunate residents of house
0
. Each succeeding day, the plague spreads to exactly one healthy household that is next to an infected household. It can be shown that each day the infected houses form a continuous segment.
Let the segment starting at the
l
-th house and ending at the
r
-th house be denoted as
[l,r]
. You know that after
n
days, the segment
[l,r]
became infected. Find any such segment
[
l
′
,
r
′
]
that could have been infected on the
m
-th day (
m≤n
).
*/
using System;
using System.Collections.Generic;
using System.Linq;
public class Program {
  public static void Main() {
    int n = int.Parse(Console.ReadLine());
    for (int i = 0; i < n; i++) {
      string input = Console.ReadLine();
      List<int> numbers = input.Split(' ').Select(int.Parse).ToList();
      int e = numbers[0]; // unused variable in current implementation
      int p = numbers[1];
      int l = numbers[2];
      int r = numbers[3];
      int ls = 0; // left side of the segment at current day
      int rs = 0; // right side of the segment at current day
      for (int j = 0; j < p; j++) {
        if (!(l == 0 || ls == l)) { // if we have not reached left boundary yet
          ls -= 1; // move left pointer one step to the left
          continue;
        }
        if (!(r == 0 || rs == r)) { // if we have not reached right boundary yet
          rs += 1; // move right pointer one step to the right
          continue;
        }
      }
      Console.WriteLine($"{ls} {rs}");
    }
  }
}


// https://github.com/VaHiX/codeForces/