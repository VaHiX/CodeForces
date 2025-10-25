// Problem: CF 1346 I - Pac-Man 2.0
// https://codeforces.com/contest/1346/problem/I

/**
 * Problem: Pac-Man 2.0
 * 
 * Purpose: Compute the minimum number of pathway traversals required to collect a given number of pellets,
 * considering that pellets respawn after all are collected.
 * 
 * Algorithms/Techniques:
 * - Floyd-Warshall for shortest paths between all pairs of nodes
 * - Dynamic Programming with bitmasking to track visited nodes and collect pellets efficiently
 * - Binary lifting technique to compute cumulative paths quickly
 * - Precomputed prefix sums of pellet counts for efficient lookup
 * 
 * Time Complexity: O(n^3 + n * 2^n + q * n * log C)
 * Space Complexity: O(n^2 + n * 2^n + n^2 * log C)
 */
fun main() {
  val INF = 1e9.toInt()
  val INF64 = 1e18.toLong()
  val LOG = 60
  var (n, m, q, s) = readLine()!!.split(' ').map { it.toInt() }
  s-- // Convert to 0-based indexing
  val a = readLine()!!.split(' ').map { it.toInt() }
  val summask = LongArray(1 shl n) { 0 } // Precompute sum for each subset of nodes
  for (mask in 0 until (1 shl n)) {
    for (i in 0 until n) {
      if ((mask and (1 shl i)) > 0) summask[mask] += a[i].toLong()
    }
  }
  val d = Array(n) { IntArray(n) { INF } } // Distance matrix for Floyd-Warshall
  for (i in 0 until m) {
    val (x, y) = readLine()!!.split(' ').map { it.toInt() }
    d[x - 1][y - 1] = 1 // Direct path with weight 1
  }
  val C = readLine()!!.split(' ').map { it.toLong() }
  
  // Floyd-Warshall to find shortest paths
  for (k in 0 until n) {
    for (i in 0 until n) {
      for (j in 0 until n) d[i][j] = minOf(d[i][j], d[i][k] + d[k][j])
    }
  }
  
  // dp[st][j][mask] = minimum steps from start 'st' to node 'j' having visited nodes in 'mask'
  val dp = Array(n) { Array(n) { IntArray(1 shl n) { INF } } }
  for (st in 0 until n) {
    dp[st][st][1 shl st] = 0 // Base case: start at node st with just that node visited
    for (mask in 0 until (1 shl n)) {
      for (i in 0 until n) {
        if ((mask and (1 shl i)) == 0) continue // Skip if node 'i' not in current mask
        for (j in 0 until n) {
          if ((mask and (1 shl j)) > 0) continue // Skip if node 'j' already in mask
          // Update dp with new state: move from 'i' to 'j' with additional node 'j'
          dp[st][j][mask or (1 shl j)] =
              minOf(dp[st][j][mask or (1 shl j)], dp[st][i][mask] + d[i][j])
        }
      }
    }
  }
  
  // bst[i][t] = maximum pellets that can be collected in exactly 't' steps starting from node 'i'
  val bst = Array(n) { LongArray(n * n) { 0 } }
  for (i in 0 until n) {
    for (mask in 0 until (1 shl n)) {
      if ((mask and (1 shl i)) > 0) {
        for (j in 0 until n) {
          if (dp[i][j][mask] != INF)
              bst[i][dp[i][j][mask]] = maxOf(bst[i][dp[i][j][mask]], summask[mask])
        }
      }
    }
  }
  
  // steps[t][i][j] = minimum paths from node 'i' to 'j' in exactly 2^t steps
  val steps = Array(LOG) { Array(n) { LongArray(n) { INF64 } } }
  for (i in 0 until n) {
    for (j in 0 until n) steps[0][i][j] = dp[i][j][(1 shl n) - 1].toLong()
  }
  for (t in 1 until LOG) {
    for (i in 0 until n) {
      for (j in 0 until n) {
        for (k in 0 until n) steps[t][i][j] =
            minOf(steps[t][i][j], steps[t - 1][i][k] + steps[t - 1][k][j])
      }
    }
  }
  
  for (qr in 0 until q) {
    val sum = summask[(1 shl n) - 1] // Total pellets in all zones
    val need = C[qr] / sum // How many full cycles are needed
    var cur = LongArray(n) { INF64 } // Minimum steps to reach each node using binary lifting
    cur[s] = 0
    for (t in 0 until LOG - 1) {
      if ((need and (1L shl t)) > 0) {
        val ncur = LongArray(n) { INF64 }
        for (i in 0 until n) {
          for (j in 0 until n) ncur[i] = minOf(ncur[i], steps[t][j][i] + cur[j])
        }
        cur = ncur
      }
    }
    var ans = INF64
    for (i in 0 until n) {
      val lft = C[qr] % sum // Remaining pellets needed after full cycles
      for (j in 0 until n * n) {
        if (bst[i][j] >= lft) ans = minOf(ans, cur[i] + j)
      }
    }
    println(ans)
  }
}


// https://github.com/VaHiX/CodeForces/