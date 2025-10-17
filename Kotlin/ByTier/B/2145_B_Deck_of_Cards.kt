// Problem: CF 2145 B - Deck of Cards
// https://codeforces.com/contest/2145/problem/B

/*
 * Problem: B. Deck of Cards
 * Purpose: Determine the fate of each card after a series of removal operations.
 *          Cards are removed from either top or bottom, or can be removed from either,
 *          leading to uncertainty in some cases.
 *
 * Algorithm:
 * 1. Count occurrences of '0' (top), '1' (bottom), and '2' (either) in the input string.
 * 2. For each card position in the deck:
 *    - If all cards will be removed by action sequence, mark as '-'.
 *    - If a card is definitely removed due to top or bottom removals, mark as '-'.
 *    - Otherwise, if it can remain depending on choice of removal (in case of '2'), mark as '?'
 *    - Else, mark as '+'.
 *
 * Time Complexity: O(n + k) per test case where n is the number of cards and k is the number of operations.
 * Space Complexity: O(n) for storing the result string and temporary counts.
 */

import java.util.Scanner

fun main() {
    val inputScanner = Scanner(System.`in`)
    var testCases = inputScanner.nextInt()
    while (testCases-- >0) {
        val count = inputScanner.nextInt()
        val unusedCount = inputScanner.nextInt() 
        inputScanner.nextLine()
        val inputString = inputScanner.nextLine()
        val resultBuilder = StringBuilder()
        for (index in 0 until count) {
            resultBuilder.append('+')
        }
        var zerosCount =0
        var onesCount =0
        var unknownCount =0
        for (character in inputString.toCharArray()) {
            when (character) {
                '0' -> zerosCount++         // Count of top removals
                '1' -> onesCount++          // Count of bottom removals
                else -> unknownCount++      // Count of uncertain removals
            }
        }
        if (unusedCount == count) {
            for (index in 0 until count) {
                resultBuilder.setCharAt(index,'-')   // If all actions are used, all cards removed
            }
        } else {
            // Mark first 'zerosCount' cards from left as removed ('-')
            for (index in 0 until zerosCount) {
                resultBuilder.setCharAt(index,'-')
            }
            // Mark last 'onesCount' cards from right as removed ('-')
            for (index in 0 until onesCount) {
                resultBuilder.setCharAt(count - 1 - index, '-')
            }
            val leftUnknownBoundary = zerosCount
            val rightUnknownBoundary = count-1-onesCount
            if (unknownCount > 0) {
                // Fill the uncertain region with '?'
                for (index in leftUnknownBoundary until leftUnknownBoundary + unknownCount) {
                    if (index <= rightUnknownBoundary) {
                        resultBuilder.setCharAt(index,'?')
                    }
                }
                for (index in rightUnknownBoundary downTo rightUnknownBoundary - unknownCount + 1) {
                    if (index >= leftUnknownBoundary) {
                        resultBuilder.setCharAt(index,'?')
                    }
                }
            }
        }
        println(resultBuilder.toString())
    }
}


// https://github.com/VaHiX/CodeForces/