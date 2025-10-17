// Problem: CF 2134 E - Power Boxes
// https://codeforces.com/contest/2134/problem/E

/*
E. Power Boxes

Algorithm:
This solution uses a greedy approach to determine the power values of boxes by making strategic throws and swaps.
It processes boxes from right to left, using swap operations to reorder boxes in a way that allows efficient deduction of power values.
Key idea:
- Use throw queries to gather information about box positions and their power values
- Use swap queries to reorganize boxes and reduce uncertainty
- Maintain state (swaps made) for later reversal to restore final configuration

Time Complexity: O(n^2) in worst case due to nested operations during processing, but limited by 3n/2 query constraint.
Space Complexity: O(n) for storing information related to boxes' positions and power values.
*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.io.StreamTokenizer
import java.util.*
import kotlin.collections.ArrayList
import kotlin.system.exitProcess

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

private class State( val n: Int ) {
    var requests = 0
    val swaps = ArrayList<Int>()
    
    private fun incRec() {
        requests ++
        if ( requests  > ( 3 * n + 1 ) / 2 ) exitProcess( 0 )
    }
    
    fun throwBall( pos: Int ): Int {
        pw.println( "throw ${pos + 1}" )
        pw.flush()
        incRec()
        return st.nextInt()
    }
    
    fun swap( pos: Int ) {
        pw.println( "swap ${pos + 1}" )
        pw.flush()
        incRec()
        swaps.add( pos )
    }
    
    fun unswap( p: IntArray ) {
        for ( pos in swaps.reversed() ) {
            val t = p[pos]
            p[pos] = p[pos + 1]
            p[pos + 1] = t
        }
    }
}

private fun solveTest() {
    val n = st.nextInt()
    val l = IntArray( n + 2 ) // l[i] stores the result of throw i+1 operation
    val p = IntArray( n ) // p[i] will store power value (1 or 2) for box at idx i
    var i = n - 1 // i is current index being processed
    val state = State( n )
    
    while ( i >= 0 ) {
        if ( l[i + 1] != l[i + 2] ) {
            // When previous throw results differ, directly check this position
            l[i] = state.throwBall( i )
            p[i] = if ( l[i] == l[i + 1] + 1 ) 1 else 2
            i --
            continue
        }
        // If previous result is same, we have an ambiguity that can be resolved with a swap
        if ( i > 0 ) {
            // Check with a throw at position i - 1 to distinguish cases
            l[i - 1] = state.throwBall( i - 1 )
            p[i - 1] = if ( l[i - 1] == l[i + 1] + 1 ) 2 else 1
            // Perform a swap and update info accordingly
            state.swap( i - 1 )
            p[i] = p[i - 1]
            l[i] = l[i + 1] + 1
            l[i - 1] = state.throwBall( i - 1 )
            p[i - 1] = if ( l[i - 1] == l[i + 1] + 1 ) 2 else 1
            i -= 2
            continue
        }
        // For last element, swap and resolve by throwing at next position
        state.swap( i )
        p[i] = p[i + 1]
        l[i] = l[i + 2] + 1
        l[i + 1] = state.throwBall( i + 1 )
        p[i + 1] = if ( l[i + 1] == l[i + 2] + 1 ) 1 else 2
        i --
    }
    
    // Reverse swaps made to restore initial array order before outputting final answer
    state.unswap( p )
    pw.println( "! ${p.joinToString( " " )}" )
    pw.flush()
}

private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/