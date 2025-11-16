// Problem: CF 2117 G - Omg Graph
// https://codeforces.com/contest/2117/problem/G

/*
 * Problem: G. Omg Graph
 * 
 * Purpose:
 *   Find the minimum cost path from vertex 1 to vertex n in an undirected weighted graph,
 *   where the cost of a path is defined as the sum of the minimum and maximum edge weights
 *   along that path.
 *   
 * Algorithm:
 *   - Use Union-Find (DSU) with modifications to track the minimum edge weight in each component.
 *   - Sort edges by weight and process them in increasing order.
 *   - For each edge added, if it connects two components containing 1 or n, check if adding this
 *     edge gives a better (smaller total cost) path from 1 to n.
 *   
 * Time Complexity: O(m log m + m α(n)) where α is the inverse Ackermann function
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 *   - Union-Find with path compression and union by size
 *   - Sorting edges to build minimum spanning tree incrementally
 *   - Tracking min edge weight in each connected component
 */

import java.util.*
import kotlin.math.min

const val INF = 1_000_000_000_000_000L

class DSU(n: Int) {
    private val p = IntArray(n + 1) { it }        // Parent array for union-find
    private val sz = IntArray(n + 1) { 1 }        // Size of each component
    val best = LongArray(n + 1) { INF }          // Minimum edge weight in each component
    
    fun find(v: Int): Int {
        if (p[v] == v) return v
        p[v] = find(p[v])  // Path compression
        return p[v]
    }
    
    fun unite(a0: Int, b0: Int, w: Long) {
        var a = find(a0)
        var b = find(b0)
        if (a == b) {
            // If same component, update the min edge weight in that component
            best[a] = min(best[a], w)
            return
        }
        // Union by size: attach smaller tree to larger tree
        if (sz[a] < sz[b]) {
            val tmp = a
            a = b
            b = tmp
        }
        p[b] = a
        sz[a] += sz[b]
        // Update the minimum edge in the merged component
        best[a] = min(min(best[a], best[b]), w)
    }
}

data class Edge(val u: Int, val v: Int, val w: Long)

fun main() {
    val scanner = Scanner(System.`in`)
    val T = scanner.nextInt()
    repeat(T) {
        val n = scanner.nextInt()
        val m = scanner.nextInt()
        val edges = mutableListOf<Edge>()
        repeat(m) {
            val u = scanner.nextInt()
            val v = scanner.nextInt()
            val w = scanner.nextLong()
            edges.add(Edge(u, v, w))
        }
        // Sort edges by weight ascending
        edges.sortBy { it.w }
        val dsu = DSU(n)
        var ans = INF
        for (ed in edges) {
            // Process the edge: unite the two vertices and maintain minimum edge weight
            dsu.unite(ed.u, ed.v, ed.w)
            // Get root of vertex 1 and n to see if they're connected now
            val r = dsu.find(1)
            if (dsu.find(n) == r) {
                // If both are in same component, calculate total path cost
                val cand = ed.w + dsu.best[r]
                if (cand < ans) ans = cand
            }
        }
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/