// Problem: CF 1533 A - Travel to Bertown
// https://codeforces.com/contest/1533/problem/A

/*
 * Problem: A. Travel to Bertown
 * 
 * Purpose: Given n friends who can host Vika from day l_i to r_i (inclusive),
 *          find the maximum number of consecutive days she can stay if she stays
 *          at exactly one friend's house, starting on day k.
 * 
 * Algorithm:
 *   - For each friend's interval [l_i, r_i], check if Vika can stay there (l_i <= k).
 *   - Among all such valid intervals, compute how many days remain from day k to r_i.
 *   - Return the maximum among these values.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 * 
 * Techniques:
 *   - Linear scan of intervals
 *   - Greedy selection based on overlap with start day k
 */

import java.io.*
import java.util.*

object program {
    @JvmStatic
    fun main(args: Array<String>) {
        val inputStream = System.`in`
        val outputStream: OutputStream = System.out
        val `in` = InputReader(inputStream)
        val out = PrintWriter(outputStream)
        val solver = APuteshestvieVBertaun()
        val testCount = `in`.next().toInt()
        for (i in 1..testCount) solver.solve(i, `in`, out)
        out.close()
    }
    
    internal class APuteshestvieVBertaun {
        fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
            val n = `in`.nextInt() // Number of friends
            val k = `in`.nextInt() // Day Vika arrives
            var res = 0 // Maximum number of days she can stay
            
            for (i in 0 until n) {
                val l = `in`.nextInt() // Start day of friend's offer
                val r = `in`.nextInt() // End day of friend's offer
                
                if (l <= k) { // Only consider friends who can host her on day k
                    // Calculate how many days from day k to the end of their stay
                    res = Math.max(res, r - k + 1)
                }
            }
            
            out.println(res) // Output the maximum number of days
        }
    }
    
    internal class InputReader(stream: InputStream?) {
        var reader: BufferedReader
        var tokenizer: StringTokenizer?
        
        operator fun next(): String {
            while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
                tokenizer =
                    try {
                        StringTokenizer(reader.readLine())
                    } catch (e: IOException) {
                        throw RuntimeException(e)
                    }
            }
            return tokenizer!!.nextToken()
        }
        
        fun nextInt(): Int {
            return next().toInt()
        }
        
        init {
            reader = BufferedReader(InputStreamReader(stream), 32768)
            tokenizer = null
        }
    }
}


// https://github.com/VaHiX/codeForces/