// Problem: CF 1431 H - Rogue-like Game
// https://codeforces.com/contest/1431/problem/H

/*
 * Problem: Rogue-like Game
 * 
 * Purpose: Find the minimum number of runs to unlock all species and classes,
 *          considering that one combination can be boosted with a guide (adding k points).
 * 
 * Approach:
 * - Preprocess the maximum possible score for each unlocked species and class.
 * - For each species, find the maximum score we can get in runs matching that species.
 * - For each class, find the maximum score we can get in runs matching that class.
 * - Combine and sort these (species and classes) by their unlock thresholds.
 * - Try each of the N+M combinations as the guide (boosting one of them by k points).
 * - For each combination, simulate the process of unlocking in order of thresholds,
 *   calculating the number of runs needed.
 * 
 * Time Complexity: O((N + M) * log(N + M) + (N + M)^2)
 * Space Complexity: O(N + M)
 */

import java.lang.Long.max

fun main() {
  val (N, M, K) = readLine()!!.split(' ').map { it.toInt() }
  val A = readLine()!!.split(' ').map { it.toLong() }
  val B = readLine()!!.split(' ').map { it.toLong() }
  val C = (0 until N).map { readLine()!!.split(' ').map { it.toLong() } }
  
  // Calculate maximum score for each species (when unlocked)
  val AOpen = (0 until N).map { i -> 
    A[i] to (0 until B.count { it <= A[i] }).map { j -> C[i][j] }.max()!! 
  }
  
  // Calculate maximum score for each class (when unlocked)
  val BOpen = (0 until M).map { i -> 
    B[i] to (0 until A.count { it <= B[i] }).map { j -> C[j][i] }.max()!! 
  }
  
  // Combine into list of (threshold, max_score) pairs and sort
  val open = (AOpen + BOpen).sortedBy { it.first }
  
  // Try each position (0 to N+M-1) as the guide (i.e., boost that specific combination by k)
  val ans = (0 until N + M)
      .map { i ->
        var ans = 0L
        var cur = 0L
        // Initially, boost the chosen combination if it's the first one
        var mx = open[0].second + (if (i == 0) K else 0)
        
        // Simulate the unlocking process
        (1 until N + M).forEach {
          // Calculate how many runs needed to reach the next threshold
          val missing = (open[it].first - cur + mx - 1) / mx // Ceil division
          cur += missing * mx
          ans += missing
          
          // Update max score considering boost if it's this position
          var self = open[it].second + (if (i == it) K else 0)
          mx = max(mx, self)
        }
        ans
      }
      .min()
  
  println(ans)
}


// https://github.com/VaHiX/CodeForces/