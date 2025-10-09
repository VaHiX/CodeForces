// Problem: CF 2112 A - Race
// https://codeforces.com/contest/2112/problem/A

/*
 * Problem: Race
 * 
 * Purpose: Determine if Bob can choose a starting position such that he will always reach the prize faster
 *          than Alice, regardless of where the prize drops (at either x or y).
 * 
 * Algorithms/Techniques:
 *   - Range analysis and interval overlapping
 *   - Brute-force search in overlapping intervals
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * Input Format:
 *   - t test cases
 *   - For each test case: a, x, y (Alice's start, prize positions)
 * 
 * Output Format:
 *   - "YES" if Bob can guarantee faster arrival regardless of prize drop, otherwise "NO"
 */

fun main() {
    val T = readln().toInt()
    repeat(T) {
        val (a, b, c) = readln().split(" ").map { it.toInt() } // a: Alice's position, b, c: possible prize positions
        val d1 = kotlin.math.abs(a - b) // Distance from Alice to prize at b
        val d2 = kotlin.math.abs(a - c) // Distance from Alice to prize at c
        
        // Compute the range of Bob's potential starting points where he can beat Alice in both cases
        val left = maxOf(minOf(b, b) - d1 + 1, minOf(c, c) - d2 + 1) // Left boundary of search interval
        val right = minOf(maxOf(b, b) + d1 - 1, maxOf(c, c) + d2 - 1) // Right boundary of search interval
        
        var found = false // Flag to indicate if valid Bob position exists
        
        // Search in the computed interval for a valid starting point for Bob
        for (x in left..right) {
            if (x != a && kotlin.math.abs(x - b) < d1 && kotlin.math.abs(x - c) < d2) {
                found = true
                break // Found a valid position, no need to check further
            }
        }
        
        println(if (found) "YES" else "NO")
    }
}


// https://github.com/VaHiX/CodeForces/