// Problem: CF 2120 A - Square of Rectangles
// https://codeforces.com/contest/2120/problem/A

/*
 * Problem: Aryan wants to arrange three rectangles into a square.
 *          Rectangles cannot be rotated, and must not overlap.
 *          
 * Algorithm:
 * 1. Calculate total area of all three rectangles.
 * 2. Check if total area is a perfect square; side length is sqrt(total_area).
 * 3. Try various arrangements where rectangles are aligned along edges to form a square.
 *    
 * Time Complexity: O(1) - constant time due to fixed number of rectangles and checks.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

fun canFormSquare(l1: Int, b1: Int, l2: Int, b2: Int, l3: Int, b3: Int): Boolean {
    val rects = listOf(Pair(l1, b1), Pair(l2, b2), Pair(l3, b3)) // Store rectangles as pairs
    val totalArea = l1 * b1 + l2 * b2 + l3 * b3 // Compute total area
    val side = kotlin.math.sqrt(totalArea.toDouble()).toInt() // Side of square
    if (side * side != totalArea) return false // If not a perfect square, impossible

    // Special case: all rectangles same orientation and fit perfectly
    if (b1 == b2 && b2 == b3 && l1 + l2 + l3 == side && b1 == side) return true
    if (l1 == l2 && l2 == l3 && b1 + b2 + b3 == side && l1 == side) return true

    // Try different arrangement patterns: check all permutations of rectangles as A, B, C
    for (i in rects.indices) {
        for (j in rects.indices) {
            if (i == j) continue
            val k = 3 - i - j // Remaining index for third rectangle
            val (lA, bA) = rects[i]
            val (lB, bB) = rects[j]
            val (lC, bC) = rects[k]

            // Check arrangement where A and B are placed horizontally side by side
            // and C is stacked vertically on top
            if (bA == bB && lA + lB == side && bA + bC == side && lC == side) return true
            
            // Check arrangement where A and B are stacked vertically
            // and C is placed horizontally next to them
            if (lA == lB && bA + bB == side && lA + lC == side && bC == side) return true
        }
    }
    return false // No valid arrangement found
}

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val input = readln().split(" ").map { it.toInt() }
        val l1 = input[0]
        val b1 = input[1]
        val l2 = input[2]
        val b2 = input[3]
        val l3 = input[4]
        val b3 = input[5]
        if (canFormSquare(l1, b1, l2, b2, l3, b3)) {
            println("YES")
        } else {
            println("NO")
        }
    }
}


// https://github.com/VaHiX/CodeForces/