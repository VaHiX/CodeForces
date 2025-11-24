// Problem: CF 2118 D1 - Red Light, Green Light (Easy version)
// https://codeforces.com/contest/2118/problem/D1

/*
 * Problem: D1. Red Light, Green Light (Easy version)
 * Algorithm/Techniques: Simulation with TreeSet for efficient stop lookup, BFS-like traversal with memoization.
 * Time Complexity: O((n + q) * log(n) * log(n)) per test case due to TreeSet operations and iteration over queries.
 * Space Complexity: O(n + q) for storing stops, queries, and auxiliary arrays.
 *
 * Description:
 * This problem involves a strip of length 10^15 with n traffic lights at positions p_i.
 * Each light has an initial delay d_i. A light is red at seconds l*k + d_i (for integer l).
 * You start at a given position, moving in direction +1 until a red light blocks you,
 * then you turn around and move in opposite direction. Determine whether you will leave the strip
 * within 10^100 seconds.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.io.StreamTokenizer
import java.util.*
import kotlin.math.abs

private val br = BufferedReader( InputStreamReader( System.`in` ) )
private val st = StreamTokenizer( br )
private val pw = PrintWriter( System.out )

fun main() {
    solve()
    pw.close()
}

private val random = Random( 3495678 )

private fun solve() {
    val tn = br.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}

/**
 * Representation of a traffic light stop, sorted by shift then x.
 */
private data class Stop( val shift: Long, val x: Long, val idx: Int = -1 ): Comparable<Stop> {
    override fun compareTo( other: Stop ): Int {
        if ( shift !=  other.shift ) return shift.compareTo( other.shift )
        return x.compareTo( other.x )
    }
}

/**
 * Solves a single test case.
 */
private fun solveTest() {
    val ( N, k ) = br.nextLongs()
    val n = N.toInt()
    val p = br.nextLongs()
    val d = br.nextLongs()
    br.readLine()
    val q = br.nextLongs()
    
    // TreeSet for rightward stops and leftward stops based on mod values
    val rstops = TreeSet( p.indices.map { i -> Stop( mod( p[i] - d[i], k ), p[i], i ) } )
    val lstops = TreeSet( p.indices.map { i -> Stop( mod( p[i] + d[i], k ), p[i], i ) } )
    
    // Memoization array for tracking results of paths
    val r = Array( 2 ) { IntArray( n ) { 0 } }
    val list = IntArray( 2 * n )
    
    for ( qq in q ) {
        var ls = 0
        var right = 1
        var x = qq - 1
        var t = -1L
        var answer = 0
        
        while ( true ) {
            // Determine next stop based on direction
            val stop = if ( right == 1 ) rstops.ceiling( Stop( mod( x - t, k ), x + 1 ) ) 
                       else lstops.floor( Stop( mod( x + t, k ), x - 1 ) )
            
            // If we don't find a valid stop or match mismatch, break
            if ( stop == null || stop.shift != if ( right == 1 ) mod( x - t, k ) else mod( x + t, k ) ) {
                answer = 1 // YES: exited the strip
                break
            }
            
            // If we've visited this stop in current path, cycle detected -> NO
            if ( r[right][stop.idx] == 2 ) {
                answer = -1
                break
            }
            
            // Read cached answer if exists
            if ( r[right][stop.idx] != 0 ) {
                answer = r[right][stop.idx]
                break
            }
            
            // Record current stop in path
            list[ls ++] = if ( right == 1 ) stop.idx else -stop.idx - 1
            t += abs( stop.x - x )
            x = stop.x
            r[right][stop.idx] = 2 // Mark as in path
            right = 1 - right // Switch direction
        }
        
        // Update memoization table
        for ( l in list.slice( 0 until ls ) ) {
            if ( l >= 0 ) {
                r[1][l] = answer
            } else {
                r[0][-l - 1] = answer
            }
        }
        
        // Output result
        pw.println( if ( answer == 1 ) "YES" else if ( answer == -1 ) "NO" else "!!!" )
    }
}

/**
 * Naive simulation approach for small inputs or debugging.
 */
private fun naive(n: Int, k: Long, p: LongArray, d: LongArray, qq: Long ): Int {
    val dp = HashSet<Triple<Int, Long, Long>>()
    var x = qq
    var t = 0
    var dir = 1
    
    while ( true ) {
        if ( x <= 0 || x > p.last() ) return 1 // YES
        val state = Triple(dir, x, t % k)
        if ( state in dp ) return -1 // NO: loop detected
        dp.add( state )
        val tl = p.indexOf( x )
        if ( tl >= 0 && d[tl] == t % k ) {
            dir = -dir
        }
        x += dir
        t ++
    }
}

/**
 * Helper to split next line into longs.
 */
private fun BufferedReader.nextLongs(): LongArray {
    return readLine().split( " " ).map { it.toLong() }.toLongArray()
}

/**
 * Reads integer from input.
 */
private fun BufferedReader.nextInt(): Int {
    return nextLongs()[0].toInt()
}

/**
 * Modular arithmetic helper to handle negative numbers correctly.
 */
private fun mod( a: Long, b: Long ): Long {
    var t = a % b
    if ( t < 0 ) t += b
    return t
}


// https://github.com/VaHiX/CodeForces/