// Problem: CF 2130 C - Double Perspective
// https://codeforces.com/contest/2130/problem/C

/**
 * Problem: C. Double Perspective
 *
 * Purpose:
 *   This code solves a problem where we need to select a subset of segments such that
 *   the difference between the total length of their union (f(S)) and the number of nodes 
 *   participating in cycles of length at least 3 (g(S)) is maximized.
 *
 * Algorithm:
 *   - For each test case, we process n segments represented as (a_i, b_i).
 *   - We use a greedy approach by sorting segments in descending order of their lengths.
 *   - A Disjoint Set Union (DSU) data structure is used to manage connectivity,
 *     and keep track of nodes that form simple cycles with 3 or more edges.
 *   - For each segment, if adding it does not create a cycle (via DSU), we add it to the result set.
 *   - This greedy approach works because longer segments contribute more to f(S) than g(S).
 *   - The DSU also helps to detect whether two nodes are connected; if they are,
 *     adding an edge between them creates a cycle.
 *
 * Time Complexity:
 *   - Sorting: O(n log n)
 *   - DSU operations: nearly O(1) amortized per operation
 *   - Overall time complexity: O(n log n) per test case
 *
 * Space Complexity:
 *   - O(n) for storing segments, DSU arrays, and output list
 */

import java.io.*
import java.util.*

private val inputReader = BufferedReader(InputStreamReader(System.`in`))
private val outWriter = PrintWriter(System.out)
private var tokenizer: StringTokenizer? = null

private fun fetchInt(): Int {
    while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
        tokenizer = StringTokenizer(inputReader.readLine())
    }
    return tokenizer!!.nextToken().toInt()
}

/**
 * Disjoint Union data structure to manage connected components and detect cycles
 */
private class DisjointUnion(size: Int) {
    private val ancestor = IntArray(size + 15) { it } // Parent array for DSU
    private val level = IntArray(size + 15) { 0 }     // Rank for union by rank optimization
    
    /**
     * Unites two nodes x and y.
     * Returns true if they were not already in the same component.
     */
    fun unite(x: Int, y: Int): Boolean {
        val px = trace(x)  // Find root of x
        val py = trace(y)  // Find root of y
        
        if (px == py) return false // Already connected, forming a cycle

        // Union by rank optimization
        if (level[px] > level[py]) {
            ancestor[py] = px
        } else if (level[px] < level[py]) {
            ancestor[px] = py
        } else {
            ancestor[py] = px
            level[px]++
        }
        return true
    }

    /**
     * Find root of x with path compression
     */
    private fun trace(x: Int): Int {
        if (ancestor[x] != x) ancestor[x] = trace(ancestor[x])
        return ancestor[x]
    }
}

/**
 * Data class representing a segment with length, endpoints, and index
 */
private data class Segment(
    val len: Int,
    val u: Int,
    val v: Int,
    val tag: Int
)

private fun processScenario() {
    val n = fetchInt()
    val segments = ArrayList<Segment>()
    
    // Read segments
    repeat(n) { idx ->
        val p = fetchInt()
        val q = fetchInt()
        segments.add(Segment(q - p, p, q, idx + 1))
    }
    
    // Sort by length descending (greedy choice)
    segments.sortByDescending { it.len }
    
    val mergeTool = DisjointUnion(n * 2 + 100) // DSU for connectivity tracking
    val outputTags = mutableListOf<Int>()      // Indices of selected segments
    
    // Greedily select segments to maximize f(S) - g(S)
    for (s in segments) {
        if (mergeTool.unite(s.u, s.v)) {  // If adding segment doesn't form a cycle
            outputTags.add(s.tag)         // Add to result set
        }
    }
    
    outWriter.println(outputTags.size)
    for (t in outputTags) outWriter.print("$t ")
    outWriter.println()
}

fun main() {
    val rounds = fetchInt()
    repeat(rounds) {
        processScenario()
    }
    outWriter.flush()
}


// https://github.com/VaHiX/CodeForces/