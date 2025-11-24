// Problem: CF 2128 B - Deque Process
// https://codeforces.com/contest/2128/problem/B

/**
 * Problem: B. Deque Process
 * Algorithm: Greedy with careful selection of left or right element based on sign of cross products
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the input and output arrays
 *
 * Given a permutation of integers, we must choose to remove elements from either end of the array
 * such that the resulting sequence q is "good", i.e., it does not contain an increasing or decreasing
 * subsequence of length 5.
 *
 * The strategy uses a greedy approach: at each step, we evaluate whether taking from left (l) or right (r)
 * maintains the good property. This decision is made based on signs of cross products of differences.
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
    val p = LongArray( n ) { st.nextInt().toLong() }
    var l = 2
    var r = n - 1
    val q = LongArray( n )
    q[0] = p[0]
    q[1] = p[1]
    pw.print( "LL" ) // First two moves are always left, to start building a potential good sequence
    for ( i in 2 until n ) {
        // Check if moving left maintains the good state based on comparison of cross products
        if ( ( p[l] - q[i - 1] ) * ( q[i - 1] - q[i - 2] ) < 0 ) {
            pw.print( 'L' )
            q[i] = p[l ++]
        } else if ( ( p[r] - q[i - 1] ) * ( q[i - 1] - q[i - 2] ) < 0 ) {
            pw.print( 'R' )
            q[i] = p[r --]
        } else if ( ( q[i - 1] - q[i - 2] ) * ( p[r] - p[l] ) < 0 ) {
            pw.print( 'L' )
            q[i] = p[l ++]
        } else {
            pw.print( 'R' )
            q[i] = p[r --]
        }
    }
    pw.println()
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/