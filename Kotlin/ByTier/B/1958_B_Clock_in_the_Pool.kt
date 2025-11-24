// Problem: CF 1958 B - Clock in the Pool
// https://codeforces.com/contest/1958/problem/B

/**
 * Problem: B. Clock in the Pool
 *
 * Purpose:
 *   Given a cyclic clock that shows water temperature, air temperature, and time in a repeating pattern
 *   of 3k seconds per cycle, determine how long to wait from moment m until the clock shows time.
 *
 * Algorithm:
 *   - The clock shows time during seconds [2k, 3k - 1] of each 3k-second cycle.
 *   - Find the next time-showing period after second m.
 *   - Calculate the difference between m and the start of that period.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
fun main() {
    val testCases = readLine()!!.toInt() // Read number of test cases
    repeat(testCases) {
        val (k, m) = readLine()!!.split(" ").map { it.toInt() } // Read k and m for current test case
        
        // Calculate the wait time:
        // - m % (3 * k) gives the position within the current 3k-second cycle
        // - If the position is in [0, 2k-1], then we're in a non-time period
        // - Else, if in [2k, 3k-1], then we're already at time or in time period
        // - The formula: maxOf(0, 2 * k - m % (3 * k)) computes wait until the next time display
        val waitTime = maxOf(0, 2 * k - m % (3 * k))
        println(waitTime)
    }
}


// https://github.com/VaHiX/codeForces/