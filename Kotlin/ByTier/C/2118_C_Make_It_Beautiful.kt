// Problem: CF 2118 C - Make It Beautiful
// https://codeforces.com/contest/2118/problem/C

/*
C. Make It Beautiful

Algorithm:
The solution uses a greedy approach to maximize the beauty of the array by incrementing elements to set more bits to 1.
For each bit position from least significant to most significant:
- Try to flip as many 0-bits to 1-bits as possible using available operations (k).
- For each element, if it has a 0-bit at current position and we have enough operations,
  increment that element to make the bit 1.

Time Complexity: O(60 * n) = O(n), where 60 is the number of bits in a long integer.
Space Complexity: O(n) for storing the array elements.

Techniques:
- Bit manipulation
- Greedy algorithm
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
    val tn = br.nextInt()
    for ( test in 1 .. tn ) {
        solveTest()
    }
}

private fun solveTest() {
    var ( N, k ) = br.nextLongs()
    val n = N.toInt()
    val a = br.nextLongs()
    var ones = a.sumOf { it.countOneBits() } // Count initial number of 1-bits in all numbers
    
    for ( sh in 0 .. 60 ) {
        val mask = 1L shl sh // Create bitmask for current bit position
        if ( k < mask ) break // If we don't have enough operations to flip this bit, stop
        
        for ( b in a ) {
            if ( ( b and mask ) == 0L ) { // Check if the current bit is 0
                k -= mask // Spend operations to set this bit to 1
                ones ++ // Increment count of 1-bits
            }
            if ( k < mask ) break // If we run out of operations, stop
        }
    }
    
    pw.println( ones )
}

private fun BufferedReader.nextLongs(): LongArray {
    return readLine().split( " " ).map { it.toLong() }.toLongArray()
}

private fun BufferedReader.nextInt(): Int {
    return nextLongs()[0].toInt()
}


// https://github.com/VaHiX/CodeForces/