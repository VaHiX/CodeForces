// Problem: CF 2143 A - All Lengths Subtraction
// https://codeforces.com/contest/2143/problem/A

/**
 * Problem: Determine if a permutation can be reduced to all zeros by performing operations on subarrays of increasing lengths.
 *
 * Algorithm:
 * For each k from n down to 1:
 *   - Find all indices where value k appears.
 *   - Check if the range [minIdx, maxIdx] is too large for any valid subarray of size k => impossible.
 *   - Try to find a valid subarray of length k such that all its elements are positive.
 *     - Subtract 1 from that subarray.
 *     - If no such subarray exists, return "NO".
 *   - Continue until all operations done.
 *
 * Time Complexity: O(n^3) in worst case due to nested loops and array manipulations.
 * Space Complexity: O(n) for storing the permutation and auxiliary data structures.
 */

import java.io.BufferedReader
import java.io.InputStreamReader

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val testCases = reader.readLine().toInt()
    repeat(testCases) {
        solve(reader)
    }
}

fun solve(reader: BufferedReader) {
    val n = reader.readLine().toInt()
    val p = reader.readLine().split(" ").map { it.toInt() }.toMutableList()

    // Process each k from n down to 1
    for (k in n downTo 1) {
        // Find all indices where value k occurs
        val kIndices = p.withIndex()
            .filter { it.value == k }
            .map { it.index }
        val minIdx = kIndices.firstOrNull() ?: -1
        val maxIdx = kIndices.lastOrNull() ?: -1

        // If the range of k's positions is larger than k itself, impossible to satisfy
        if (minIdx != -1 && maxIdx - minIdx + 1 > k) {
            println("NO")
            return
        }

        var operationPerformed = false
        // Try all possible subarrays of length k
        for (start in 0..n - k) {
            val end = start + k - 1

            // Skip if this window doesn't include minIdx or maxIdx
            if (minIdx != -1 && (start > minIdx || end < maxIdx)) {
                continue
            }

            var allPositive = true
            // Check if every element in the subarray is positive
            for (i in start..end) {
                if (p[i] <= 0) {
                    allPositive = false
                    break
                }
            }

            if (allPositive) {
                // Subtract 1 from each element in this subarray
                for (i in start..end) {
                    p[i]--
                }
                operationPerformed = true
                break
            }
        }

        if (!operationPerformed) {
            println("NO")
            return
        }
    }
    println("YES")
}


// https://github.com/VaHiX/codeForces/