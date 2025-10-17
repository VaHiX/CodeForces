// Problem: CF 2110 E - Melody
// https://codeforces.com/contest/2110/problem/E

/**
 * E. Melody
 *
 * Problem Description:
 * Given n sounds characterized by volume (v) and pitch (p), construct a sequence
 * such that:
 * 1. Any two consecutive sounds differ in either volume or pitch only (beautiful).
 * 2. No three consecutive sounds have the same volume or same pitch (non-boring).
 * 3. Each sound is used exactly once.
 *
 * Algorithm:
 * - This is essentially finding an Eulerian path in a graph where nodes are volumes and pitches,
 *   edges represent sounds connecting volume and pitch nodes.
 * - Build a bipartite graph with volumes on one side, pitches on the other.
 * - Use DSU (Disjoint Set Union) to ensure all components are connected.
 * - Apply Hierholzer's algorithm to find Eulerian path.
 *
 * Time Complexity: O(n * α(n)) where α is inverse Ackermann function (n for DSU operations)
 * Space Complexity: O(n) for DSU, adjacency lists, etc.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import java.util.ArrayDeque
import java.util.ArrayList
import java.util.HashMap

private class DSU(n: Int) {
    private val p = IntArray(n) { it }  // Parent array for DSU
    private val r = IntArray(n)         // Rank array for DSU
    fun find(x: Int): Int {
        if (p[x] != x) p[x] = find(p[x])  // Path compression
        return p[x]
    }
    fun unite(a0: Int, b0: Int) {
        var a = find(a0)
        var b = find(b0)
        if (a == b) return
        if (r[a] < r[b]) a = b.also { b = a }  // Union by rank
        p[b] = a
        if (r[a] == r[b]) r[a]++
    }
}

private data class Edge(val to: Int, val id: Int)  // Edge representation: destination node and sound ID

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val out = StringBuilder()
    val t = br.readLine().trim().toInt()
    repeat(t) {
        val n = br.readLine().trim().toInt()
        val vols = LongArray(n + 1)   // Volume array
        val pits = LongArray(n + 1)   // Pitch array
        for (i in 1..n) {
            val st = StringTokenizer(br.readLine())
            vols[i] = st.nextToken().toLong()
            pits[i] = st.nextToken().toLong()
        }
        val mapV = HashMap<Long, Int>()  // Map volume to index
        val mapP = HashMap<Long, Int>()  // Map pitch to index
        var vCnt = 0
        var pCnt = 0
        for (i in 1..n) {
            mapV.computeIfAbsent(vols[i]) { vCnt++ }   // Assign unique ID to each volume
            mapP.computeIfAbsent(pits[i]) { pCnt++ }   // Assign unique ID to each pitch
        }
        val totVert = vCnt + pCnt       // Total number of unique volumes and pitches
        val adj = Array(totVert) { ArrayList<Edge>() }  // Adjacency list for bipartite graph
        val deg = IntArray(totVert)   // Degree array
        val dsu = DSU(totVert)        // DSU for connectivity check
        for (idx in 1..n) {
            val vId = mapV[vols[idx]]!!     // Get volume node ID
            val pId = vCnt + mapP[pits[idx]]!!   // Get pitch node ID (shifted by vCnt)
            adj[vId].add(Edge(pId, idx))    // Add edge from volume to pitch
            adj[pId].add(Edge(vId, idx))    // Add edge from pitch to volume
            deg[vId]++                       // Increment degree of volume node
            deg[pId]++                       // Increment degree of pitch node
            dsu.unite(vId, pId)              // Connect volume and pitch in DSU
        }
        var comp = -1
        var ok = true
        var oddCnt = 0
        for (v in 0 until totVert) if (deg[v] > 0) {
            if (comp == -1) comp = dsu.find(v) else if (dsu.find(v) != comp) ok = false  // Check all nodes are in one component
            if (deg[v] and 1 == 1) oddCnt++   // Count vertices with odd degree
        }
        if (!ok || !(oddCnt == 0 || oddCnt == 2)) {
            out.append("NO\n")
            return@repeat
        }
        var start = 0
        if (oddCnt == 2) {
            for (v in 0 until totVert) if (deg[v] and 1 == 1) { start = v; break } // Start at a vertex with odd degree
        } else {
            for (v in 0 until totVert) if (deg[v] > 0) { start = v; break }         // Start at any non-zero degree vertex
        }
        val usedEdge = BooleanArray(n + 1)    // Track used edges to avoid duplicates
        val ptr = IntArray(totVert)           // Pointer for current edge in adjacency list
        val stk: ArrayDeque<Pair<Int, Int>> = ArrayDeque()     // Stack for DFS traversal (vertex, incoming edge index)
        val res = IntArray(n)                 // Result array storing indices of sounds
        var resSz = 0
        stk.addLast(Pair(start, -1))
        while (!stk.isEmpty()) {
            val (v, inEdge) = stk.peekLast()
            var p = ptr[v]
            while (p < adj[v].size && usedEdge[adj[v][p].id]) p++   // Skip already used edges
            ptr[v] = p
            if (p == adj[v].size) {
                stk.removeLast()
                if (inEdge != -1) res[resSz++] = inEdge  // Record the edge when backtracking
            } else {
                val e = adj[v][p]
                usedEdge[e.id] = true
                ptr[v]++
                stk.addLast(Pair(e.to, e.id))   // Move to next vertex
            }
        }
        if (resSz != n) {             // If not all edges were covered, no Eulerian path exists
            out.append("NO\n")
            return@repeat
        }
        out.append("YES\n")
        for (i in n - 1 downTo 0) {
            out.append(res[i]).append(' ')
        }
        out.append('\n')
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/