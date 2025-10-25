// Problem: CF 2098 C - Sports Betting
// https://codeforces.com/contest/2098/problem/C

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
    val d2c = TreeMap<Int, Int>() // Map to count occurrences of each day
    for ( i in 1..n ) {
        val day = st.nextInt()
        d2c[day] = d2c.getOrDefault( day, 0 ) + 1
    }
    var ok = false // Flag to determine if a winning strategy exists
    for ( day in d2c.keys ) {
        if ( d2c[day]!! >= 4 ) {
            // If there are 4 or more bets on the same day, 
            // Vadim can guarantee a win by assigning predictions 
            // such that at least one student is correct.
            ok = true
            break
        }
        if ( d2c[day]!! >= 2 ) {
            // If there are at least 2 bets on a day, 
            // check if there are at least 2 bets on (day + 1) 
            // to guarantee a win through a pair of consecutive days.
            var d = day + 1
            while ( true ) {
                val cnt = d2c.getOrDefault( d, 0 )
                if ( cnt >= 2 ) {
                    // Found a pair of consecutive days
                    // where each has at least 2 bets,
                    // allowing Vadim to assign consistent predictions
                    ok = true
                    break
                }
                if ( cnt == 0 ) break
                // Continue checking subsequent days
                d ++
            }
            if ( ok ) break
        }
    }
    println( if ( ok ) "Yes" else "No" )
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/