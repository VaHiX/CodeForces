// Problem: CF 2131 A - Lever
// https://codeforces.com/contest/2131/problem/A

/*
 * Problem: The Lever Iteration
 * Purpose: Calculate the number of iterations needed for array 'a' to reach a state where all elements 
 *          are greater than or equal to corresponding elements in array 'b', under specific rules:
 *          - Decrease an element in 'a' if it's greater than the corresponding element in 'b'
 *          - Increase an element in 'a' if it's smaller than the corresponding element in 'b'
 *          - Stop iteration when no more decreases are possible.
 *
 * Algorithm/Techniques:
 *   Greedy approach: For each position, we compute how much we need to "make up" for a[i] < b[i].
 *   The sum of such differences represents the number of increments needed.
 *   Each increment/decrement operation reduces one gap and creates another (or closes a gap).
 *   So total operations = sum of deficits = sum(max(0, a[i] - b[i])) for all i
 *
 * Time Complexity: O(n) per test case, since we iterate through the array once.
 * Space Complexity: O(n) for storing input arrays.
 */

import java.util.StringTokenizer

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read length of arrays
        val a = readLine()!!.split(" ").map { it.toInt() } // Read array 'a'
        val b = readLine()!!.split(" ").map { it.toInt() } // Read array 'b'
        var sum = 0 // Initialize sum to count the number of operations needed
        for (i in 0 until n) {
            if (a[i] > b[i]) sum += a[i] - b[i] // Accumulate deficit where a[i] > b[i]
        }
        println(sum + 1) // Add one because final iteration ends when no more decreases are made
    }
}


// https://github.com/VaHiX/codeForces/