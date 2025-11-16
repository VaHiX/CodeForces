// Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
// https://codeforces.com/contest/2127/problem/B

/*
 * Problem: B. Hamiiid, Haaamid... Hamid?
 * Purpose: Determine the minimum number of days Hamid needs to escape a 1×n grid,
 *          where Mani builds walls optimally to delay Hamid's escape and Hamid
 *          moves optimally to escape as soon as possible.
 *
 * Algorithm:
 * - Simulate both players' optimal strategies for each test case:
 *   - Mani always places a wall in an empty cell that maximizes the escape time.
 *   - Hamid always chooses a direction to move that minimizes the escape time.
 * - Preprocess: 
 *   - Convert string to array of 0s and 1s indicating empty (0) or occupied (1) cells.
 *   - Find the nearest wall to the left and right of Hamid's current position.
 * - Time Complexity: O(n) per test case, since each cell is visited at most once in the loops.
 * - Space Complexity: O(n) for storing the array representation of the grid.
 */

fun main() {
    val t = readln().toInt()
    repeat(t) {
        // Read n (grid size) and x (initial pos of Hamid)
        val (n, x) = readln().split(" ").map { it.toInt() }
        
        // Read the string representing the initial state of grid
        val s = readln()
        
        // Convert string to IntArray where 1 = wall, 0 = empty space
        val a = IntArray(n) { if (s[it] == '#') 1 else 0 }
        
        // Calculate total number of walls in the grid
        val sum = a.sum()
        
        // If Hamid is at a corner or there are no walls, he can escape immediately
        if (x == 1 || x == n || sum == 0) {
            println(1)
            return@repeat
        }
        
        // Find the nearest wall to the left of Hamid's position (0-indexed)
        var l = x - 1
        while (l >= 0 && a[l] == 0) l--
        
        // Find the nearest wall to the right of Hamid's position (0-indexed)
        var r = x - 1
        while (r < n && a[r] == 0) r++
        
        // Check conditions and decide the optimal escape strategy
        
        if (l == -1) {
            // No wall on the left side
            if (x - 1 > n - r) {
                // Escape from the right is better
                println(n - r + 1)
            } else {
                // Escape from the left is better or equal
                println(x)
            }
        } else if (r == n) {
            // No wall on the right side
            if (n - x > l + 1) {
                // Escape from the left is better
                println(l + 2)
            } else {
                // Escape from the right is better or equal
                println(n - x + 1)
            }
        } else {
            // There are walls on both sides
            if (l + 1 == n - r) {
                // Both distances are equal, choose any
                println(l + 2)
            } else if (l + 1 < n - r) {
                // Left distance is smaller; compare escape paths from left vs right
                if (x - 1 > n - r) {
                    println(n - r + 1)
                } else {
                    println(x)
                }
            } else {
                // Right distance is smaller
                if (l + 1 > n - x) {
                    println(n - x + 1)
                } else {
                    println(l + 2)
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/