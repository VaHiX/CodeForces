// Problem: CF 1910 D - Remove and Add
// https://codeforces.com/contest/1910/problem/D

/**
 * Problem: D. Remove and Add
 *
 * Purpose:
 *   Determines whether it's possible to make an array strictly increasing by:
 *   1. Removing exactly one element.
 *   2. Adding 1 to any subset of the remaining elements.
 *
 * Algorithm:
 *   - Greedily process the array from left to right.
 *   - When a non-increasing condition is encountered, check if we can resolve it:
 *     - If we've already dropped an element, return false.
 *     - Otherwise, drop current element and adjust based on previous elements.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) (excluding input storage)
 */
private fun solve(): Boolean {
    val n = readInt()
    val a = readInts().toIntArray()
    var dropped = false // Flag to track if we've already removed one element
    
    for (i in 1 until n) {
        if (a[i] == a[i - 1]) {
            // If elements are equal, increment the current one
            a[i]++
        } else if (a[i] < a[i - 1]) {
            // If current element is less than previous, we must remove it
            if (dropped) return false // Already removed one element, can't do more
            dropped = true
            
            if (i != 1) {
                // Adjust based on two positions back to maintain strictly increasing order
                when {
                    a[i - 2] > a[i] -> a[i] = a[i - 1] // Set current to just above previous
                    a[i - 2] == a[i] -> a[i]++         // Increment if equal to element before previous
                    else -> {}                         // No change needed
                }
            }
        }
    }
    
    return true
}

fun main() {
    repeat(readInt()) { println(if (solve()) "YES" else "NO") }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }


// https://github.com/VaHiX/codeForces/