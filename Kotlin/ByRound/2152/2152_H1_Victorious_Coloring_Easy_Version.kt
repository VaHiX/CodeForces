// Problem: CF 2152 H1 - Victorious Coloring (Easy Version)
// https://codeforces.com/contest/2152/problem/H1

/*
 * Problem: H1. Victorious Coloring (Easy Version)
 * Purpose:
 *   This code solves a tree-based optimization problem where we are tasked with assigning non-negative weights to vertices such that for a given threshold `l`, the minimum cost of a "victorious coloring" satisfies f(x) >= l, and the total sum of vertex weights is minimized.
 *
 * Algorithms/Techniques:
 *   - Union-Find (Disjoint Set Union) for building a maximum spanning tree
 *   - Tree DP (Dynamic Programming) to compute required weight adjustments
 *   - Greedy approach with preprocessing of edges sorted by weight
 *
 * Time Complexity: O(n log n + q * n), where n is number of vertices and q is number of queries.
 * Space Complexity: O(n)
 */
import java.io.BufferedInputStream
import kotlin.math.*
private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c = readByte()
        while (c <= 32 && c >= 0) c = readByte()
        var sign = 1
        if (c == '-'.code) {
            sign = -1
            c = readByte()
        }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = readByte()
        }
        return res * sign
    }
    fun nextLong(): Long = nextInt().toLong()
}
fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    repeat(t) {
        val n = fs.nextInt()
        val edges = ArrayList<Triple<Long, Int, Int>>(n - 1)
        repeat(n - 1) {
            val u = fs.nextInt() - 1
            val v = fs.nextInt() - 1
            val w = fs.nextLong()
            edges.add(Triple(w, u, v))
        }
        edges.sortWith(compareByDescending<Triple<Long, Int, Int>> { it.first }) // Sort edges by weight in descending order to build MST greedily
        val size = 2 * n - 1
        val parent = IntArray(size) { it } // Union-Find data structure for grouping components
        val left = IntArray(size) { -1 }   // Left child node index in the binary tree representation of the forest
        val right = IntArray(size) { -1 }  // Right child node index in the binary tree representation of the forest
        val cost = LongArray(size)
        fun find(x: Int): Int {
            var a = x
            while (parent[a] != a) {
                parent[a] = parent[parent[a]] // Path compression
                a = parent[a]
            }
            return a
        }
        for (i in 0 until n - 1) {
            val (w, uu, vv) = edges[i]
            var u = find(uu)
            var v = find(vv)
            val newNode = i + n
            parent[u] = newNode // Merge two components into a new node
            parent[v] = newNode
            left[newNode] = u
            right[newNode] = v
            cost[uu] += w  // Accumulate edge weights for vertex cost adjustments
            cost[vv] += w
            cost[newNode] -= 2L * w // The new node's contribution to edges is reduced by twice the weight because it represents two endpoints connected
        }
        for (i in n until (2 * n - 1)) {
            val l = left[i]
            val r = right[i]
            // Propagate child costs upward
            cost[i] += (if (l >= 0) cost[l] else 0L) + (if (r >= 0) cost[r] else 0L)
        }
        val q = fs.nextInt()
        repeat(q) {
            val x = fs.nextLong()
            val dp = LongArray(size)
            var ans = 0L
            for (i in 0 until (2 * n - 1)) {
                if (i >= n) {
                    // For internal nodes, update DP based on their children's DP values
                    val l = left[i]
                    val r = right[i]
                    dp[i] += dp[l] + dp[r]
                }
                // Calculate the needed additional weight to ensure cost is at least x
                val need = x - cost[i] - dp[i]
                if (need > 0) {
                    ans += need
                    dp[i] += need
                }
            }
            out.append(ans).append('\n')
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/