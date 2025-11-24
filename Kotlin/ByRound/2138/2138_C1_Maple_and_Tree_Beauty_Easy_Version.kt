// Problem: CF 2138 C1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2138/problem/C1

/*
 * Problem: C1. Maple and Tree Beauty (Easy Version)
 *
 * Purpose:
 *   Given a rooted tree with n vertices, each vertex can be labeled as 0 or 1.
 *   There are exactly k zeros and (n - k) ones.
 *   For each leaf node, we compute the binary string formed by concatenating labels from root to leaf.
 *   The beauty of the tree is defined as the length of the longest common subsequence (LCS)
 *   among all leaf names.
 *   Task is to determine maximum possible beauty over all valid labelings.
 *
 * Algorithm:
 *   1. Build a tree from parent array.
 *   2. For each root-to-leaf path, compute depth and store count of nodes at each depth.
 *   3. Use dynamic programming to explore all possible ways of placing zeros among depths,
 *      trying to maximize LCS by finding best split of k zeros between depths.
 *   4. Answer is `mn + 1` if it's better than current (for edge case), otherwise `mn`.
 *
 * Time Complexity:
 *   O(n^2) per test case due to DP and nested loops over depths and counts.
 *
 * Space Complexity:
 *   O(n) for storing tree structure, counts, and DP table.
 */

import java.util.*

fun main() {
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    repeat(t) {
        val n = sc.nextInt()
        val k = sc.nextInt()
        val g = Array(n) { mutableListOf<Int>() }
        for (i in 1 until n) {
            val u = sc.nextInt() - 1
            g[u].add(i)
        }
        val cnt = IntArray(n)
        var mn = Int.MAX_VALUE
        
        // DFS to count nodes at each depth and find minimum depth of leaves
        fun dfs(u: Int, depth: Int) {
            cnt[depth]++ // Count how many nodes are at this depth
            if (g[u].isEmpty()) mn = minOf(mn, depth) // If leaf node, update min depth
            for (v in g[u]) dfs(v, depth + 1)
        }
        dfs(0, 0)

        val dp = BooleanArray(n + 1)
        dp[0] = true // Base case: no nodes selected, possible

        // Dynamic programming on counting valid placements of zeros
        for (i in 0..mn) {
            for (j in n downTo cnt[i]) {
                if (dp[j - cnt[i]]) dp[j] = true // Update DP array
            }
        }

        val sum = (0..mn).sumOf { cnt[it] } // Total number of nodes

        var ans = (sum <= k || sum <= n - k) // Trivial condition for early answer

        // Check all possible ways to place zeros and compute optimal LCS
        for (i in 0..sum) {
            if (dp[i]) {
                if (i <= k && sum - i <= n - k) ans = true
            }
        }

        println(if (ans) mn + 1 else mn) // Output result based on computed answer
    }
}


// https://github.com/VaHiX/codeForces/