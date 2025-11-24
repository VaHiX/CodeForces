// Problem: CF 2134 B - Add 0 or K
// https://codeforces.com/contest/2134/problem/B

/**
 * Problem: B. Add 0 or K
 * 
 * Purpose:
 *   Given an array of positive integers and a value k, we can add either 0 or k to each element
 *   at most k times. The goal is to make the GCD of the resulting array greater than 1.
 * 
 * Algorithm:
 *   - For each element in the array, compute how much we need to add so that the final value
 *     is divisible by some number > 1 (typically 2 or a small prime).
 *   - If k == 1: We can make each element even by adding 0 or 1, so use `a[i] + (a[i] % 2)`.
 *   - Otherwise: Use modular arithmetic to determine minimal additions needed modulo (k+1),
 *     then add k * (addition needed).
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
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
    val tn = st.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}
private fun solveTest() {
    val n = st.nextInt()
    val k = st.nextInt().toLong()
    val a = LongArray( n ) { st.nextInt().toLong() }
    if ( k == 1L ) {
        // When k=1, we can only add 0 or 1. Make each element even.
        pw.println( a.map { it + it % 2 }.joinToString( " " ) )
    } else {
        // For general k, use modulo arithmetic to find minimal additions for divisibility.
        pw.println( a.map { it + ( it % ( k + 1 ) ) * k }.joinToString( " " ) )
    }
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/