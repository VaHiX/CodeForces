// Problem: CF 1089 L - Lazyland
// https://codeforces.com/contest/1089/problem/L

﻿/*
 * Problem: Lazyland
 * 
 * Algorithm/Technique: Greedy approach with sorting
 * 
 * Time Complexity: O(n log n) due to sorting the list of persuasions
 * Space Complexity: O(n) for storing input arrays and auxiliary data structures
 * 
 * Approach:
 * 1. For each job, we find the maximum persuasion time needed among all idlers who chose that job.
 * 2. We count how many jobs have no choosers (i.e., jobs with zero persuasion time).
 * 3. For each idler, we determine if their choice is the best (maximum persuasion time) for that job.
 *    If so, we mark it as being replaced (incrementing the max). If not, we add their persuasion time
 *    to a list for potential replacement.
 * 4. Sort the list of persuasion times in ascending order.
 * 5. Select the minimum persuasion times from the list to cover the missing jobs.
 * 
 * Input:
 *   - n: number of idlers
 *   - k: number of jobs
 *   - a[]: jobs chosen by each idler
 *   - b[]: persuasion times for each idler
 * 
 * Output:
 *   - Minimum total time to convince idlers to cover all jobs
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace Lazyland {
internal class Program {
  static void Main(string[] args) {
    string[] split = Console.ReadLine().Split(' ');
    int input_1 = Convert.ToInt32(split[0]),
        input_2 = Convert.ToInt32(split[1]), jobs_open = 0;
    long answer = 0;
    split = Console.ReadLine().Split(' ');
    int[] container_1 = new int[input_1], container_2 = new int[input_1],
          maxi = new int[input_2];
    for (int x = 0; x < input_1; ++x) {
      container_1[x] = Convert.ToInt32(split[x]);
    }
    split = Console.ReadLine().Split(' ');
    for (int y = 0; y < input_1; ++y) {
      container_2[y] = Convert.ToInt32(split[y]);
    }
    // For each job, we store the maximum persuasion needed for the idlers who chose it
    for (int z = 0; z < input_1; ++z) {
      maxi[container_1[z] - 1] =
          Math.Max(maxi[container_1[z] - 1], container_2[z]);
    }
    // Count the number of jobs that have zero choosers
    for (int a = 0; a < input_2; ++a) {
      if (maxi[a] == 0) {
        jobs_open += 1;
      }
    }
    List<int> idler = new List<int>();
    // Determine which idlers' persuasion times are needed for job switching
    for (int b = 0; b < input_1; ++b) {
      // If this idler has the highest persuasion time for the job they chose
      if (maxi[container_1[b] - 1] == container_2[b]) {
        // Indicate that this job will be covered by another idler (simulate replacement)
        maxi[container_1[b] - 1] += 1;
      } else if (maxi[container_1[b] - 1] > container_2[b]) {
        // Add this idler's persuasion time to the replacement candidates
        idler.Add(container_2[b]);
      }
    }
    // Sort the candidate persuasions in increasing order
    idler.Sort();
    // Select the minimum persuasion costs to convince necessary idlers
    for (int c = 0; c < idler.Count && c < jobs_open; ++c) {
      answer += idler[c];
    }
    Console.WriteLine(answer);
    Console.ReadLine();
  }
}
}


// https://github.com/VaHiX/CodeForces/