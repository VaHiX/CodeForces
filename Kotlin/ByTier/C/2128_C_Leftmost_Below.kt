// Problem: CF 2128 C - Leftmost Below
// https://codeforces.com/contest/2128/problem/C

/**
 * Problem: C. Leftmost Below
 *
 * Purpose:
 *   Determine if a target array `b` can be achieved through a series of operations.
 *   Each operation chooses a value x > min(a), finds the leftmost index i such that a[i] < x,
 *   then increments a[i] by x.
 *
 * Algorithm:
 *   - Traverse the array from left to right.
 *   - Keep track of the minimum value seen so far (`min`) and the new minimum (`newMin`).
 *   - For each element b[i]:
 *     - If b[i] <= min, continue (no need to check further constraints).
 *     - Otherwise:
 *       - Compute half = b[i] / 2 + 1.
 *       - If half <= min, it's impossible to satisfy the condition for this step → return "NO".
 *   - If all elements pass, return "YES".
 *
 * Time Complexity: O(n) per test case.
 * Space Complexity: O(n) due to input array storage.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.io.StreamTokenizer
import java.util.*
import kotlin.math.min

private val sc = Scanner( System.`in` )
private val br = BufferedReader( InputStreamReader( System.`in` ) )
private val st = StreamTokenizer( br )
private val pw = PrintWriter( System.out )

fun main() {
    solve()
    pw.close()
}

private fun solve() {
    val tn = st.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}

private fun solveTest() {
    val n = st.nextInt()
    val b = IntArray( n ) { st.nextInt() }
    var min = 2E9.toInt() // Initialize to a large value
    var newMin = min // Tracks the current minimum in the processed part of array
    for ( i in b.indices ) {
        min = newMin // Update min with the previous newMin before updating newMin
        newMin = min( newMin, b[i] ) // New minimum after processing current element
        if ( b[i] <= min ) continue // If current element is smaller or equal to min, skip checks
        val half = b[i] / 2 + 1 // Compute half of current value plus one
        if ( half <= min ) continue // If half is less than or equal to min, impossible to proceed
        pw.println( "NO" )
        return // Early exit if constraint fails
    }
    pw.println( "YES" )
}

private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/