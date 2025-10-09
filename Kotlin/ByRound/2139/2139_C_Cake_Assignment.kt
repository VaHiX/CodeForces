// Problem: CF 2139 C - Cake Assignment
// https://codeforces.com/contest/2139/problem/C

/**
 * Problem: Cake Assignment
 * 
 * Purpose:
 * This solution determines the minimum number of operations to redistribute cakes between Chocola and Vanilla so that Chocola ends up with exactly x cakes.
 * The algorithm uses a binary representation approach to simulate the steps needed to reach the target distribution.
 * 
 * Algorithms/Techniques:
 * - Binary manipulation and bit manipulation to trace the path from initial state to target.
 * - Greedy simulation of cake transfers using halving operations.
 * 
 * Time Complexity: O(k) per test case, where k is the input parameter determining the number of cakes.
 * Space Complexity: O(k), for storing the sequence of operations.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import kotlin.math.min

private val br = BufferedReader( InputStreamReader( System.`in` ) )
private val pw = PrintWriter( System.out )

fun main() {
    solve()
    pw.close()
}

private fun solve() {
    val tn = br.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}

private fun solveTest() {
    val ( k, x ) = br.nextLongs()
    val total = 1L shl ( k + 1 ).toInt()       // Total number of cakes: 2^(k+1)
    val half = 1L shl k.toInt()                // Half of total, initial amount each has: 2^k
    var cur = x                                // Current cakes Chocola has
    val switch = ArrayList<Boolean>( k.toInt() ) // Stores the direction of operations

    // Traverse from current state towards the middle (half) to determine operation sequence
    while ( cur != half ) {
        switch.add( cur > half )               // True if we need to give cakes to Vanilla (cur > half)
        cur = min( cur, total - cur )          // Mirror the position closer to half (to avoid overflow and simplify steps)
        cur *= 2                               // Scale up the value to simulate the next step in binary tree
    }

    pw.println( switch.size )

    var s = switch.sumOf { it -> ( if ( it ) 1 else 0 ).toInt() } // Count of True values (operations toward Vanilla)
    val r = ArrayList<Int>( switch.size )              // Result operations list

    // Reverse traversal to build operations in the correct order
    for ( i in switch.indices.reversed() ) {
        r.add( if ( s % 2 == 0 ) 1 else 2 )             // Choose operation based on parity of remaining switches
        s -= if ( switch[i] ) 1 else 0                  // Decrease counter if we're going to use a switch toward Vanilla
    }

    pw.println( r.joinToString( " " ) )
}

private fun BufferedReader.nextLongs(): LongArray {
    return readLine().split( ' ' ).map { it.toLong() }.toLongArray()
}

private fun BufferedReader.nextInt(): Int = nextLongs()[0].toInt()


// https://github.com/VaHiX/codeForces/