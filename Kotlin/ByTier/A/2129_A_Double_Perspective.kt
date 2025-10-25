// Problem: CF 2129 A - Double Perspective
// https://codeforces.com/contest/2129/problem/A

/*
 * Problem: Maximize f(S') - g(S') where S' is a subset of given pairs
 * Algorithm: 
 *   - Use Union-Find (DSU) to manage connectivity and detect cycles in graph representation
 *   - Sort edges by (b - a) descending to prioritize longer segments first for maximizing f(S')
 *   - For each edge, if adding it doesn't create a cycle, include it in the result
 *   - This approach is based on the idea that:
 *     * f(S') corresponds to total length of union of intervals
 *     * g(S') counts nodes involved in cycles of length >= 3
 *     * To maximize f(S') - g(S'), we want to include as many segments as possible,
 *       but minimize the number of nodes in cycles.
 * Time Complexity: O(n log n + α(n) * n), where α is inverse Ackermann function (nearly constant)
 * Space Complexity: O(n)
 */

import java.util.*
import kotlin.math.*
import kotlin.collections.*

class DSU(n: Int) {
    private val parent = IntArray(n + 1) { it }
    private val rank = IntArray(n + 1)
    
    fun find(x: Int): Int {
        if (parent[x] != x) {
            parent[x] = find(parent[x]) // Path compression
        }
        return parent[x]
    }
    
    fun union(a: Int, b: Int): Boolean {
        var aRoot = find(a)
        var bRoot = find(b)
        if (aRoot == bRoot) return false // Already connected, forming a cycle
        
        // Union by rank
        if (rank[aRoot] < rank[bRoot]) {
            val temp = aRoot
            aRoot = bRoot
            bRoot = temp
        }
        parent[bRoot] = aRoot
        if (rank[aRoot] == rank[bRoot]) {
            rank[aRoot]++
        }
        return true
    }
}

fun main() {
    val reader = System.`in`.bufferedReader()
    val t = reader.readLine().toInt()
    
    repeat(t) {
        val n = reader.readLine().toInt()
        
        // Read pairs and store with original index (1-based)
        val v = Array(n) {
            val (a, b) = reader.readLine().split(" ").map { it.toInt() }
            arrayOf(b - a, a, b, it + 1) // [segment_length, start, end, original_index]
        }
        
        // Sort by segment length in descending order to prioritize longer segments
        v.sortWith(compareByDescending { it[0] }) 
        
        val dsu = DSU(2 * n + 5) // DSU for nodes from 1 to 2*n+5
        val result = mutableListOf<Int>()
        
        for (e in v) {
            // Try to add edge (e[1], e[2]) to the spanning forest
            // If union succeeds, it means no cycle was formed, so include edge
            if (dsu.union(e[1], e[2])) {
                result.add(e[3])
            }
        }
        
        println(result.size)
        println(result.joinToString(" "))
    }
}


// https://github.com/VaHiX/CodeForces/