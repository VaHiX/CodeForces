// Problem: CF 2110 D - Fewer Batteries
// https://codeforces.com/contest/2110/problem/D

/**
 * Problem: D. Fewer Batteries
 * 
 * Description:
 * In a robot competition, the robot must travel from checkpoint 1 to checkpoint n.
 * Each checkpoint has a number of batteries available (b_i). The robot starts with no batteries
 * and may collect up to b_i batteries at each checkpoint.
 * There are directed edges between checkpoints that require a minimum number of batteries (w_i)
 * to traverse. The goal is to find the minimum number of batteries needed at the end when reaching checkpoint n,
 * or -1 if unreachable.
 * 
 * Approach:
 * - Use binary search on the answer (minimum batteries required at the end).
 * - For each candidate value M, check whether it's possible to reach the destination using BFS-style DP.
 * - The DP tracks for each node: whether it is reachable, and the maximum cumulative battery count
 *   achievable with sufficient energy to pass through all valid edges.
 * 
 * Algorithms/Techniques:
 * - Binary Search (on the result)
 * - Dynamic Programming with graph traversal
 * 
 * Time Complexity: O(m * log(maxW)) where maxW is the maximum weight edge
 * Space Complexity: O(n + m)
 */
fun main() {
    val t = readln().toInt()
    repeat(t) {
        val (n, m) = readln().split(" ").map { it.toInt() }
        val b = LongArray(n + 1)
        val inputB = readln().split(" ").map { it.toLong() }
        for (i in 1..n) {
            b[i] = inputB[i - 1]
        }
        val adj = Array(n + 1) { mutableListOf<Pair<Int, Long>>() }
        var maxW = 0L
        repeat(m) {
            val (s, t, w) = readln().split(" ")
            val from = s.toInt()
            val to = t.toInt()
            val weight = w.toLong() // Weighted edge going from -> to
            adj[to].add(from to weight)
            maxW = maxOf(maxW, weight)
        }
        if (m == 0) {
            println(if (n == 1) "0" else "-1")
            return@repeat
        }
        fun check(M: Long): Boolean {
            val dp = BooleanArray(n + 1) { false } // Whether node i is reachable
            val cum = LongArray(n + 1) { -1L }    // Maximum cumulative battery count at node i
            dp[1] = true
            cum[1] = b[1]
            for (v in 2..n) {
                var maxCumV = -1L
                var canReach = false
                for ((u, w) in adj[v]) { // For all predecessors u of v
                    if (w <= M && dp[u] && cum[u] >= w) { // Valid transition with sufficient battery
                        canReach = true
                        maxCumV = maxOf(maxCumV, cum[u] + b[v])
                    }
                }
                if (canReach) {
                    dp[v] = true
                    cum[v] = maxCumV
                }
            }
            return dp[n]
        }

        var low = 0L
        var high = maxW
        while (low < high) {
            val mid = (low + high) / 2
            if (check(mid)) {
                high = mid
            } else {
                low = mid + 1
            }
        }
        println(if (check(low)) low else -1)
    }
}


// https://github.com/VaHiX/CodeForces/