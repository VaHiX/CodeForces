// Problem: CF 1999 C - Showering
// https://codeforces.com/contest/1999/problem/C

/**
 * Problem: C. Showering
 *
 * Purpose: Determine if Alex can shower for 's' minutes within a day of 'm' minutes,
 *          given 'n' non-overlapping tasks that block certain time intervals.
 *
 * Algorithm:
 * - Iterate through all tasks and check for free time gaps between consecutive tasks.
 * - Also check for free time from the end of the last task to the end of the day.
 * - If any such gap has length >= s, Alex can shower.
 *
 * Time Complexity: O(n) - Linear scan of tasks
 * Space Complexity: O(1) - Only using a few variables
 */

fun main() {
    val t = readLine()!!.toInt()
    for (test in 1..t) {
        val (n, s, m) = readLine()!!.split(' ').map { it.toInt() }
        var can = false
        var previousEnd = 0
        for (i in 1..n) {
            val (start, end) = readLine()!!.split(' ').map { it.toInt() }
            // Check if there's enough free time between previous task and current task
            if (start - previousEnd >= s)
                can = true
            previousEnd = end
        }
        // Check if there's enough free time from the end of last task to the end of the day
        if (m - previousEnd >= s)
            can = true
        if (can)
            print("YES\n")
        else
            print("NO\n")
    }
}


// https://github.com/VaHiX/CodeForces/