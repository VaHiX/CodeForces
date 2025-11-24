// Problem: CF 2010 B - Three Brothers
// https://codeforces.com/contest/2010/problem/B

/*
B. Three Brothers
time limit per test1 second
memory limit per test256 megabytes

Three brothers agreed to meet. Let's number the brothers as follows: the oldest brother is number 1, the middle brother is number 2, and the youngest brother is number 3.
When it was time for the meeting, one of the brothers was late. Given the numbers of the two brothers who arrived on time, you need to determine the number of the brother who was late.

Algorithms/Techniques: Mathematical calculation
Time complexity: O(1)
Space complexity: O(1)

Input
The first line of input contains two different integers a and b (1 ≤ a, b ≤ 3, a ≠ b) — the numbers of the brothers who arrived on time. The numbers are given in arbitrary order.
Output
Output a single integer — the number of the brother who was late to the meeting.
Example
input
3 1
output
2
*/

using System;
class Program {
  static void Main() {
    string[] input = Console.ReadLine().Split(' '); // Read and split input line into two strings
    int a = int.Parse(input[0]); // Parse first number as integer
    int b = int.Parse(input[1]); // Parse second number as integer
    int lateBrother = 3 + 1 + 2 - a - b; // Calculate the missing brother number (1+2+3=6, so 6-a-b gives the late brother)
    Console.WriteLine(lateBrother); // Output the result
  }
}


// https://github.com/VaHiX/codeForces/