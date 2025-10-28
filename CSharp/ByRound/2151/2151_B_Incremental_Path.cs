// Problem: CF 2151 B - Incremental Path
// https://codeforces.com/contest/2151/problem/B

/*
B. Incremental Path
Algorithm: Simulate commands and track black cells efficiently using a linked list to maintain white cell positions.
Time Complexity: O(n * m) in worst case due to traversal of linked list for each command; however, practical performance is better due to sparse updates.
Space Complexity: O(m) for storing initial black/white cell positions in linked list structure.

The program simulates a sequence of commands (A and B) on a strip of cells. 
Command A moves the pointer one step forward.
Command B jumps to the next white cell.
Each command execution ends by coloring the last visited cell black (if not already).
We maintain current position and update the set of black cells as we process commands.
*/

using System.Text;
using System.IO;
using System;
using System.Collections.Generic;
class Program {
  static void Solve() {
    int n = Next(); // Read number of commands
    int m = Next(); // Read initial number of black cells
    int[] s = new int[n]; // Store command sequence (1 for A, 2 for B)
    for (int i = 0; i < n; i++)
      s[i] = Next(); // Parse each command into integer representation
    LinkedList<int> ll = new LinkedList<int>(); // Maintain list of white cell positions (sorted)
    for (int i = 0; i < m; i++)
      ll.AddLast(Next()); // Initialize linked list with black cell positions
    ll.AddLast(int.MaxValue); // Add sentinel value to simplify end-of-list handling
    LinkedListNode<int> curr = ll.First; // Pointer to current node in linked list
    if (curr.Value == 1) // If position 1 is black, move pointer forward
      curr = curr.Next;
    for (int i = 0, pos = 1; i < n; i++) { // Process through each command
      if (s[i] == 1) { // A command - move forward one cell
        pos++;
        if (curr.Value > pos) { // Insert new position if not present
          curr = ll.AddBefore(curr, pos);
        }
        curr = curr.Next; // Move pointer to next node
      } else { // B command - jump to next white cell
        pos++;
        while (curr.Value == pos) { // Skip over black cells (they become white after processing)
          curr = curr.Next;
          pos++;
        }
        curr = ll.AddBefore(curr, pos); // Insert newly visited black position
        while (curr.Value == pos) { 
          curr = curr.Next;
          pos++;
        }
      }
    }
    LinkedListNode<int> ans = ll.First; // Start output with first node
    writer.WriteLine(ll.Count - 1); // Output total number of black cells (excluding sentinel)
    while (ans.Value != int.MaxValue) { // Print all positions until sentinel
      writer.Write(ans.Value);
      writer.Write(' ');
      ans = ans.Next;
    }
    writer.WriteLine();
  }
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      Solve(); // Execute solve for each test case
    writer.Flush(); // Flush output buffer
  }
  static int Next() { // Parse next integer from console input
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == 'A') // Return 1 for 'A'
        return 1;
      if (c == 'B') // Return 2 for 'B'
        return 2;
      if (c == '-')
        m = -1; // Handle negative numbers
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read(); // Read next digit
      if (c < '0' || c > '9') // If not a digit, return value
        return m * res;
      res *= 10;
      res += c - '0'; // Build number
    }
  }
  static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/CodeForces/