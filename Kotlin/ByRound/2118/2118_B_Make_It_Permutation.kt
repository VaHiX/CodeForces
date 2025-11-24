// Problem: CF 2118 B - Make It Permutation
// https://codeforces.com/contest/2118/problem/B

/**
 * Problem: B. Make It Permutation
 *
 * Purpose:
 *   Given an n×n matrix A where A[i][j] = j for all 1 ≤ i,j ≤ n,
 *   we need to perform at most 2n operations (reversing subarrays in rows)
 *   such that every column contains a permutation of integers from 1 to n.
 *
 * Algorithm/Techniques:
 *   - The key insight is to rearrange each row so that column i contains values
 *     1, 2, ..., n in some order by reversing appropriate subarrays.
 *   - For each row i (from 2 to n), reverse the subarray from position 1 to i,
 *     moving value i to the front of that row.
 *   - Then for each column from 1 to n-2, perform a reversal to bring element n
 *     into place in the correct column.
 *
 * Time Complexity:
 *   O(n^2) per test case due to the nested operations on rows and columns.
 *
 * Space Complexity:
 *   O(1) additional space (not counting input/output buffers).
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
    pw.println( 2 * n - 3 ) // Total operations needed
    // Reverse subarrays to move elements to front of rows (from 2nd row onward)
    for ( i in 2 .. n ) pw.println( "$i 1 $i" )
    // Move the largest element 'n' into proper columns
    for ( i in 1 .. n - 2 ) pw.println( "$i ${i + 1} $n" )
}
private fun StreamTokenizer.nextInt(): Int {
    nextToken()
    return nval.toInt()
}


// https://github.com/VaHiX/CodeForces/