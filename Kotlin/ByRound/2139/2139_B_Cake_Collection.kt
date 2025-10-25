// Problem: CF 2139 B - Cake Collection
// https://codeforces.com/contest/2139/problem/B

/*
B. Cake Collection
Algorithms/Techniques: Greedy algorithm with sorting

Time Complexity: O(n log n + n) where n is the number of ovens, due to sorting and a single pass through the array.
Space Complexity: O(1) excluding input storage, as we only use a constant amount of extra space.

Problem:
Maple wants to bake cakes using magical ovens. Each oven i bakes a_i cakes per second.
At the end of each second, she can collect all cakes from any oven.
We need to maximize the total number of cakes collected in m seconds.
Approach:
- Sort ovens by baking rate in descending order.
- For each of the first min(n,m) seconds, collect from the highest-rated oven available.
- The contribution of an oven is a_i * (m - i), since it's used for (m - i) seconds.
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
    val n = st.nextInt() // Number of ovens
    val m = st.nextInt() // Number of seconds
    val a = IntArray( n ) { st.nextInt() } // Array of baking rates
    a.sortDescending() // Sort in descending order to prioritize higher rate ovens
    var r = 0L // Result accumulator
    for ( i in 0 until min( n, m ) ) {
        // Multiply the oven's rate by how many seconds it will be used (m - i)
        r += a[i].toLong() * ( m - i )
    }
    pw.println( r )
}

private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/