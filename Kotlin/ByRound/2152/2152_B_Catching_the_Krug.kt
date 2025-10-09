// Problem: CF 2152 B - Catching the Krug
// https://codeforces.com/contest/2152/problem/B

/**
 * Problem: Catching the Krug
 *
 * Purpose:
 *   This code determines the maximum number of turns the Krug can survive against Doran,
 *   given optimal play from both players on an n x n grid, where Doran starts first and
 *   tries to catch the Krug while the Krug aims to evade as long as possible. The survival 
 *   time is represented by the number of Doran's turns until he catches the Krug, or -1 if
 *   the Krug can survive forever.
 *
 * Algorithms & Techniques:
 *   - Binary search on answer: We perform binary search over the possible survival times
 *     to find the maximum safe distance (manhattan radius) such that the Krug can survive.
 *   - Manhatten distance logic and reachability validation using bounding constraints.
 *   - Grid boundary clamping and movement tracking for both players.
 *
 * Time Complexity:
 *   O(log(n) * n) per test case due to binary search over possible distances (log n),
 *   and verification step involving constant number of checks (~8 for corners/edges).
 *
 * Space Complexity:
 *   O(1) as we use only a fixed amount of variables and data structures regardless of input size.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
typealias Lng = Long
@Suppress("NOTHING_TO_INLINE")
private inline fun Lng.absoluteValue() = if (this < 0) -this else this
@Suppress("NOTHING_TO_INLINE")
private inline infix fun Lng.withinBounds(limit: Lng) = this in 0L..limit
private inline fun verifyConfiguration(
    gridSize: Lng,
    originRow: Lng,
    originCol: Lng,
    targetRow: Lng,
    targetCol: Lng,
    manhattanRadius: Lng
): Boolean {
    val targetRowMin = targetRow - manhattanRadius // Minimum row of valid target region
    val targetRowMax = targetRow + manhattanRadius // Maximum row of valid target region
    val targetColMin = targetCol - manhattanRadius // Minimum column of valid target region
    val targetColMax = targetCol + manhattanRadius // Maximum column of valid target region
    
    val isInsideTarget: (Lng, Lng) -> Boolean = { row, col ->
        row in targetRowMin..targetRowMax && col in targetColMin..targetColMax // Check if coordinate lies within the target area
    }
    
    val boundaryPoints = mutableListOf<Pair<Lng, Lng>>() // Stores points that are reachable but may be outside forbidden area
    
    val addIfReachable: (Lng, Lng) -> Unit = lambda@{ row, col ->
        val clampedRow = row.coerceIn(0L, gridSize) // Clamp row to grid bounds [0, gridSize]
        val clampedCol = col.coerceIn(0L, gridSize) // Clamp column to grid bounds [0, gridSize]
        if ((clampedRow - originRow).absoluteValue() + 
            (clampedCol - originCol).absoluteValue() <= manhattanRadius) {
            boundaryPoints.add(clampedRow to clampedCol) // Add valid reachable point
        }
    }
    
    // Check for reachable edge points from all four directions along the radius
    if (originRow - manhattanRadius withinBounds gridSize) 
        addIfReachable(originRow - manhattanRadius, originCol)
    if (originRow + manhattanRadius withinBounds gridSize) 
        addIfReachable(originRow + manhattanRadius, originCol)
    if (originCol - manhattanRadius withinBounds gridSize) 
        addIfReachable(originRow, originCol - manhattanRadius)
    if (originCol + manhattanRadius withinBounds gridSize) 
        addIfReachable(originRow, originCol + manhattanRadius)
    
    // Check for corners where row or column matches edge of grid
    sequenceOf(0L, gridSize).forEach { edgeRow ->
        val rowDelta = (edgeRow - originRow).absoluteValue() // Distance from edge to origin row
        if (rowDelta <= manhattanRadius) {
            val remainingSteps = manhattanRadius - rowDelta // Remaining steps in the other direction allowed by radius
            val leftCol = (originCol - remainingSteps).coerceIn(0L, gridSize) // Clamp column on left
            val rightCol = (originCol + remainingSteps).coerceIn(0L, gridSize) // Clamp column on right
            addIfReachable(edgeRow, leftCol) // Check leftmost reachable point at edgeRow
            addIfReachable(edgeRow, rightCol) // Check rightmost reachable point at edgeRow
        }
    }
    
    sequenceOf(0L, gridSize).forEach { edgeCol ->
        val colDelta = (edgeCol - originCol).absoluteValue() // Distance from edge to origin column
        if (colDelta <= manhattanRadius) {
            val remainingSteps = manhattanRadius - colDelta // Remaining steps in the other direction allowed by radius
            val topRow = (originRow - remainingSteps).coerceIn(0L, gridSize) // Clamp row at top
            val bottomRow = (originRow + remainingSteps).coerceIn(0L, gridSize) // Clamp row at bottom
            addIfReachable(topRow, edgeCol) // Check upper reachable point at edgeCol
            addIfReachable(bottomRow, edgeCol) // Check lower reachable point at edgeCol
        }
    }
    
    // Add the four corner points of the grid explicitly
    arrayOf(0L to 0L, 0L to gridSize, gridSize to 0L, gridSize to gridSize)
        .forEach { (r, c) -> addIfReachable(r, c) }
    
    // Return true if none of the possible boundary points lie outside the target area (valid configuration).
    return boundaryPoints.none { (r, c) -> !isInsideTarget(r, c) }
}

fun main() = with(BufferedReader(InputStreamReader(System.`in`))) {
    val output = PrintWriter(System.out, false)
    generateSequence { readLine()?.toIntOrNull() }
        .first()
        .let { testCases ->
            repeat(testCases) {
                readLine()!!.split(' ').map(String::toLong).let { params ->
                    val (gridSize, startRow, startCol, destRow, destCol) = params
                    var lowerBound = 0L
                    var upperBound = gridSize.shl(1) // Shifting left by 1 == multiply by 2 == max possible distance
                    var result = -1L // Default value indicating infinite survival time
                    
                    while (lowerBound <= upperBound) {
                        val midpoint = lowerBound.plus(upperBound).shr(1) // Right-shift by 1 == divide by 2 == binary search midpoint
                        
                        when {
                            verifyConfiguration(gridSize, startRow, startCol, 
                                              destRow, destCol, midpoint) -> { // Try to assign the current mid as minimum safe radius
                                result = midpoint
                                upperBound = midpoint.dec() // Reduce upper bound to find smaller radius that works
                            }
                            else -> lowerBound = midpoint.inc() // Increase lower bound because such a radius wouldn't work
                        }
                    }
                    output.println(result)
                }
            }
        }
    output.flush()
}


// https://github.com/VaHiX/CodeForces/