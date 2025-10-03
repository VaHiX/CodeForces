// Problem: CF 2102 C - Mex in the Grid
// https://codeforces.com/contest/2102/problem/C

/**
 * Problem: Mex in the Grid
 *
 * Purpose:
 *   Arrange numbers from 0 to n^2 - 1 in an n x n grid such that the sum of MEX values
 *   over all possible subgrids is maximized.
 *
 * Approach:
 *   The algorithm uses a spiral-like filling technique starting from the center and moving outward,
 *   placing values in a way to maximize the chances of achieving higher MEX values in subgrids.
 *   It fills the grid layer by layer, spiraling from the center outwards, and places consecutive integers
 *   along each boundary of the current layer.
 *
 * Complexity:
 *   Time: O(n^2) per test case — Each cell is visited exactly once during the spiral traversal.
 *   Space: O(n^2) — For storing the n x n grid.
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
    val a = Array( n ) { IntArray( n ) { -1 } }
    var l = ( n - 1 ) / 2   // Left boundary of current layer, starts from center
    var r = n / 2           // Right boundary of current layer, starts from center
    var cur = 0             // Current number to place in the grid
    while ( l >= 0 ) {
        // Fill top row from left to right
        for ( x in ( if ( cur == 0 ) l else l + 1 ) .. r ) {  // Start from l if cur==0, else l+1
            a[l][x] = cur
            cur ++
        }
        // Fill right column from top to bottom
        for ( y in l + 1 .. r ) {
            a[y][r] = cur
            cur ++
        }
        // Fill bottom row from right to left
        for ( x in r - 1 downTo l ) {
            a[r][x] = cur
            cur ++
        }
        // Fill left column from bottom to top
        for ( y in r - 1 downTo ( if ( r == n / 2 ) l + 1 else l ) ) {  // Adjust starting point based on center
            a[y][l] = cur
            cur ++
        }
        l --    // Move to outer layer
        r ++    // Move to outer layer
    }
    // Output the grid
    for ( aa in a ) {
        pw.print( aa[0] )
        for ( i in 1 until n ) {
            pw.print( " " )
            pw.print( aa[i] )
        }
        pw.println()
    }
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/