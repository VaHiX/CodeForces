// Problem: CF 2131 D - Arboris Contractio
// https://codeforces.com/contest/2131/problem/D

/*
 * Problem: D. Arboris Contractio
 *
 * Purpose: Given a tree, find the minimum number of operations to minimize its diameter.
 *          Each operation allows choosing two vertices s and t, removing the path between them,
 *          and connecting all intermediate vertices directly to s.
 *
 * Algorithms/Techniques:
 * - Tree diameter computation using BFS/DFS
 * - Segment tree for efficient range maximum queries
 * - Leaf counting and centroid-based approach
 *
 * Time Complexity: O(n log n) per test case (due to segment tree operations)
 * Space Complexity: O(n) for segment tree and adjacency list
 */

import java.util.*

class SegmentTree(private val n: Int) {
    private val tree = IntArray(4 * n)
    
    // Builds the segment tree from an array
    fun build(arr: IntArray, id: Int, l: Int, r: Int) {
        if (l == r) {
            tree[id] = arr[l]
            return
        }
        val mid = (l + r) / 2
        build(arr, id * 2, l, mid)
        build(arr, id * 2 + 1, mid + 1, r)
        tree[id] = maxOf(tree[id * 2], tree[id * 2 + 1])
    }
    
    // Query for maximum value in range [u, v]
    fun queryMax(id: Int, l: Int, r: Int, u: Int, v: Int): Int {
        if (r < u || l > v) return Int.MIN_VALUE
        if (u <= l && r <= v) return tree[id]
        val mid = (l + r) / 2
        return maxOf(
            queryMax(id * 2, l, mid, u, v),
            queryMax(id * 2 + 1, mid + 1, r, u, v)
        )
    }
}

fun main() {
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    
    repeat(t) {
        val n = sc.nextInt()
        val adj = Array(n + 1) { mutableListOf<Int>() }
        val deg = IntArray(n + 1)
        
        // Read edges and build adjacency list
        repeat(n - 1) {
            val u = sc.nextInt()
            val v = sc.nextInt()
            adj[u].add(v)
            adj[v].add(u)
            deg[u]++
            deg[v]++
        }
        
        // Special case: two nodes form a diameter of 1
        if (n == 2) {
            println(0)
            return@repeat
        }
        
        var ans = 0
        val leafCnt = IntArray(n + 1)
        
        // Count how many leaves are connected to each node
        for (u in 1..n) {
            if (deg[u] == 1) { // Node u is a leaf
                ans++   // Increment operation count
                for (v in adj[u]) {
                    leafCnt[v]++ // Increase count of adjacent nodes
                }
            }
        }
        
        // Build segment tree for range max queries
        val seg = SegmentTree(n)
        seg.build(leafCnt, 1, 1, n)
        
        // Find maximum number of leaves connected to a single node (that could be reduced)
        val cnt = seg.queryMax(1, 1, n, 1, n)
        
        // Result is total operations minus max leaf count
        println(ans - cnt)
    }
}


// https://github.com/VaHiX/codeForces/