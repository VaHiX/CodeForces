// Problem: CF 1867 C - Salyg1n and the MEX Game
// https://codeforces.com/contest/1867/problem/C

/*
Purpose: Solve the interactive problem "C. Salyg1n and the MEX Game" where Alice aims to maximize MEX(S) and Bob aims to minimize it.
Algorithm: 
- Determine initial MEX and optimal first move based on the sorted set S.
- Use a strategy where Alice tries to maintain a prefix of consecutive integers starting from 0.
- Track a variable 're' to indicate the next number Alice should try to add.
- Adjust 're' appropriately after each Bob's move to ensure optimal play.
Time Complexity: O(n) per test case, where n is the size of the set S.
Space Complexity: O(n) for storing the set S in a dictionary.
*/
using System;
using System.Linq;
using System.Collections.Generic;
class sol {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      Dictionary<int, bool> d = new Dictionary<int, bool>();
      string[] str = Console.ReadLine().Split(' ');
      int re = 0, mex = -1;
      bool x = false, y = false;
      for (int i = 0; i < n; i++) {
        int a = int.Parse(str[i]);
        d.Add(a, true);
        // If we're tracking a potential mex and have found a gap in sequence
        if (y && i + 1 != a) {
          mex = i + 1;
          y = false;
        }
        // If we haven't determined the first number to place yet, try to find the first gap in sequence
        if (!x && i != a) {
          re = i;
          x = true;
          y = true;
          // If current element is not consecutive, we know the gap is at position re + 1
          if (a != re + 1) {
            mex = re + 1;
            y = false;
          }
        }
      }
      // Special case: if the sequence starts with 0, the minimum missing integer is n
      if (d.Keys.ElementAt(0) == re)
        re = n;
      // If no gap was found in initial sequence, MEX is n+1
      if (mex < 0)
        mex = n + 1;
      while (true) {
        // Alice makes her move by adding value 're'
        Console.WriteLine(re);
        Console.Out.Flush();
        string s = Console.ReadLine();
        if (s == "-1")
          break;
        else if (s == "-2")
          return;
        else {
          int b = int.Parse(s);
          // If Bob removes a number below MEX, set re to that number
          if (b < mex)
            re = b;
          else {
            // Bob removes number >= MEX
            re = mex;
            d.Remove(b);
            // Try to find new MEX after removal
            for (int j = mex; j < n - 1; j++) {
              if (d.Keys.ElementAt(j) != j + 1) {
                mex = j + 1;
                break;
              }
            }
          }
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/