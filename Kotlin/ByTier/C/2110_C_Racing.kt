// Problem: CF 2110 C - Racing
// https://codeforces.com/contest/2110/problem/C

/*
 * C. Racing
 *
 * Problem Description:
 * A drone must fly through a course with n obstacles. Each obstacle has a height range [l_i, r_i].
 * The drone's height changes according to a program d_1, d_2, ..., d_n where d_i = h_i - h_{i-1}.
 * Values are restricted to 0 or 1, and some values may be unknown (-1).
 * Replace unknowns with 0 or 1 such that all heights fall within the obstacle ranges.
 *
 * Algorithm:
 * - For each position, compute the valid range of possible heights after applying d_i.
 * - Use dynamic programming approach for lower and upper bounds.
 * - Backtrack from the end to assign values based on bounds.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing arrays and bounds
 */

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val cases = scanner.nextInt()
    repeat(cases) {
        val n = scanner.nextInt()
        val input = IntArray(n + 1)   // Stores the d array with index 1 to n
        val lower = IntArray(n + 1)   // Lower bound of possible height at each obstacle
        val upper = IntArray(n + 1)   // Upper bound of possible height at each obstacle
        for (i in 1..n) input[i] = scanner.nextInt()
        for (i in 1..n) {
            lower[i] = scanner.nextInt()
            upper[i] = scanner.nextInt()
        }
        val bounds = Array(n + 1) { IntArray(2) } // Stores [min, max] range of height at each step
        var valid = true
        for (i in 1..n) {
            val minPrev = bounds[i - 1][0]
            val maxPrev = bounds[i - 1][1]
            val (nextMin, nextMax) = when (input[i]) {
                0 -> minPrev to maxPrev                   // No change in height
                1 -> (minPrev + 1) to (maxPrev + 1)       // Drone rises by 1
                else -> minPrev to (maxPrev + 1)          // Unknown: can rise or stay same
            }
            val updatedMin = maxOf(lower[i], nextMin)
            val updatedMax = minOf(upper[i], nextMax)
            if (updatedMin > updatedMax) {                // No valid range exists
                valid = false
                break
            }
            bounds[i][0] = updatedMin
            bounds[i][1] = updatedMax
        }
        if (!valid) {
            println("-1")
            return@repeat
        }
        val result = IntArray(n + 1)
        var current = bounds[n][0]
        for (i in n downTo 1) {
            if (input[i] != -1) {
                result[i] = input[i]
                current -= input[i]                   // Adjust for known value
            } else {
                result[i] = if (current in bounds[i - 1][0]..bounds[i - 1][1]) {
                    0                                 // Assign 0 if still within bounds
                } else {
                    current -= 1                      // Otherwise assign 1, updating current
                    1
                }
            }
        }
        println(result.slice(1..n).joinToString(" "))
    }
}


// https://github.com/VaHiX/CodeForces/