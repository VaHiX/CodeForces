// Problem: CF 1701 C - Schedule Management
// https://codeforces.com/contest/1701/problem/C

﻿/*
 * Problem: Schedule Management
 * 
 * Purpose:
 *   Assign m tasks to n workers such that all tasks are completed in minimum time.
 *   Each worker can only work on one task at a time.
 *   If a worker is proficient in a task, it takes 1 hour; otherwise, 2 hours.
 *   Workers work in parallel.
 * 
 * Algorithm:
 *   - Count how many tasks each worker is proficient in.
 *   - Use a greedy approach with sorting to distribute tasks optimally.
 *   - Simulate the process of task assignment and time progression.
 * 
 * Time Complexity:
 *   O(m + n * log(n)) - For counting, sorting, and simulation.
 * 
 * Space Complexity:
 *   O(n + m) - For storing task proficiency counts and input arrays.
 */
using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0;
      int n = (int)a[0];
      int m = (int)a[1];
      int[] w = new int[n];  // w[i] = number of tasks worker i is proficient in
      long remainingBuildings = 0;  // total number of tasks remaining to assign
      for (int i = 0; i < m; i++) {
        w[b[i] - 1]++;  // b[i] is 1-indexed, convert to 0-indexed
        remainingBuildings++;
      }
      Array.Sort(w);  // Sort by number of tasks each worker is proficient in
      int freeWorkers = 0;  // Number of workers who have no tasks assigned
      for (int i = 0; i < n; i++) {
        if (w[i] > 0) {
          freeWorkers = i;
          break;
        }
      }
      int partialBuildings = 0;  // Number of tasks workers can complete in 1 hour
      while (remainingBuildings > 0) {
        // In current time step, workers with no task will take 2 hours,
        // but since we're simulating, we simulate the progress.
        remainingBuildings -= partialBuildings;  // Workers with proficiency finish 1 task each
        remainingBuildings -= (n - freeWorkers);  // Workers without proficiency finish 1 task each (but in 2 hrs)
        partialBuildings = freeWorkers - partialBuildings;  // Update how many tasks can be done in 1 hour
        o++;  // Increment time by 1 hour
        while (freeWorkers < n && o >= w[freeWorkers])
          freeWorkers++;  // Update workers who now become free after finishing tasks
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/