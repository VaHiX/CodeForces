// Problem: CF 2118 A - Equal Subsequences
// https://codeforces.com/contest/2118/problem/A

/*
 * Problem: Equal Subsequences
 * Algorithm/Technique: Greedy Construction
 *
 * Purpose:
 *   Construct a bitstring of length n with exactly k '1's such that the number of 
 *   "101" and "010" subsequences are equal.
 *
 * Approach:
 *   - Place all k ones at the beginning, followed by zeros.
 *   - This ensures that any "101" subsequence must have a '1' on the left and '0' in the middle,
 *     and any "010" subsequence must have a '0' on the left and '1' in the middle.
 *   - Since we only have one group of 1s followed by a group of 0s, the number of 
 *     distinct "101" and "010" subsequences is equal (or zero if k=0 or k=n).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for output string
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.io.StreamTokenizer
import java.util.*
private val sc = Scanner( System.`in` )
private val br = BufferedReader( InputStreamReader( System.`in` ) )
private val st = StreamTokenizer( br )
private val pw = PrintWriter( System.out )
fun main() {
    solve()
    pw.close()
}
private fun solve() {
    val tn = st.nextInt() // Read number of test cases
    for ( test in 1 .. tn ) {
        solveTest() // Solve each test case
    }
}
private fun solveTest() {
    val n = st.nextInt() // Length of the bitstring
    val k = st.nextInt() // Number of ones in the bitstring
    for ( i in 1 .. k ) pw.print( '1' ) // Print k ones first
    for ( i in k + 1 .. n ) pw.print( '0' ) // Then print remaining zeros
    pw.println() // New line after each test case
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/