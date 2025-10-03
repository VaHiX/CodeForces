// Problem: CF 2119 B - Line Segments
// https://codeforces.com/contest/2119/problem/B

/**
 * Problem: Line Segments
 * 
 * Task: Determine if it's possible to reach a terminal point (qx, qy) from a starting point (px, py)
 *       by performing n moves, where each move has a specific distance 'a[i]' to travel.
 * 
 * Algorithm:
 *  - Calculate squared Euclidean distance between start and end points.
 *  - Compute sum of all distances and maximum single move.
 *  - Use geometric constraints:
 *    1. If the squared distance between start and end is greater than square of total sum,
 *       then impossible (too far).
 *    2. If twice the max distance is >= sum and (2*max - sum)^2 > squared_dist, 
 *       then impossible (can't "loop back" enough to reach target).
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing array 'a'
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
    val d2 = run {
        val x1 = st.nextInt().toLong()
        val y1 = st.nextInt().toLong()
        val x2 = st.nextInt().toLong()
        val y2 = st.nextInt().toLong()
        return@run ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) // squared distance between start and end
    }
    val a = LongArray( n ) { st.nextInt().toLong()} // array of distances to move in each operation
    val sum = a.sum() // total distance that can be traveled
    val max = a.max() // maximum single move distance
    if ( d2 > sum * sum ) {
        pw.println( "No" ) // impossible since we can't cover the distance even with all moves
    } else if ( 2 * max >= sum && ( 2 * max - sum ) * ( 2 * max - sum ) > d2 ) {
        pw.println( "No" ) // impossible due to triangle inequality constraint
    } else {
        pw.println( "Yes" )
    }
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/