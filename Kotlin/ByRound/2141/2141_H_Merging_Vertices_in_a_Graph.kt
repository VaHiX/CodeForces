// Problem: CF 2141 H - Merging Vertices in a Graph
// https://codeforces.com/contest/2141/problem/H

/*
H. Merging Vertices in a Graph

Algorithms/Techniques:
- Graph traversal using BFS
- Simulation of merging operations
- Finding minimum and maximum number of operations by identifying connected components and their sizes

Time Complexity: O(n + m)
Space Complexity: O(n + m)

The problem involves simulating a process where vertices in an undirected graph are merged,
creating a new vertex that connects to all common neighbors of the two merged vertices.
We compute the minimum and maximum number of operations possible before a universal vertex
(connected to all other vertices) appears.

The solution identifies the smallest connected component size in the graph to determine
the minimum number of operations, and uses a BFS-like approach to simulate the maximum
number of operations.

*/
import java.io.BufferedInputStream

private class FS {
    private val i = BufferedInputStream(System.`in`)
    private val b = ByteArray(1 shl 16)
    private var l = 0
    private var p = 0
    private fun r(): Int {
        if (p >= l) {
            l = i.read(b)
            p = 0
            if (l < 0) return -1
        }
        return b[p++].toInt()
    }
    fun n(): Int {
        var c = r()
        while (c <= 32) c = r()
        var s = 1
        if (c == 45) {
            s = -1
            c = r()
        }
        var x = 0
        while (c > 32) {
            x = x * 10 + (c - 48)
            c = r()
        }
        return x * s
    }
}

fun main() {
    val fs = FS()
    val n = fs.n()
    val m = fs.n()
    val d = IntArray(n + 1) // degree of each vertex
    val a = IntArray(m)
    val c = IntArray(m)
    for (k in 0 until m) {
        val u = fs.n()
        val v = fs.n()
        a[k] = u
        c[k] = v
        d[u]++
        d[v]++
    }
    
    // If any vertex has degree n-1, it's already universal, so no operations possible
    for (i in 1..n) if (d[i] == n - 1) {
        println("0 0")
        return
    }
    
    // Build adjacency list representation of the graph
    val g = Array(n + 1) { IntArray(d[it]) }
    val ptr = IntArray(n + 1)
    for (k in 0 until m) {
        val u = a[k]
        val v = c[k]
        g[u][ptr[u]++] = v
        g[v][ptr[v]++] = u
    }
    
    // Set up singly linked list to keep track of unvisited vertices
    val nx = IntArray(n + 1)
    var h = if (n >= 1) 1 else 0
    for (i in 1 until n) nx[i] = i + 1
    
    val mk = BooleanArray(n + 1) // mark visited vertices
    val tmp = IntArray(n + 5)
    val q = IntArray(n + 5 + n) // queue for BFS traversal
    
    var mn = n // minimum component size
    var left = n // number of remaining vertices (initially n)
    
    while (h != 0) {
        var u = h
        h = nx[h]
        var sz = 0 // component size
        var qh = 0
        var qt = 0
        q[qt++] = u
        while (qh < qt) {
            val v = q[qh++]
            sz++
            var t = 0
            mk[v] = true
            tmp[t++] = v // store vertices in current component
            
            val gv = g[v]
            var j = 0
            while (j < gv.size) {
                val w = gv[j]
                if (!mk[w]) {
                    mk[w] = true
                    tmp[t++] = w
                }
                j++
            }
            
            // Remove processed vertices from the linked list
            var p = 0
            var cur = h
            while (cur != 0) {
                val nxcur = nx[cur]
                if (!mk[cur]) {
                    if (p == 0) h = nxcur else nx[p] = nxcur
                    q[qt++] = cur
                } else p = cur
                cur = nxcur
            }
            
            // Clear visited marks for next iteration
            var k = 0
            while (k < t) {
                mk[tmp[k]] = false
                k++
            }
        }
        if (sz < mn) mn = sz // update minimum component size
        left -= sz // subtract component size from remaining vertices
    }
    
    val minOps = mn - 1 // minimum number of operations is size of smallest component minus one
    val maxOps = n - 1 // maximum number of operations = total vertices minus one
    
    println("$minOps $maxOps")
}


// https://github.com/VaHiX/codeForces/