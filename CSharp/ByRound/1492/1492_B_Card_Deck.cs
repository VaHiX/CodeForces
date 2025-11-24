// Problem: CF 1492 B - Card Deck
// https://codeforces.com/contest/1492/problem/B

/*
 * Problem: Card Deck
 * Algorithm: Stack-based approach to determine optimal card order
 * 
 * Approach:
 * 1. Use a stack to find the next greater element for each position from right to left
 * 2. Process elements in reverse order to construct the final sequence
 * 
 * Time Complexity: O(n) - Each element is pushed and popped from stack at most once
 * Space Complexity: O(n) - For the stack and auxiliary arrays
 */

using System;
using System.Text;
using System.Collections.Generic;
namespace HelloWorld {
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var arr = Console.ReadLine().Split(' ');
      Stack<int> stack = new Stack<int>();
      // Build a stack of indices representing positions with decreasing values from right to left
      for (int i = arr.Length - 1; i >= 0; i--) {
        // Pop elements from stack while the current element is greater than the element at stack top
        while (stack.Count > 0 &&
               int.Parse(arr[stack.Peek()]) < int.Parse(arr[i]))
          stack.Pop();
        stack.Push(i);
      }
      Stack<int> st2 = new Stack<int>();
      // Transfer elements from first stack to second in reverse order
      while (stack.Count > 0) {
        st2.Push(stack.Pop());
      }
      int pv = arr.Length;
      // Construct final output by processing the indices in order
      while (st2.Count > 0) {
        int num = st2.Pop();
        // Print elements from current index to previous position
        for (int i = num; i < pv; i++) {
          Console.Write(arr[i] + " ");
        }
        pv = num;
      }
      Console.WriteLine();
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/