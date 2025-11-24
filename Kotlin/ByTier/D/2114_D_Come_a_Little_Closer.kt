// Problem: CF 2114 D - Come a Little Closer
// https://codeforces.com/contest/2114/problem/D

/**
 * Problem: D. Come a Little Closer
 *
 * Purpose:
 *   Given n monsters on a large grid (10^9 x 10^9), we can move at most one monster to an empty cell,
 *   then select a rectangle that covers all remaining monsters. The goal is to minimize the area of this rectangle.
 *
 * Algorithm:
 *   - For each point, compute the minimum rectangle that contains all points.
 *   - Try moving one monster and recompute minimal enclosing rectangle after move.
 *   - Preprocess max/min coordinates along with second-best values for efficient computation.
 *   - Consider all possible optimal rectangles formed by the original set of points, potentially
 *     improved by moving one point.
 *
 * Time Complexity:
 *   O(n) per test case due to preprocessing and single pass logic; total over all test cases is bounded by 2*10^5
 *
 * Space Complexity:
 *   O(n) for storing the monster positions and auxiliary data structures
 */

import kotlin.math.min

const val INF = 1_000_000_000 + 5;

private fun readStr() = readln() 
private fun readInt() = readStr().toInt() 
private fun readStrings() = readStr().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 

/**
 * Updates two values (first, second) such that first >= second in the order defined by comparator.
 * Useful for tracking max and second max or min and second min efficiently.
 */
private fun consider(value: Int, first: Int, second: Int, comparator: Comparator<Int>): Pair<Int, Int> {
    return when {
        comparator.compare(value, first) >= 0 -> value to first
        comparator.compare(value, second) > 0 -> first to value
        else -> first to second
    }
}

val bigger = { a : Int, b : Int -> a.compareTo(b) } // Ascending order
val smaller = { a : Int, b : Int -> b.compareTo(a) } // Descending order

private fun solve(test: Int) {
    val n = readInt()
    val (x, y) = readInts()
    val arr = mutableListOf(x to y);
    if (n == 1) {
        println("1");
        return;
    }
    var maxx : Int = x
    var minx : Int = x
    var maxy : Int = y;
    var miny : Int = y;
    var maxx2 : Int = -INF; // Second largest x
    var minx2 : Int = INF;  // Second smallest x
    var maxy2 : Int = -INF; // Second largest y
    var miny2 : Int = INF;  // Second smallest y
    
    repeat (n - 1) {
        val (x, y) = readInts()
        arr.add(x to y);
        // Update maximum x and second maximum x
        val (newmaxx, newmaxx2) = consider(x, maxx, maxx2, bigger);
        maxx = newmaxx;
        maxx2 = newmaxx2;
        // Update minimum x and second minimum x
        val (newminx, newminx2) = consider(x, minx, minx2, smaller);
        minx = newminx;
        minx2 = newminx2;
        // Update maximum y and second maximum y
        val (newmaxy, newmaxy2) = consider(y, maxy, maxy2, bigger);
        maxy = newmaxy;
        maxy2 = newmaxy2;
        // Update minimum y and second minimum y
        val (newminy, newminy2) = consider(y, miny, miny2, smaller);
        miny = newminy;
        miny2 = newminy2;
    }
    
    var best = 1L * INF * INF; // Initialize with a large value
    
    for ((x, y) in arr) {
        // Compute the dimensions of the rectangle if we exclude this point
        val up = if (x == maxx) maxx2 else maxx;       // Max x excluding current x
        val down = if (x == minx) minx2 else minx;     // Min x excluding current x
        val right = if (y == maxy) maxy2 else maxy;    // Max y excluding current y
        val left = if (y == miny) miny2 else miny;     // Min y excluding current y
        
        val height = up - down + 1;
        val width = right - left + 1;
        val ans = 1L * width * height;
        
        // If area is less than total monster count, it's better to adjust one dimension
        if (ans < n) {
            best = min(best, min(1L * (width + 1) * height, 1L * width * (height + 1)))
        } else {
            best = min(best, ans)
        }
    }
    
    println(best);
}

fun main() {
    val t = readInt()
    for (i in 0 until t) {
        solve(i);
    }
}


// https://github.com/VaHiX/CodeForces/