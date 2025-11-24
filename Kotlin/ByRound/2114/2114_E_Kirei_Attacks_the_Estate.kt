// Problem: CF 2114 E - Kirei Attacks the Estate
// https://codeforces.com/contest/2114/problem/E

/*
 * Problem: E. Kirei Attacks the Estate
 * 
 * Purpose:
 *   This code computes the maximum alternating sum along vertical paths from each node to the root,
 *   in a tree where each node has a danger value 'a[i]'.
 *   For each vertex, it calculates the threat value as defined by the alternating sum:
 *   a_i - a_{p_i} + a_{p_{p_i}} - ...
 *   where p_i is the parent of vertex i in the path to root.
 *
 * Algorithms Used:
 *   - BFS Traversal to build parent array and order of nodes from root
 *   - Dynamic Programming on Tree to compute max threat value per node
 *
 * Time Complexity: O(n) for each test case, since we do a single traversal (BFS) and a second traversal (DP).
 * Space Complexity: O(n) due to adjacency list, parent array, order list, and DP arrays.
 */

import java.util.*
import kotlin.math.*

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val n = scanner.nextInt()
        val a = LongArray(n + 1)
        for (i in 1..n) {
            a[i] = scanner.nextLong() // Read dangers of all vertices
        }
        val adj = Array(n + 1) { mutableListOf<Int>() } // Adjacency list for the tree
        repeat(n - 1) {
            val u = scanner.nextInt()
            val v = scanner.nextInt()
            adj[u].add(v)
            adj[v].add(u)
        }
        val parent = IntArray(n + 1)
        val order = mutableListOf<Int>()
        val q: Queue<Int> = LinkedList()
        q.add(1)
        parent[1] = 0
        order.add(1)
        while (q.isNotEmpty()) {
            val u = q.poll() // BFS to compute parent and traversal order
            for (v in adj[u]) {
                if (v != parent[u]) {
                    parent[v] = u
                    q.add(v)
                    order.add(v)
                }
            }
        }
        val maxThreat = LongArray(n + 1) // Stores the maximum alternating sum for each node
        val minSum = LongArray(n + 1)   // Stores minimum alternating sum seen so far during path
        for (u in order) {
            if (u == 1) {
                // Root node's threat is its own danger
                maxThreat[u] = a[u]
                minSum[u] = a[u]
            } else {
                val p = parent[u]
                // Max threat = max of current element or (current - minSum of parent)
                maxThreat[u] = max(a[u], a[u] - minSum[p])
                // Min sum = min of current element or (current - maxThreat of parent)
                minSum[u] = min(a[u], a[u] - maxThreat[p])
            }
        }
        println((1..n).joinToString(" ") { maxThreat[it].toString() })
    }
}


// https://github.com/VaHiX/CodeForces/