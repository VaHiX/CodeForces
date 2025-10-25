// Problem: CF 2136 C - Against the Difference
// https://codeforces.com/contest/2136/problem/C

/*
 * Problem: C. Against the Difference
 * Purpose: Find the length of the longest "neat" subsequence in an array.
 *          A "neat" subsequence is one that can be split into blocks,
 *          where each block has all elements equal to its length.
 * 
 * Algorithms/Techniques:
 * - Dynamic Programming with Segment Tree-like processing
 * - Preprocessing positions of values
 * - For each value, for all valid lengths (as block sizes), connect left and right indices
 * - DP is used to track best ending at each position and best so far
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops over positions
 * Space Complexity: O(n^2) due to storing edges for all possible block lengths
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val t = reader.readLine().trim().toInt()
    val out = StringBuilder()
    repeat(t) {
        val n = reader.readLine().trim().toInt()
        val st = StringTokenizer(reader.readLine())
        val arr = IntArray(n + 1)
        for (i in 1..n) {
            arr[i] = st.nextToken().toInt()
        }
        // Store positions of each value
        val positions = Array(n + 1) { mutableListOf<Int>() }
        for (i in 1..n) {
            val v = arr[i]
            if (v <= n) positions[v].add(i)
        }
        // Build edges between indices based on blocks
        val edges = Array(n + 1) { mutableListOf<Pair<Int, Int>>() }
        for (valNum in 1..n) {
            val idxList = positions[valNum]
            val count = idxList.size
            for (len in valNum..count) {
                val left = idxList[len - valNum] // Left index of the block
                val right = idxList[len - 1]    // Right index of the block
                edges[right].add(left to valNum) // Add edge from left to right with weight equal to block size
            }
        }
        // DP arrays for tracking maximum neat subsequence length
        val dpEnd = IntArray(n + 1)   
        val bestUpTo = IntArray(n + 1) 
        for (i in 1..n) {
            for ((l, w) in edges[i]) {
                dpEnd[i] = max(dpEnd[i], bestUpTo[l - 1] + w)
            }
            bestUpTo[i] = max(bestUpTo[i - 1], dpEnd[i])
        }
        out.append(bestUpTo[n]).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/