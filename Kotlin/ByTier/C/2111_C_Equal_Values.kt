// Problem: CF 2111 C - Equal Values
// https://codeforces.com/contest/2111/problem/C

/**
 * Problem: C. Equal Values
 * 
 * Purpose:
 *   This solution computes the minimum total cost to make all elements of an array equal
 *   using two types of operations:
 *     1. Set all elements to the left of a position i to a[i], cost = (i - 1) * a[i]
 *     2. Set all elements to the right of a position i to a[i], cost = (n - i) * a[i]
 * 
 * Algorithm:
 *   For each unique value in the array, we determine the optimal position to use as
 *   the target value. The cost is calculated as: value * (left_changes + right_changes).
 *   We iterate through each group of consecutive equal elements and compute the cost
 *   for using that value as a pivot.
 * 
 * Time Complexity:
 *   O(n) where n is the length of the array, since we traverse the array only once per test case.
 * 
 * Space Complexity:
 *   O(1) excluding input storage, as we use only a constant amount of additional variables.
 */

import java.util.*

fun processTestCase(scanner: Scanner) {
    val length = scanner.nextInt()
    val sequence = LongArray(length) { scanner.nextLong() }
    var minimumTotalCost = Long.MAX_VALUE
    var pointer = 0
    while (pointer < length) {
        var endPointer = pointer
        // Find the end of consecutive elements with the same value
        while (endPointer + 1 < length && sequence[endPointer + 1] == sequence[pointer]) {
            endPointer++
        }
        val currentValue = sequence[pointer]
        // Calculate how many changes are needed on the left side
        val leftChanges = pointer.toLong()
        // Calculate how many changes are needed on the right side
        val rightChanges = (length - 1 - endPointer).toLong()
        // Total cost if current value is used as pivot
        val totalCost = currentValue * (leftChanges + rightChanges)
        if (totalCost < minimumTotalCost) {
            minimumTotalCost = totalCost
        }
        pointer = endPointer + 1
    }
    println(minimumTotalCost)
}

fun main() {
    val scanner = Scanner(System.`in`)
    val numberOfCases = scanner.nextInt()
    repeat(numberOfCases) {
        processTestCase(scanner)
    }
    scanner.close()
}


// https://github.com/VaHiX/CodeForces/