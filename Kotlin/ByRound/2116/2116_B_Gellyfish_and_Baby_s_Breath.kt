// Problem: CF 2116 B - Gellyfish and Baby's Breath
// https://codeforces.com/contest/2116/problem/B

/**
 * Problem: B. Gellyfish and Baby's Breath
 * 
 * Purpose:
 *   Given two permutations p and q of [0, 1, ..., n-1], compute an array r where:
 *   r[i] = max_{j=0}^{i} (2^{p[j]} + 2^{q[i-j]})
 *   Output all elements modulo 998244353.
 *
 * Algorithms/Techniques:
 *   - Precompute powers of 2 modulo M for efficient lookup.
 *   - For each i, maintain maximum values of p and q seen so far to avoid recomputation.
 *   - Use optimized input parsing via StreamTokenizer.
 *
 * Time Complexity:
 *   O(n) per test case, since we process each index once and use constant-time operations
 *   for updates and max comparisons.
 *
 * Space Complexity:
 *   O(n) for precomputed powers of 2 and arrays p, q.
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

private const val M = 998244353
private const val MAXN = 100000

// Precompute powers of 2 modulo M to speed up calculations
private val p2 = run {
    val r = IntArray( MAXN )
    r[0] = 1
    for ( i in 1 until MAXN ) {
        r[i] = r[i - 1] * 2
        if ( r[i] >= M ) r[i] -= M
    }
    r
}

private fun solveTest() {
    val n = st.nextInt()
    val p = IntArray( n ) { st.nextInt() }
    val q = IntArray( n ) { st.nextInt() }
    
    var mip = 0 // index of max p[j] seen so far (j from 0 to i)
    var miq = 0 // index of max q[i-j] seen so far (j from 0 to i)
    
    for ( i in 0 until n ) {
        if ( p[i] > p[mip] ) mip = i
        if ( q[i] > q[miq] ) miq = i
        
        // Compute the maximum value of 2^{p[j]} + 2^{q[i-j]} for j=0..i
        // Using precomputed max indices to optimize evaluation
        pw.print( pow( max( Pair( p[mip], q[i - mip] ), Pair( q[miq], p[i - miq] ) ) ) )
        if ( i < n - 1 ) pw.print( " " )
    }
    pw.println()
}

fun pow( pair: Pair<Int, Int> ): Int {
    var r = p2[pair.first] + p2[pair.second]
    if ( r >= M ) r -= M
    return r
}

fun max(p1: Pair<Int, Int>, p2: Pair<Int, Int> ): Pair<Int, Int> {
    if ( p1.first > p2.first || ( p1.first == p2.first && p1.second > p2.second ) ) return p1
    return p2
}

private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/