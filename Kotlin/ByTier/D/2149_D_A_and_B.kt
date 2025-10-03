// Problem: CF 2149 D - A and B
// https://codeforces.com/contest/2149/problem/D

/*
 * Problem: D. A and B
 * Purpose: Find minimum number of adjacent swaps to make all 'a's or all 'b's form a single continuous block.
 *
 * Algorithm:
 * - For each test case, find positions of 'a' and 'b'.
 * - Compute the cost of making all 'a's or all 'b's form a block by minimizing total Manhattan distances,
 *   which is equivalent to moving elements to median position in sorted array (optimal for sum of distances).
 * - This uses the idea that for minimizing sum of absolute differences, we should move to median.
 *
 * Time Complexity: O(n) per test case, where n is length of string.
 * Space Complexity: O(n), due to storage of positions of 'a' and 'b'.
 */

import kotlin.math.abs
import kotlin.math.min

fun computeCost(positions: IntArray): Long {
    val m = positions.size
    if (m <= 1) return 0L // If only one element, no moves needed
    
    // Transform positions to relative coordinates by subtracting index
    val vals = LongArray(m)
    for (i in 0 until m) vals[i] = positions[i].toLong() - i.toLong()
    
    // Find median of the transformed array (key idea: minimize sum of distances)
    val med = vals[m / 2]
    
    // Compute total cost to move all elements to median
    var cost = 0L
    for (i in 0 until m) cost += abs(vals[i] - med)
    return cost
}

fun main() {
    val data = java.io.BufferedInputStream(System.`in`).readBytes()
    val tokens = String(data).trim().split(Regex("\\s+"))
    var idx = 0
    val t = tokens[idx++].toInt()
    val sb = StringBuilder()
    repeat(t) {
        val n = tokens[idx++].toInt()
        val s = tokens[idx++]
        
        // Collect positions of 'a' and 'b'
        val posA = mutableListOf<Int>()
        val posB = mutableListOf<Int>()
        for (i in s.indices) {
            if (s[i] == 'a') posA.add(i) else posB.add(i)
        }
        
        val arrA = posA.toIntArray()
        val arrB = posB.toIntArray()
        
        // Take minimum cost of making either all 'a's or all 'b's form a block
        val ans = min(computeCost(arrA), computeCost(arrB))
        sb.append(ans).append('\n')
    }
    print(sb.toString())
}


// https://github.com/VaHiX/CodeForces/