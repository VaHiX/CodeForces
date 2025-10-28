// Problem: CF 2102 D - Quartet Swapping
// https://codeforces.com/contest/2102/problem/D

/*
 * Problem: D. Quartet Swapping
 * Purpose: Given a permutation of integers from 1 to n, determine the lexicographically smallest
 *          permutation that can be obtained by swapping pairs of elements at indices (i, i+2) and (i+1, i+3)
 *          simultaneously for any valid index i.
 *
 * Algorithm:
 * - Split the array into two arrays: one containing elements at even indices (0-based), 
 *   and one at odd indices.
 * - Sort each of these subarrays independently.
 * - Reconstruct the final array by placing sorted even-indexed elements at even positions,
 *   and sorted odd-indexed elements at odd positions.
 * - If the parity (odd/even) of cycles in the original permutation differs from that of the sorted version,
 *   adjust the last two elements to ensure correct parity, swapping the last three and last element.
 *
 * Time Complexity: O(n log n), due to sorting operations on subarrays
 * Space Complexity: O(n), for storing copies of subarrays during sorting
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
    val a = IntArray( n ) { st.nextInt() }
    if ( n < 4 ) {
        pw.println( a.joinToString( " " ) )
        return
    }
    val b = sort( a )
    if ( odd( a ) != odd( b ) ) {
        // Adjust parity if needed
        val t = b[n - 3]
        b[n - 3] = b[n - 1]
        b[n - 1] = t
    }
    pw.println( b.joinToString( " " ) )
}

// Sort the array by splitting into even and odd indexed elements,
// sorting each part separately, then merging.
fun sort( a: IntArray ): IntArray {
    val t1 = IntArray( ( a.size + 1 ) / 2 ) { a[it * 2] }      // Collect even-indexed elements
    val t2 = IntArray( a.size / 2 ) { a[it * 2 + 1] }         // Collect odd-indexed elements
    t1.sort()
    t2.sort()
    return IntArray( a.size ) { if ( it % 2 == 0 ) t1[it / 2] else t2[it / 2] }
}

// Determine whether the number of cycles with even length is odd.
// This helps assess parity changes in permutation.
fun odd( a: IntArray ): Boolean {
    val g = BooleanArray( a.size )
    var o = true
    for ( i in a.indices ) {
        if ( g[i] ) continue
        var c = 0
        var j = i
        do {
            g[j] = true
            c ++
            j = a[j] - 1   // Convert to 0-based indexing
        } while ( j != i )
        if ( c % 2 == 0 ) o = ! o
    }
    return o
}

private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/