// Problem: CF 2126 F - 1-1-1, Free Tree!
// https://codeforces.com/contest/2126/problem/F

/*
 * 1-1-1, Free Tree!
 * 
 * Problem Description:
 * Given a tree with n vertices, each having an initial color a_i, and edges with costs defined as:
 * if adjacent vertices have same color, cost = 0; otherwise cost = c (edge weight).
 * Support q queries to repaint a vertex and output the total sum of edge costs.
 * 
 * The solution uses DFS traversal combined with a hash map to maintain edge contributions per node.
 * For each vertex, we track how many edges connect to other colors using m[v] which maps color -> cumulative cost.
 * 
 * Time Complexity:
 *   O(n + q) amortized per test case due to efficient updates on tree structure.
 * Space Complexity:  
 *   O(n) for storing graph and auxiliary arrays.
 */

var g = arrayOf<MutableList<Pair<Int, Int>>>() // Graph represented as adjacency list with edge weights
var a = mutableListOf<Int>() // Vertex colors
var p = arrayOf<Int>() // Parent array for DFS traversal
var pc = arrayOf<Int>() // Edge weights from parent to child
var m = arrayOf<HashMap<Int, Long>>() // For each node v: map of color -> sum of costs of edges to that color
var s = 0L // Total current cost of all edges

fun dfs(v : Int) {
    for ((u, c) in g[v]) { // Iterate through neighbors
        if (u != p[v]) { // Skip parent node
            if (a[u] != a[v]) s += c // If colors differ, add cost to total
            m[v][a[u]] = m[v].getOrDefault(a[u], 0L) + c // Update edge contribution map
            p[u] = v // Set current node as parent
            pc[u] = c // Store edge weight from parent
            dfs(u) // Recurse on neighbor
        }
    }
}

fun main() {
    repeat(readln().toInt()) {
        val (n, q) = readln().split(' ').map {it.toInt()}
        a = readln().split(' ').map {it.toInt()}.toMutableList()
        g = Array(n) {mutableListOf<Pair<Int, Int>>()}
        p = Array(n) {-1}
        pc = Array(n) {0}
        m = Array(n) {hashMapOf<Int, Long>()}
        s = 0L
        repeat(n - 1) {
            var (u, v, c) = readln().split(' ').map {it.toInt()}
            --u
            --v
            g[u].add(v to c)
            g[v].add(u to c)
        }
        dfs(0) // Start DFS from root
        repeat(q) {
            var (v, x) = readln().split(' ').map {it.toInt()}
            --v
            s += m[v].getOrDefault(a[v], 0L) // Add contribution of old color
            if (p[v] != -1) { // If not root
                if (a[p[v]] == a[v]) s += pc[v] // Cost from parent to this node if colors match
                m[p[v]][a[v]] = m[p[v]].getOrDefault(a[v], 0L) - pc[v].toLong() // Remove edge cost
            }
            a[v] = x // Update color of vertex v
            s -= m[v].getOrDefault(a[v], 0L) // Subtract new contribution
            if (p[v] != -1) { // If not root
                if (a[p[v]] == a[v]) s -= pc[v] // Subtract edge cost if colors match
                m[p[v]][a[v]] = m[p[v]].getOrDefault(a[v], 0L) + pc[v].toLong() // Add new edge cost
            }
            println(s)
        }
    }
}


// https://github.com/VaHiX/CodeForces/