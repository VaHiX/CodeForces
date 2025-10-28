// Problem: CF 2101 A - Mex in the Grid
// https://codeforces.com/contest/2101/problem/A

/*
 * Magical Spiral Grid Generator
 *
 * Purpose:
 * This code generates a spiral pattern in an n x n grid starting from the center,
 * filling values from 0 to n^2 - 1 in a specific order. The algorithm simulates
 * a clockwise spiral traversal starting from either the center (for odd n) or
 * the top-left of the center (for even n).
 *
 * Algorithm:
 * - Start at the center of the grid.
 * - Move in four directions: right, down, left, up, alternating step count.
 * - Fill each unvisited cell with increasing values from 0 to n^2 - 1.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val numberOfTestCases = scanner.nextInt()   
    for (i in 0 until numberOfTestCases) {      
        magicalSpiral(scanner)
    }
}

fun magicalSpiral(scanner: Scanner) {
    val n = scanner.nextInt()   
    val arr = Array(n) { IntArray(n) { -1 } } // Initialize grid with -1 to mark unvisited cells
    var x: Int
    var y: Int
    if (n % 2 == 0) {
        x = n / 2 - 1 // For even n, start at the top-left of center
        y = n / 2 - 1
    } else {
        x = n / 2 // For odd n, start at exact center
        y = n / 2
    }
    arr[x][y] = 0 // Mark the starting position as 0
    var value = 1 // Start filling values from 1
    var step = 1 // Number of steps to take in each direction
    
    val dir = arrayOf(  // Direction vectors: right, down, left, up
        intArrayOf(0, 1),   
        intArrayOf(1, 0),   
        intArrayOf(0, -1),  
        intArrayOf(-1, 0)   
    )
    
    while (value < n * n) { // Continue until all cells are filled
        for (d in 0..3) { // Traverse each of the four directions
            val dx = dir[d][0]
            val dy = dir[d][1]
            val steps = step // Number of steps to take in this direction
            
            if (d % 2 == 1) step++ // Increase step count after moving down and left
            
            for (i in 0 until steps) {
                x += dx
                y += dy
                
                // If the new position is valid and unvisited, fill it with current value
                if (x in 0 until n && y in 0 until n && arr[x][y] == -1) {
                    arr[x][y] = value
                    value++
                }
                
                if (value >= n * n) break // Stop early if all values are filled
            }
            
            if (value >= n * n) break // Stop early if all values are filled
        }
    }
    
    for (row in arr) {
        println(row.joinToString(" ")) // Print the final grid
    }
    println()
}


// https://github.com/VaHiX/CodeForces/