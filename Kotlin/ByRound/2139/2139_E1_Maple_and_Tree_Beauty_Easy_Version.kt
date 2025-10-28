// Problem: CF 2139 E1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2139/problem/E1

/**
 * Problem: E1. Maple and Tree Beauty (Easy Version)
 *
 * Purpose:
 *   This solution computes the maximum "beauty" of a labeled rooted tree,
 *   where beauty is defined as the length of the longest common subsequence
 *   (LCS) of names of all leaves.
 *
 *   A name of a vertex is formed by concatenating labels from root to that vertex.
 *   Labels are either 0 or 1. Exactly k vertices must be labeled 0, others 1.
 *
 * Algorithms/Techniques:
 *   - Tree parsing and depth calculation using DFS
 *   - Layer (depth) analysis of tree structure
 *   - Dynamic Programming (DP) approach for assigning labels to maximize LCS
 *   - Greedy assignment of labels based on layer constraints
 *
 * Time Complexity: O(n * k * L), where n is number of nodes, k is number of zeros,
 *                  and L is the maximum depth. In worst case it can be up to O(n^3).
 *
 * Space Complexity: O(n * k + n), for storing DP table and tree data.
 *
 * Notes:
 *   - The algorithm assumes that we want to assign 0's and 1's to achieve maximum
 *     LCS among leaves. This is done using a greedy-like DP approach.
 *   - Layers of the tree are analyzed to ensure feasibility of label assignments.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.io.StreamTokenizer
import java.util.*
private val sc = Scanner( System.`in` )
private val br = BufferedReader( InputStreamReader( System.`in` ) )
private val st = StreamTokenizer( br )
private val pw = PrintWriter( System.out )
fun main() {
    solve()
    pw.close()
}
private fun solve() {
    val tn = st.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}
private class RTree( val n: Int, val layers: IntArray ) {
    companion object {
        fun readTree( n: Int ): RTree {
            val p = IntArray( n ) { if ( it == 0 ) -1 else st.nextInt() - 1 }
            val deg = IntArray( n )
            for ( i in 1 until n ) deg[p[i]] ++ // Compute out-degree of each node
            val depth = IntArray( n ) { -1 }
            depth[0] = 0
            for ( i in 1 until n ) dfs( i, depth, p )  // DFS to assign depths
            val firstLeaf = depth.indices.filter { deg[it] == 0 }.minOf { depth[it] }  // Find the shallowest leaf layer
            val layers = IntArray( firstLeaf + 1 )
            for ( d in depth ) {
                if ( d < layers.size ) layers[d] ++ // Count how many nodes are at each depth level
            }
            return RTree( n, layers )
        }
        private fun dfs( v: Int, depth: IntArray, p: IntArray ) {
            if ( depth[v] >= 0 ) return
            dfs( p[v], depth, p )
            depth[v] = depth[p[v]] + 1  // Propagate depth information up the tree
        }
    }
}
private fun solveTest() {
    val n = st.nextInt()
    val k = st.nextInt()
    val tree = RTree.readTree( n )  // Parse and process tree layers
    val dp = Array( k + 1 ) { BooleanArray( n - k + 1 ) }  // DP table: [zeros_used][ones_used]
    dp[0][0] = true  // Base case: no zeros or ones used yet
    var sum = 0
    tree.layers.forEachIndexed { i, ls ->
        var ok = false
        for ( a in 0 .. sum ) {  // Iterate through number of zeros assigned so far
            val b = sum - a  // Corresponding number of ones
            if ( a <= k && b <= n - k && dp[a][b] ) {
                // Try assigning all leaves at this layer to zeros or ones
                if ( a + ls <= k ) {  // If we can add these leaves as zeros
                    dp[a + ls][b] = true  // Mark new state in DP
                    ok = true
                }
                if ( b + ls <= n - k ) {  // If we can add these leaves as ones
                    dp[a][b + ls] = true  // Mark new state in DP
                    ok = true
                }
            }
        }
        if ( ! ok ) {
            pw.println( i )  // No valid assignment found: output current layer index
            return
        }
        sum += ls  // Update the total number of visited nodes so far
    }
    pw.println( tree.layers.size )  // All layers were feasible
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/