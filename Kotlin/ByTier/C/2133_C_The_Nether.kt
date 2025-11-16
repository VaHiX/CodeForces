// Problem: CF 2133 C - The Nether
// https://codeforces.com/contest/2133/problem/C

/*
 * Problem: C. The Nether (Interactive)
 *
 * Purpose:
 *   This code finds the longest path in a directed acyclic graph (DAG) of n nodes,
 *   using at most 2*n queries to an interactive judge.
 *
 * Algorithms:
 *   - First, we query each node as a starting point for paths within the entire graph,
 *     obtaining the maximum path length from that node and identifying a candidate
 *     start node.
 *   - Then, a binary search-like approach is used to determine which adjacent nodes
 *     are part of the longest path, reconstructing it step-by-step.
 *
 * Time Complexity:
 *   O(n^2 * log n) per test case. For each of n nodes, we make one query with up to n vertices.
 *   Reconstructing the path uses binary search which is O(log n) for each step,
 *   and we perform at most n steps, leading to overall complexity of O(n^2 * log n).
 *
 * Space Complexity:
 *   O(n^2) due to storing node lists indexed by length and auxiliary data structures.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer

fun checkJudgeResponse(value: Int) {
    if (value == -1) {
        System.exit(0)
    }
}

fun solve(reader: BufferedReader, out: PrintWriter) {
    val n = reader.readLine().toInt()
    checkJudgeResponse(n)
    val len = IntArray(n + 1) // Stores longest path length from each node
    var maxLen = 0
    var startNode = -1
    
    // Query every node to find the start node of the longest path
    for (i in 1..n) {
        out.print("? $i $n") // Start with full set of nodes
        for (j in 1..n) out.print(" $j")
        out.println()
        out.flush()
        val res = reader.readLine().toInt()
        len[i] = res
        checkJudgeResponse(res)
        if (res > maxLen) {
            maxLen = res
            startNode = i
        }
    }
    
    // Group nodes by their computed path length
    val nodesByLen = Array(n + 1) { mutableListOf<Int>() }
    for (i in 1..n) {
        nodesByLen[len[i]].add(i)
    }
    
    // Reconstruct the path starting with startNode
    val path = mutableListOf<Int>()
    path.add(startNode)
    
    while (path.size < maxLen) {
        val currentNode = path.last()
        val targetLen = len[currentNode] - 1
        if (targetLen <= 0) break
        
        val candidates = nodesByLen[targetLen]
        if (candidates.size == 1) {
            // Only one possible next node, so take it
            path.add(candidates[0])
            continue
        }
        
        // Binary search to determine correct node among candidates
        var low = 0
        var high = candidates.size
        
        while (high - low > 1) {
            val mid = low + (high - low) / 2
            out.print("? ${path[0]} ${path.size + (mid - low)}")
            for (node in path) out.print(" $node")
            for (i in low until mid) out.print(" ${candidates[i]}")
            out.println()
            out.flush()
            val res = reader.readLine().toInt()
            checkJudgeResponse(res)
            
            // Adjust binary search bounds based on judge response
            if (res > path.size) {
                high = mid
            } else {
                low = mid
            }
        }
        // Add the chosen node to the path
        path.add(candidates[low])
    }
    
    // Output the result path
    out.print("! ${path.size}")
    for (node in path) out.print(" $node")
    out.println()
    out.flush()
}

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val out = PrintWriter(System.out, true)
    val t = reader.readLine().toInt()
    checkJudgeResponse(t)
    repeat(t) {
        solve(reader, out)
    }
}


// https://github.com/VaHiX/CodeForces/