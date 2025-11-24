// Problem: CF 2159 B - Rectangles
// https://codeforces.com/contest/2159/problem/B

/*
Purpose: Find the minimum area of rectangles that can cover each cell in a binary grid.
Algorithms/Techniques: 
- Brute force enumeration of column pairs (x1, x2) 
- For each valid pair, scan rows to find valid rectangles (both corners are 1)
- Use dynamic programming to store and propagate minimum areas
- Transpose grid when m > n for optimization

Time Complexity: O(n * m^2) where n and m are grid dimensions
Space Complexity: O(n * m^2) for the DP table storing minimum areas for each cell and column pair

*/
import kotlin.math.min

fun main() {
    val out = StringBuilder()
    repeat(readln().toInt()) {
        val (n, m) = readln().split(" ").map(String::toInt)
        val grid = Array(n) { readln().map { it - '0' }.toIntArray() }
        if (m <= n) {
            val answer = solve(n, m, grid)
            answer.forEach { out.appendLine(it.joinToString(" ")) }
        } else {
            // Transpose the grid to reduce problem size when m > n
            val transpose = Array(m) { x -> IntArray(n) { y -> grid[y][x] } }
            val answer = solve(m, n, transpose)
            // Output transposed result back to original orientation
            for (y in 0 until n) {
                for (x in 0 until m) {
                    out.append(answer[x][y]).append(' ')
                }
                out.appendLine()
            }
        }
    }
    print(out)
}

fun solve(n: Int, m: Int, grid: Array<IntArray>): Array<IntArray> {
    // dp[y][x2][x1] stores minimum area of rectangle with left boundary x1 and right boundary x2 that covers cell (y, x2)
    val dp = Array(n) { Array(m) { IntArray(it + 1) { Int.MAX_VALUE } } }
    
    // Iterate over all column pairs (x1, x2) where x1 < x2
    for (x2 in 0 until m) {
        for (x1 in 0 until x2) {
            var last = -1
            // Scan rows to find valid rectangles (both corners 1)
            for (y in 0 until n) {
                if (grid[y][x1] == 1 && grid[y][x2] == 1) {
                    if (last != -1) {
                        // Calculate area of rectangle formed by (last, x1) and (y, x2)
                        val area = (y - last + 1) * (x2 - x1 + 1)
                        // Update dp table for all rows in rectangle interval [last, y]
                        for (yK in last..y) {
                            dp[yK][x2][x1] = min(dp[yK][x2][x1], area)
                        }
                    }
                    last = y
                }
            }
        }
    }
    
    // Propagate minimum areas within same row to fill gaps
    for (y in 0 until n) {
        for (x1 in 0 until m) {
            for (x2 in m - 1 downTo x1) {
                if (x1 > 0) {
                    // Propagate minimum from left
                    dp[y][x2][x1] = min(dp[y][x2][x1], dp[y][x2][x1 - 1])
                }
                if (x2 < m - 1) {
                    // Propagate minimum from right
                    dp[y][x2][x1] = min(dp[y][x2][x1], dp[y][x2 + 1][x1])
                }
            }
        }
    }
    
    // Prepare final output grid: dp[y][x][x] means minimal area covering (y,x) in x column interval
    return Array(n) { y -> IntArray(m) { x -> if (dp[y][x][x] == Int.MAX_VALUE) 0 else dp[y][x][x] } }
}


// https://github.com/VaHiX/CodeForces/