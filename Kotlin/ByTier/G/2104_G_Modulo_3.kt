// Problem: CF 2104 G - Modulo 3
// https://codeforces.com/contest/2104/problem/G

/*
 * Problem: G. Modulo 3 (Functional Graph Coloring)
 * 
 * Purpose:
 *   Given a functional graph with n vertices and q queries, each query modifies an edge and 
 *   calculates the number of valid colorings modulo 3, where each vertex can be colored in k different colors.
 * 
 * Approach:
 *   - Uses DSU (Disjoint Set Union) with rollback to track connected components and parity information.
 *   - Builds a segment tree to process updates and queries efficiently over time.
 *   - For each query, the graph is rebuilt from scratch using DSU with path compression and rollback.
 *   - The number of valid colorings is calculated using combinatorics: for k colors and n connected components,
 *     possible colorings = k ^ (number of components) mod 3.
 * 
 * Time Complexity:
 *   O((n + q) * log(n)) where each operation in DSU with rollback is nearly constant amortized time.
 * 
 * Space Complexity:
 *   O(n + q) for DSU arrays and segment tree structure.
 */

import kotlin.math.log2

const val MAXN = 5 * 100000
const val LOGN = 19 

data class Pair(val first: Int, val second: Int)

class DSU(n: Int) {
    val p = IntArray(n + 1) { it } // Parent array for Union-Find
    val sz = IntArray(n + 1) { 1 } // Size of each component
    val par = IntArray(n + 1) { 0 } // Parity of the path to root (xor flag)
    var even = 0 // Tracks whether total number of cycles is even or odd
    val ops = mutableListOf<Triple<Int, Triple<Int, Int, Int>, Boolean>>() // Rollback info
    
    fun find(x: Int): Pair {
        if (p[x] == x) return Pair(x, 0)
        val pr = find(p[x])
        return Pair(pr.first, pr.second xor par[x]) // Path compression with parity
    }
    
    fun unite(x: Int, y: Int) {
        val a = find(x)
        val b = find(y)
        var rx = a.first
        var ry = b.first
        var px = a.second
        var py = b.second
        
        if (rx == ry) {
            // Self-loop detected => update even parity if needed
            ops.add(Triple(0, Triple(even, 0, 0), true))
            if ((px xor py xor 1) == 0) even = even xor 1
        } else {
            // Union by size with path reversal
            if (sz[rx] > sz[ry]) {
                rx = ry.also { ry = rx }
                px = py.also { py = px }
            }
            ops.add(Triple(rx, Triple(p[rx], sz[ry], par[rx]), false))
            p[rx] = ry
            par[rx] = px xor py xor 1 // Parity update after merge
            sz[ry] += sz[rx]
        }
    }
    
    fun snapshot(): Int = ops.size // Save state for rollback
    
    fun rollback(s: Int) {
        while (ops.size > s) {
            val (u, o, isC) = ops.removeLast()
            if (isC) {
                even = o.first // Restore parity
            } else {
                val ry = p[u]
                sz[ry] = o.second
                p[u] = o.first
                par[u] = o.third
            }
        }
    }
}

class SegmentTree(val q: Int) {
    val seg = MutableList(4 * (q + 1)) { mutableListOf<Pair>() } // Segtree with pairs (u, v)
    
    fun add(o: Int, l: Int, r: Int, ql: Int, qr: Int, e: Pair) {
        if (ql > qr) return
        if (ql <= l && r <= qr) {
            seg[o].add(e) // Add connection in segment tree node
            return
        }
        val m = (l + r) shr 1
        if (ql <= m) add(o shl 1, l, m, ql, qr, e)
        if (qr > m) add((o shl 1) or 1, m + 1, r, ql, qr, e)
    }
    
    fun dfs(o: Int, l: Int, r: Int, dsu: DSU, ans: MutableList<Int>, kq: List<Int>, n: Int) {
        val s = dsu.snapshot() // Save current state
        for (e in seg[o]) dsu.unite(e.first, e.second) // Apply pending unions
        
        if (l == r) {
            val km = kq[l]
            ans[l] = when (km) {
                0 -> 0 // No colorings possible
                1 -> 1 // Only one coloring (all same)
                else -> if ((n and 1) xor dsu.even == 1) 2 else 1 // Based on parity logic
            }
        } else {
            val m = (l + r) shr 1
            dfs(o shl 1, l, m, dsu, ans, kq, n)
            dfs((o shl 1) or 1, m + 1, r, dsu, ans, kq, n)
        }
        
        dsu.rollback(s) // Restore previous state
    }
}

fun main() {
    val (n, q) = readLine()!!.trim().split(" ").map { it.toInt() }
    val g = MutableList(n + 1) { 0 } // Original graph edges
    readLine()!!.trim().split(" ").map { it.toInt() }.forEachIndexed { idx, value -> g[idx + 1] = value }
    
    val segTree = SegmentTree(q)
    val ans = MutableList(q + 1) { 0 }
    val kq = MutableList(q + 1) { 0 }
    val cur = MutableList(n + 1) { 0 } // Current version of graph
    for (i in 1..n) cur[i] = g[i]
    val lst = MutableList(n + 1) { 1 } // Last used time for each node
    
    for (i in 1..q) {
        val (x, y, k) = readLine()!!.trim().split(" ").map { it.toInt() }
        segTree.add(1, 1, q, lst[x], i - 1, Pair(x, cur[x])) // Add to segment tree
        lst[x] = i
        cur[x] = y
        kq[i] = k % 3 // Modulo 3 as required
    }
    
    for (i in 1..n) {
        segTree.add(1, 1, q, lst[i], q, Pair(i, cur[i])) // Add final state to segment tree
    }
    
    val dsu = DSU(n)
    segTree.dfs(1, 1, q, dsu, ans, kq, n)
    
    for (i in 1..q) {
        println(ans[i])
    }
}


// https://github.com/VaHiX/CodeForces/