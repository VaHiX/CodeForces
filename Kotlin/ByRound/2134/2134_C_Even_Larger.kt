// Problem: CF 2134 C - Even Larger
// https://codeforces.com/contest/2134/problem/C

/**
 * Problem: C. Even Larger
 *
 * Purpose:
 *   Given an array of non-negative integers, we need to make it "good" by decreasing elements
 *   such that for every subarray of length >= 2, the sum of elements at even indices is >= 
 *   sum of elements at odd indices in that subarray. We use a greedy approach to minimize
 *   operations.
 *
 * Algorithm:
 *   - Process the array from left to right in pairs (i, i+1) where i is odd index.
 *   - For each such pair, if the value at the odd index is too small compared to neighbors,
 *     adjust the values by reducing one of the neighbor elements to meet the condition.
 *   - We only process even-length segments of the array to avoid redundant checks.
 *
 * Time Complexity:
 *   O(n) where n is the length of the array. Each element is processed once in a single pass.
 *
 * Space Complexity:
 *   O(n) for storing the array and auxiliary variables.
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
    // Use only even-length portion of the array, padding with 0 if needed
    val a = IntArray( n + 1 - n % 2 ) { if ( it < n ) st.nextInt() else 0 }
    var r = 0L
    // Iterate over odd indices (i) in steps of 2 to check conditions for triplets
    for ( i in 1 until n step 2 ) {
        // If current element is already large enough, skip
        if ( a[i] >= a[i - 1] + a[i + 1] ) continue
        // Calculate how much operations are needed to make the constraint satisfied
        r += a[i - 1] + a[i + 1] - a[i]
        // If left neighbor is smaller or equal, reduce right neighbor
        if ( a[i - 1] <= a[i] ) {
            a[i + 1] = a[i] - a[i - 1]
        } else {
            // Else reduce the left neighbor to 0 and shift difference to the right
            a[i - 1] = a[i]
            a[i + 1] = 0
        }
    }
    pw.println( r )
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/codeForces/