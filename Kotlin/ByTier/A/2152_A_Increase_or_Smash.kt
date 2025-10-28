// Problem: CF 2152 A - Increase or Smash
// https://codeforces.com/contest/2152/problem/A

/*
 * Problem: A. Increase or Smash
 * Purpose: Find the minimum number of operations (Increase and Smash) to transform an array of zeros into a target array.
 * Algorithms/Techniques:
 *   - Greedy approach based on distinct elements in the array.
 *   - For each unique value in the target array, we simulate an increase operation that raises all elements by that value,
 *     followed by necessary smash operations to zero out specific elements.
 *   - The minimum number of operations is equal to twice the number of distinct elements minus one.
 *
 * Time Complexity: O(n) per test case where n is the size of the array.
 * Space Complexity: O(n) due to storing distinct elements in a set.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val writer = PrintWriter(System.out, false)
    val t = reader.readLine()!!.toInt() // Read number of test cases
    
    repeat(t) {
        val n = reader.readLine()!!.toInt() // Read size of array
        val distinctElements = reader.readLine()!!
            .splitToSequence(' ') // Split input line by space
            .map { it.toInt() } // Convert each element to integer
            .toHashSet() // Collect distinct elements into a set
            .size // Get count of distinct elements
        writer.println(distinctElements.shl(1) - 1) // Equivalent to (2 * distinctElements - 1)
    }
    writer.flush() // Flush the output buffer
}


// https://github.com/VaHiX/CodeForces/