// Problem: CF 1910 B - Security Guard
// https://codeforces.com/contest/1910/problem/B

/*
 * Problem: B. Security Guard
 * Purpose: Determine if a sequence of + and - operations can be made valid by swapping at most one pair of characters.
 * Algorithm:
 *   1. For each string, simulate the process of entering/leaving people.
 *   2. Track the minimum count of people inside the university during the process (runningFold).
 *   3. If the minimum is negative, it's impossible to make it valid by swapping any one pair.
 *   4. Otherwise:
 *      - Find the first '-' and last '+' that can be swapped to fix imbalance.
 *      - If such pair exists, swap them and output their indices.
 *      - Else, just report a no-op swap (e.g., "1 1").
 *
 * Time Complexity: O(n) per test case, where n is the length of string s.
 * Space Complexity: O(n) for storing the character array and intermediate running fold values.
 */

fun main() {
    repeat(readInt()) {
        val s = readln().toCharArray()
        val firstMinus = s.indexOfFirst { it == '-' } // Find index of first minus
        val lastPlus = s.indexOfLast { it == '+' }    // Find index of last plus
        
        val ans =
            if (firstMinus != -1 && lastPlus != -1 && firstMinus < lastPlus) {
                // Swap the first minus and last plus to potentially fix the sequence
                s[firstMinus] = '+'  // Change first minus to plus
                s[lastPlus] = '-'   // Change last plus to minus
                "${firstMinus + 1} ${lastPlus + 1}" // Output 1-based indices
            } else {
                "1 1" // No valid swap possible; pretend we swap positions 1 and 1
            }
        
        println(
            if (s.runningFold(0) { acc, c -> acc + (if (c == '+') 1 else -1) }.min() < 0) {
                // If at any point people inside the university go below zero, it's invalid
                -1
            } else {
                ans // Return either swap indices or "1 1"
            }
        )
    }
}

private fun readInt() = readln().toInt()


// https://github.com/VaHiX/codeForces/