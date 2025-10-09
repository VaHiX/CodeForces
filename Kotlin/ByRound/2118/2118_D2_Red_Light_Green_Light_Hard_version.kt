// Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
// https://codeforces.com/contest/2118/problem/D2

/*
 * Problem: D2. Red Light, Green Light (Hard version)
 *
 * Algorithm/Techniques:
 * - Preprocessing with TreeSet for efficient ceiling/floor queries on modular arithmetic.
 * - Simulating movement with memoization to detect cycles.
 * - Modular arithmetic with custom mod function to handle negative values correctly.
 *
 * Time Complexity: O(n log n + q * sqrt(k))
 * Space Complexity: O(n)
 *
 * Key idea:
 * For each query, simulate the movement by following the traffic lights until
 * either leaving the strip (YES), detecting a cycle (NO), or hitting an unreachable limit.
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
 * Data class to represent a traffic light stop with shift, x-coordinate and index.
 */
private data class Stop( val shift: Long, val x: Long, val idx: Int = -1 ): Comparable<Stop> {
    override fun compareTo( other: Stop ): Int {
        if ( shift !=  other.shift ) return shift.compareTo( other.shift )
        return x.compareTo( other.x )
    }
}

private fun solveTest() {
    val ( N, k ) = br.nextLongs()
    val n = N.toInt()
    val p = br.nextLongs()
    val d = br.nextLongs()
    br.readLine()
    val q = br.nextLongs()
    
    // TreeSet to store stops based on shift and x for fast ceiling/floor queries
    val rstops = TreeSet( p.indices.map { i -> Stop( mod( p[i] - d[i], k ), p[i], i ) } )
    val lstops = TreeSet( p.indices.map { i -> Stop( mod( p[i] + d[i], k ), p[i], i ) } )
    
    // r[0] for leftward direction, r[1] for rightward
    val r = Array( 2 ) { IntArray( n ) { 0 } }
    
    // List to temporarily store sequence of visited indices
    val list = IntArray( 2 * n )
    
    for ( qq in q ) {
        var ls = 0
        var right = 1       // 1 = going right, 0 = going left
        var x = qq - 1      // Current position
        var t = -1L         // Time passed
        var answer = 0      // 0=not determined, 1=yes, -1=no (cycle)

        while ( true ) {
            // Get next stop based on current direction and time
            val stop = if ( right == 1 ) 
                rstops.ceiling( Stop( mod( x - t, k ), x + 1 ) ) 
            else 
                lstops.floor( Stop( mod( x + t, k ), x - 1 ) )

            // Check if no more stops or wrong shift
            if ( stop == null || stop.shift != if ( right == 1 ) mod( x - t, k ) else mod( x + t, k ) ) {
                answer = 1
                break
            }
            
            // If already visited this stop in current path, it's a cycle
            if ( r[right][stop.idx] == 2 ) {
                answer = -1
                break
            }
            
            // Already determined outcome for this stop
            if ( r[right][stop.idx] != 0 ) {
                answer = r[right][stop.idx]
                break
            }
            
            // Add to path and update state
            list[ls ++] = if ( right == 1 ) stop.idx else -stop.idx - 1
            t += abs( stop.x - x )
            x = stop.x
            r[right][stop.idx] = 2  // Mark as visited in current path
            right = 1 - right       // Switch direction
        }
        
        // Update memoization table with final result
        for ( l in list.slice( 0 until ls ) ) {
            if ( l >= 0 ) {
                r[1][l] = answer
            } else {
                r[0][-l - 1] = answer
            }
        }
        
        pw.println( if ( answer == 1 ) "YES" else if ( answer == -1 ) "NO" else "!!!" )
    }
}

/**
 * Naive simulation for reference, not used in final implementation.
 */
private fun naive(n: Int, k: Long, p: LongArray, d: LongArray, qq: Long ): Int {
    val dp = HashSet<Triple<Int, Long, Long>>()
    var x = qq
    var t = 0
    var dir = 1
    while ( true ) {
        if ( x <= 0 || x > p.last() ) return 1
        val state = Triple(dir, x, t % k)
        if ( state in dp ) return -1
        dp.add( state )
        val tl = p.indexOf( x )
        if ( tl >= 0 && d[tl] == t % k ) {
            dir = -dir
        }
        x += dir
        t ++
    }
}

private fun BufferedReader.nextLongs(): LongArray {
    return readLine().split( " " ).map { it.toLong() }.toLongArray()
}

private fun BufferedReader.nextInt(): Int {
    return nextLongs()[0].toInt()
}

/**
 * Modular arithmetic helper to ensure result is in range [0, b).
 */
private fun mod( a: Long, b: Long ): Long {
    var t = a % b
    if ( t < 0 ) t += b
    return t
}


// https://github.com/VaHiX/CodeForces/