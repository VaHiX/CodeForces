// Problem: CF 2022 A - Bus to Pénjamo
// https://codeforces.com/contest/2022/problem/A

/*
 * Problem: Bus to Pénjamo
 * 
 * Purpose:
 *   Given n families with a_i members each and a bus with r rows of 2 seats,
 *   determine the maximum number of happy people in an optimal seating arrangement.
 *   
 *   A person is happy if:
 *     - Another family member is seated in the same row, or
 *     - They are alone in their row (with one empty seat).
 *   
 *   All families must be seated, and the total number of people fits in the bus.
 *   
 * Algorithm:
 *   1. For each family member count how many rows can accommodate them entirely (happy rows)
 *      and how many will be in "unhappy" rows (with one empty seat).
 *   2. Use a greedy approach to assign rows to maximize happiness:
 *      - Place as many families as possible in same-row pairs.
 *      - Deal with leftover family members who will end up alone or in mixed rows to minimize unhappiness.
 *   
 * Time Complexity: O(n) per test case (since n <= 100)
 * Space Complexity: O(1) excluding input storage
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and r
      var n = int.Parse(line[0]);
      var r = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' '); // Read family sizes
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, r, a); // Compute answer for current test case
    }
  }

  static void getAns(int n, int r, int[] a) {
    var happyrow = 0;     // Count of rows where at least 2 people sit together (happy)
    var unhappy = 0;      // Count of single people in rows (can't be happy due to not being alone but others seated)
    
    foreach (var x in a) {
      happyrow += x / 2;  // Number of full pairs (each produces 2 happy people)
      unhappy += x % 2;   // Number of unpaired individuals
    }

    var freerow = r - happyrow; // Number of rows left to be used where at least one spot is empty
    
    if (freerow == 0) {
      Console.WriteLine(happyrow * 2); // All rows are full, all people must be paired
      return;
    }

    int ans;

    if (unhappy == freerow * 2)
      ans = happyrow * 2; // Each unpaired person can get a free spot; no gain in total happiness from redistribution

    else if (freerow >= unhappy)
      ans = unhappy + happyrow * 2; // Use enough free rows to place all unpaired people alone in their own rows

    else
      ans = unhappy - (unhappy % freerow) * 2 + happyrow * 2; // Redistribute unpaired people among fewer free rows effectively
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/