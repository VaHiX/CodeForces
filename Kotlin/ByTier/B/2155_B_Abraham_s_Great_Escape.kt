// Problem: CF 2155 B - Abraham's Great Escape
// https://codeforces.com/contest/2155/problem/B

/**
 * B. Abraham's Great Escape
 *
 * Problem Description:
 * Given an n x n grid and a number k, construct a grid where exactly k starting cells allow Abraham to escape.
 * An arrow in each cell forces movement in that direction. If movement leads outside the grid, he escapes.
 *
 * Algorithm/Approach:
 * - The solution builds a pattern that controls how many cells lead to escape.
 * - First, handle impossible cases: if k = n² - 1, it's impossible because we need at least one cell
 *   that cannot escape (i.e., leads into a loop or another valid escape).
 * - Build a grid with specific arrow patterns:
 *   - Start by placing 'U' in all cells.
 *   - If k > 0 and there are remaining cells to mark for escape, use 'U' moves to create 
 *     paths leading out (by moving up from lower rows).
 *   - Then alternate between 'R' and 'L' or 'D' for other rows to control how many escape.
 *   - Special handling of row n-1 to ensure proper escaping and non-looping behavior.
 *
 * Time Complexity: O(n²) per test case — we iterate through the grid once to place arrows.
 * Space Complexity: O(n²) — used to store the output grid as strings.
 */
fun solve() {
    val (n, k0) = readLine()!!.split(" ").map { it.toInt() }
    var k = k0
    if ((n * n - 1) == k) {
        println("NO")
        return
    }
    println("YES")
    for (i in 0 until n) {
        val sb = StringBuilder()
        if (k > 0) {
            var j = 0
            while (j < n && k > 0) {
                sb.append('U') // Fill current row with 'U' arrows to allow upward escape paths
                k-- // Decrement remaining escape count
                j++
            }
            if (j < n) {
                if (i == n - 1) {
                    // At last row, ensure correct pattern for escaping
                    while (j < n - 1) {
                        sb.append('R')
                        j++
                    }
                    sb.append('L') // End with 'L' to avoid escape loops
                } else {
                    // For other rows before last, fill rest with 'D' to allow more escape options
                    while (j < n) {
                        sb.append('D')
                        j++
                    }
                }
            }
        } else {
            // No more escapes needed. Fill row completely with 'R' and end with 'L'
            for (j in 0 until n - 1) {
                sb.append('R')
            }
            sb.append('L')
        }
        println(sb.toString())
    }
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/