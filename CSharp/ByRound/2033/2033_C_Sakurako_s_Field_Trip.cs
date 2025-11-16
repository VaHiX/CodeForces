// Problem: CF 2033 C - Sakurako's Field Trip
// https://codeforces.com/contest/2033/problem/C

/*
 * Problem: C. Sakurako's Field Trip
 * Purpose: Minimize the number of adjacent elements with same values by swapping symmetric positions.
 * Algorithm:
 *   - For each test case, we check if the length is even or odd.
 *   - We process from the center outward trying to minimize disturbances.
 *   - At each step, we compare two choices of how to update the current pair and take the one that results in fewer mismatches.
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), excluding input/output storage.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the array
    }
  }

  // Function to check how many of two pairs match with current head/tail values
  static int check(int f, int e, int w, int w2) {
    var res = 0;
    if (f == w)
      res++;
    if (e == w2)
      res++;
    return res;
  }

  // Handle case when array length is odd
  static void oddN(int n, int[] a) {
    var imax = n / 2; // Middle index
    var f = a[imax]; // First element of the comparison pair
    var e = f;       // Second element of the comparison pair (initially same)
    var c = 0;       // Counter for disturbances
    for (int i = imax - 1; i >= 0; i--) {
      var w = a[i];     // Left element
      var w2 = a[n - 1 - i]; // Right element (mirror index)
      var res1 = check(f, e, w, w2); // Cost of keeping current pair as is
      var res2 = check(f, e, w2, w); // Cost of swapping the pair
      if (res1 >= res2) { // Choose cheaper option
        f = w2;
        e = w;
        c += res2;
      } else {
        f = w;
        e = w2;
        c += res1;
      }
    }
    Console.WriteLine(c);
  }

  // Handle case when array length is even
  static void evenN(int n, int[] a) {
    var imax = n / 2; // Middle index
    var f = a[imax - 1]; // First element of the comparison pair (left center)
    var e = a[n - imax]; // Second element of the comparison pair (right center)
    var c = f == e ? 1 : 0; // If equal, increment disturbance count
    for (int i = imax - 2; i >= 0; i--) {
      var w = a[i];     // Left element
      var w2 = a[n - 1 - i]; // Right element (mirror index)
      var res1 = check(f, e, w, w2); // Cost of keeping current pair as is
      var res2 = check(f, e, w2, w); // Cost of swapping the pair
      if (res1 >= res2) { // Choose cheaper option
        f = w2;
        e = w;
        c += res2;
      } else {
        f = w;
        e = w2;
        c += res1;
      }
    }
    Console.WriteLine(c);
  }

  // Decide whether to call odd or even processing based on array length
  static void getAns(int n, int[] a) {
    if (n % 2 == 0)
      evenN(n, a);
    else
      oddN(n, a);
  }
}


// https://github.com/VaHiX/codeForces/