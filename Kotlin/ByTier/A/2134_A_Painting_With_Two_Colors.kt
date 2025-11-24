// Problem: CF 2134 A - Painting With Two Colors
// https://codeforces.com/contest/2134/problem/A

/**
 * Problem: Painting With Two Colors
 * 
 * Task: Determine if there exists a way to paint two consecutive segments of lengths `a` and `b`
 *       such that the final coloring is symmetric.
 *       
 * Algorithm:
 *   - Check parity conditions between `n`, `a`, and `b`.
 *   - If `n` and `b` have different parities, it's impossible to achieve symmetry.
 *   - If `a > b` and `a` and `n` have different parities, also impossible.
 *   
 * Time Complexity: O(1)
 * Space Complexity: O(1)
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
    val a = st.nextInt()
    val b = st.nextInt()
    // If n and b have different parity, it's impossible to achieve symmetric coloring
    if ( n % 2 != b % 2 ) {
        pw.println( "NO" )
        return
    }
    // If a > b and a and n have different parity, also impossible
    if ( a > b && a % 2 != n % 2 ) {
        pw.println( "NO" )
        return
    }
    pw.println( "YES" )
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/