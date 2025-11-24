// Problem: CF 2111 A - Energy Crystals
// https://codeforces.com/contest/2111/problem/A

/**
 * Problem: A. Energy Crystals
 *
 * Purpose:
 *   Given a target energy level x, compute the minimum number of actions required to charge
 *   three crystals to exactly level x, under the constraint that after each action,
 *   for any two crystals i and j, it must hold that a_i >= floor(a_j / 2).
 *
 * Algorithm:
 *   The solution observes that the optimal charging pattern follows a recurrence relation.
 *   It computes log2(x) and uses the formula: 2 * floor(log2(x)) + 3.
 *   This formula is derived based on the structure of the constraints and optimal strategy.
 *
 * Time Complexity:
 *   O(1) per test case, since we perform constant-time operations (log2, floor, arithmetic).
 *
 * Space Complexity:
 *   O(1), no additional space used except for variables.
 */

import kotlin.math.floor
import kotlin.math.log2

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val x = readLine()!!.toInt()
        if (x == 0) {
            println(0)
            return@repeat
        }
        val log2x = floor(log2(x.toDouble())).toInt() // Compute floor of log base 2 of x
        println(2 * log2x + 3) // Apply derived formula to get minimum actions
    }
}


// https://github.com/VaHiX/CodeForces/