// Problem: CF 2155 E - Mimo & Yuyu
// https://codeforces.com/contest/2155/problem/E

/*
 * Problem: E. Mimo & Yuyu
 * Algorithms/Techniques: Game theory, Nim-like game, parity analysis
 * 
 * Time Complexity: O(k) per test case, where k is the number of tokens
 * Space Complexity: O(m) for storing counts of tokens in each column
 *
 * The game involves moving tokens from higher columns to lower columns such that:
 * - Each move must go from col c1 to col c2 where c1 > c2 (strictly decreasing)
 * - Moves follow adjacent grid paths (Manhattan distance 1)
 * - Tokens can only be moved to the first column
 * 
 * Key Insight: The game is essentially about parity of token counts per column.
 * If we have an odd number of tokens in any column >= 2, then there exists a winning strategy for the first player.
 * This is based on the fact that the game resembles a Nim-like structure where each "pile" (column) influences the outcome.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import java.util.HashMap 

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine()?.toIntOrNull() ?: return // Read number of test cases
    val output = StringBuilder()
    repeat(t) {
        var st = StringTokenizer(br.readLine())
        val n = st.nextToken().toLong() // Number of rows
        val m = st.nextToken().toLong() // Number of columns
        val k = st.nextToken().toInt() // Number of tokens
        val counts = HashMap<Long, Int>() // Count tokens per column (1-indexed)
        for (i in 0 until k) {
            st = StringTokenizer(br.readLine())
            st.nextToken() // Read token row (ignore)
            val y = st.nextToken().toLong() // Read token column
            if (y >= 1 && y <= m) { // Only consider valid columns
                counts[y] = counts.getOrDefault(y, 0) + 1 // Increment count for that column
            }
        }
        var f = false 
        if (n == 1L) { // Special case when only one row
            if (m >= 2) {
                val countY2 = counts.getOrDefault(2L, 0) // Count of tokens in column 2
                if (countY2 % 2 != 0) { // If odd number of tokens in column 2, Mimo wins
                    f = true
                }
            }
        } else {
            for (y in counts.keys) {
                if (y >= 2) { // Only evaluate columns >= 2
                    val count = counts.getValue(y)
                    if (count % 2 != 0) { // If odd number of tokens in column y, Mimo wins
                        f = true
                        break 
                    }
                }
            }
        }
        if (f) {
            output.append("Mimo\n") // Mimo wins if any column has odd number of tokens
        } else {
            output.append("Yuyu\n") // Yuyu wins otherwise
        }
    }
    print(output.toString())
}


// https://github.com/VaHiX/CodeForces/