// Problem: CF 2111 E - Changing the String
// https://codeforces.com/contest/2111/problem/E

/*
 * Problem: E. Changing the String
 * Purpose: To transform a string consisting of 'a', 'b', and 'c' characters into the lexicographically smallest string
 *          by performing a series of operations that allow changing one occurrence of character x to character y.
 *
 * Algorithm:
 * - Use greedy approach:
 *   - Process all operations first to determine how many 'b' -> 'a' and 'c' -> 'a' transformations can be done,
 *     preferring direct 'b'->'a' or 'c'->'a' over longer chains like 'b'->'c'->'a'.
 *   - For each character in the string:
 *     - If it's 'b', change to 'a' if possible using available 'ba' or 'cba' transformations.
 *     - If it's 'c', change to 'a' if possible using available 'ca', 'bca', 'cba' or 'cb' -> 'b' transformations.
 *
 * Time Complexity: O(n + m) where n is the length of string s, and m is number of operations
 * Space Complexity: O(1) - Only fixed-size variables used regardless of input size.
 */
import java.util.Scanner

fun solve(scanner: Scanner) {
    var ca = 0 // count of 'c' -> 'a' transformations allowed later
    var cb = 0 // count of 'c' -> 'b' operations
    var ba = 0 // count of 'b' -> 'a' operations or directly available 'b's to convert to 'a'
    var bc = 0 // count of 'b' -> 'c' operations (to use for future 'c' -> 'a')
    var cba = 0 // count of 'c' -> 'b' then 'b' -> 'a' transformations (chain: c->b->a)
    var bca = 0 // count of 'b' -> 'c' then 'c' -> 'a' transformations (chain: b->c->a)
    val n = scanner.nextInt()
    val m = scanner.nextInt()
    val s = scanner.next().toCharArray()
    
    repeat(m) {
        val x = scanner.next()[0]
        val y = scanner.next()[0]
        when {
            x == 'b' && y == 'a' -> {
                if (cb > 0) { // If we have a 'c' that can be converted to 'b', then convert this 'b' to 'a'
                    cb--
                    cba++ // This forms a chain: c->b->a
                } else {
                    ba++ // Direct conversion of 'b' to 'a' using existing 'b's
                }
            }
            x == 'b' && y == 'c' -> bc++ // Store the number of 'b' to 'c' conversions
            x == 'c' && y == 'a' -> {
                if (bc > 0) { // If we can take a 'b' and convert it into 'c', then convert this 'c' to 'a'
                    bc--
                    bca++ // This forms a chain: b->c->a
                } else {
                    ca++ // Direct conversion of 'c' to 'a'
                }
            }
            x == 'c' && y == 'b' -> cb++ // Store the number of 'c' to 'b' conversions
        }
    }
    
    for (i in s.indices) {
        when (s[i]) {
            'b' -> {
                when {
                    ba > 0 -> { // There are direct 'b' -> 'a' transformations available
                        s[i] = 'a'
                        ba--
                    }
                    cba > 0 -> { // There are 'c'->'b' then 'b'->'a' chain conversions available
                        cb++ // Release the 'b' for future use after consuming it here
                        cba--
                        s[i] = 'a'
                    }
                    bca > 0 -> { // There are 'b'->'c' then 'c'->'a' chain conversions available
                        s[i] = 'a'
                        bca-- // Use up one such chain
                    }
                }
            }
            'c' -> {
                when {
                    ca > 0 -> { // There are direct 'c' -> 'a' conversions available
                        s[i] = 'a'
                        ca--
                    }
                    bca > 0 -> { // There are 'b'->'c' then 'c'->'a' chain conversions available
                        s[i] = 'a'
                        bca-- // Use up one such chain
                    }
                    cba > 0 -> { // There are 'c'->'b' then 'b'->'a' chain conversions available
                        s[i] = 'a'
                        cba-- // Use up one such chain
                    }
                    cb > 0 -> { // There is a 'c' that can be used to get 'b', which will later become 'a'
                        s[i] = 'b'
                        cb--
                    }
                }
            }
        }
    }
    println(s.joinToString(""))
}

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        solve(scanner)
    }
}


// https://github.com/VaHiX/CodeForces/