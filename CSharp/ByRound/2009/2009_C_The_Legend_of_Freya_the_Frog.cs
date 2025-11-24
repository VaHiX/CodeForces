// Problem: CF 2009 C - The Legend of Freya the Frog
// https://codeforces.com/contest/2009/problem/C

/*
C. The Legend of Freya the Frog
time limit per test2 seconds
memory limit per test256 megabytes

Freya the Frog is traveling on the 2D coordinate plane. She is currently at point
(0,0)
and wants to go to point
(x,y)
. In one move, she chooses an integer
d
 such that
0≤d≤k
 and jumps
d
 spots forward in the direction she is facing.
Initially, she is facing the positive
x
direction. After every move, she will alternate between facing the positive
x
direction and the positive
y
direction (i.e., she will face the positive
y
direction on her second move, the positive
x
direction on her third move, and so on).
What is the minimum amount of moves she must perform to land on point
(x,y)
?

Algorithm:
- For each axis (x and y), compute the minimal number of steps needed.
  - To reach x: since we can jump up to k steps in one move, we need ceil(x/k) moves if x > 0
  - Similarly for y: ceil(y/k) moves
- The key insight is that Freya alternates directions: x, y, x, y, ...
  - So, the total number of moves will be:
    * If xSteps >= ySteps: min_moves = xSteps + (ySteps) + (xSteps - ySteps) = 2*xSteps - (ySteps - xSteps)
    * Otherwise: min_moves = (xSteps) + 2*ySteps - (ySteps - xSteps)
  - Simplified version:
    * If xSteps >= ySteps, then result = 2 * xSteps - 1 (since last move is in x direction)
    * Else result = 2 * ySteps

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Concurrent;

class Program {
  static void Main() {
    int fieldName = int.Parse(Console.ReadLine()); // Read number of test cases
    
    for (int i = 0; i < fieldName; i++) {
      string[] input = Console.ReadLine().Split(); // Read x, y, k
      int x = int.Parse(input[0]);
      int y = int.Parse(input[1]);
      int k = int.Parse(input[2]);
      
      int xSteps = 0;
      int ySteps = 0;
      
      // Calculate minimum steps in x direction
      if (x % k == 0)
        xSteps = x / k;
      else
        xSteps = x / k + 1;
        
      // Calculate minimum steps in y direction  
      if (y % k == 0)
        ySteps = y / k;
      else
        ySteps = y / k + 1;
        
      // Determine final number of moves based on the comparison between step counts
      if (xSteps > ySteps)
        Console.Write(Math.Max(xSteps, ySteps) * 2 - 1); // Odd number of moves when x_steps > y_steps
      else
        Console.Write(Math.Max(xSteps, ySteps) * 2); // Even number of moves otherwise
        
      Console.Write("\n");
    }
  }
  
  static int ExampleMethod(int exampleParameter) {
    exampleParameter = 0;
    return exampleParameter;
  }
}


// https://github.com/VaHiX/codeForces/