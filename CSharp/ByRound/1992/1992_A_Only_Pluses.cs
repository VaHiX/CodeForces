// Problem: CF 1992 A - Only Pluses
// https://codeforces.com/contest/1992/problem/A

/*
Code Purpose:
This program takes three integers a, b, and c as input and maximizes their product a*b*c 
by incrementing any of them at most 5 times. It does this by always incrementing the smallest 
of the three values at each step to maximize the product.

Algorithms/Techniques:
- Greedy approach: At each step, we increase the smallest of the three values to 
  maximize the product after 5 increments.
- Iteration: We perform 5 iterations of incrementing the smallest value.

Time Complexity: O(1) - The number of iterations is fixed (5), and operations are constant time.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

using System;
class HelloWorld {
  static void Main() {
    int a = 0;
    int b = 0;
    int c = 0;
    string s;
    string[] mas;
    int n = int.Parse(Console.ReadLine());
    for (int i = 0; i < n; i++) {
      s = Console.ReadLine();
      mas = s.Split(' ');
      a = int.Parse(mas[0]);
      b = int.Parse(mas[1]);
      c = int.Parse(mas[2]);
      // Perform at most 5 increments to maximize the product
      for (int j = 0; j < 5; j++) {
        // If a is the smallest, increment it
        if (a <= c) {
          if (a <= b)
            a++;
          else
            b++;
        } else {
          // Otherwise, compare c and b to decide which to increment
          if (c < b)
            c++;
          else
            b++;
        }
      }
      Console.WriteLine(a * b * c);
    }
  }
}


// https://github.com/VaHiX/CodeForces/