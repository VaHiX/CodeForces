// Problem: CF 2118 E - Grid Coloring
// https://codeforces.com/contest/2118/problem/E

/*
E. Grid Coloring
Algorithm: 
    - For each cell in the grid, compute two metrics:
        1. Chessboard distance (max(abs(i - midX), abs(j - midY)))
        2. Manhattan distance (abs(i - midX) + abs(j - midY))
    - Sort all cells based on these two distances:
        - Primary key: chessboard distance
        - Secondary key: Manhattan distance
    - Output the sorted cell coordinates in order.

Time Complexity: O(n * m * log(n * m)) where n and m are grid dimensions.
Space Complexity: O(n * m) for storing the sequence of cells.

The solution uses a greedy approach with a custom sorting criterion to minimize 
penalties while coloring. By sorting based on the distance metrics, we ensure that 
cells further away from the previously colored cell receive penalties in an optimal order.
*/
import kotlin.math.*
fun main() {
    val reader = System.`in`.bufferedReader()
    val t = reader.readLine().trim().toInt()
    val ans = StringBuilder()
    repeat(t) {
        val parts = reader.readLine().trim().split(" ")
        val r = parts[0].toInt()
        val c = parts[1].toInt()
        val midX = r / 2   // Calculate center of the grid (for distance calculations)
        val midY = c / 2
        val seq = mutableListOf<IntArray>()
        for (i in 0 until r) {
            for (j in 0 until c) {
                val chb = max(abs(i - midX), abs(j - midY)) // Chessboard distance
                val mnn = abs(i - midX) + abs(j - midY)     // Manhattan distance
                seq.add(intArrayOf(chb, mnn, i + 1, j + 1)) // Store with coordinates
            }
        }
        seq.sortWith(compareBy({ it[0] }, { it[1] }))  // Sort using custom comparator
        for (v in seq) ans.append(v[2]).append(' ').append(v[3]).append('\n')  // Output result
    }
    print(ans.toString())
}


// https://github.com/VaHiX/CodeForces/