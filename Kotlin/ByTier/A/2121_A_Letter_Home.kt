// Problem: CF 2121 A - Letter Home
// https://codeforces.com/contest/2121/problem/A

/*
 * Problem: A. Letter Home
 * Algorithms/Techniques: Greedy, Two Pointers
 * 
 * Time Complexity: O(n) per test case, where n is the number of positions to visit.
 * Space Complexity: O(n) due to storing the array of positions.
 *
 * The problem asks to find the minimum number of steps to visit all given positions
 * starting from a specific position 's', moving only one step at a time either left or right.
 * 
 * Approach:
 * - If n == 1, we just need to move from s to x[0].
 * - Otherwise, the optimal strategy involves going from the start position s to either 
 *   the leftmost (x[0]) or rightmost (x[n-1]) point and then traveling the full range [x[0], x[n-1]].
 * - The total steps is: distance to closest end + range of the interval.
 */

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val (n, s) = readLine()!!.split(" ").map { it.toInt() }
        val x = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
        
        if (n == 1) {
            // Only one position to visit; just move from s to that position
            println(Math.abs(s - x[0]))
            return@repeat
        }
        
        // Calculate the range of positions (difference between max and min)
        val range = x[n - 1] - x[0]
        
        // Distance from start 's' to leftmost and rightmost points
        val distToMin = Math.abs(s - x[0])
        val distToMax = Math.abs(s - x[n - 1])
        
        // Minimum steps is the range plus the shorter of the two distances to ends
        val steps = range + minOf(distToMin, distToMax)
        println(steps)
    }
}


// https://github.com/VaHiX/CodeForces/