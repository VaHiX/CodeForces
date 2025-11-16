// Problem: CF 2128 A - Recycling Center
// https://codeforces.com/contest/2128/problem/A

/**
 * Problem: Recycling Center
 * 
 * Description:
 * We have n trash bags with weights a[i]. Each second, we choose one bag to destroy:
 * - If weight > c, it costs 1 coin.
 * - After destruction, all remaining bags double in weight.
 * Goal: Minimize total coins spent to destroy all bags.
 * 
 * Algorithm:
 * Greedy strategy with binary search on answer.
 * Sort the array. For a given number of bags (m) that we will destroy,
 * check if it's possible to destroy them using the greedy method:
 * - Always destroy the heaviest available bag (greedy choice).
 * - If the weight of current bag is <= c, no coin is paid.
 * 
 * Time Complexity: O(n log n + T * n * log n), where T = number of test cases
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
    val c = st.nextInt()
    val a = LongArray( n ) { st.nextInt().toLong() }
    a.sort()
    var l = 0
    var r = n
    while ( l < r ) {
        val m = ( l + r + 1 ) / 2 // Binary search on number of bags to destroy
        var ok = true
        for ( i in 0 until m ) {
            // Destroy the heaviest bag among the remaining ones (greedy)
            if ( a[m - i - 1] shl i > c ) { // Check if cost is > c (shl i means multiply by 2^i)
                ok = false
                break
            }
        }
        if ( ok ) {
            l = m // Can destroy m bags, try to increase
        } else {
            r = m - 1 // Cannot destroy m bags, decrease
        }
    }
    pw.println( n - l ) // Remaining bags that don't get destroyed = n - l
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/