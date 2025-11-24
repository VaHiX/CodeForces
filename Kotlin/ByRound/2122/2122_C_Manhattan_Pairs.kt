// Problem: CF 2122 C - Manhattan Pairs
// https://codeforces.com/contest/2122/problem/C

/*
C. Manhattan Pairs
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing points and order list

The problem is to pair n (even) points on a 2D plane such that the sum of Manhattan distances
between paired points is maximized. The Manhattan distance between two points (x1, y1) and (x2, y2)
is |x1 - x2| + |y1 - y2|.

Key idea:
- For maximizing sum of absolute differences, we want to pair points that are as far apart as possible
  in both x and y coordinates.
- Sort all points by x-coordinate to group close x-values together.
- Split the sorted list into two halves.
- Within each half, sort by y-coordinate to ensure pairing elements with large differences in y.
- Pair first half's elements with second half's elements in reverse order to maximize Manhattan distance.

This greedy approach ensures that we are making locally optimal choices
that lead to a globally optimal solution for the Manhattan distance maximization.
*/

fun main() {
    val br = System.`in`.bufferedReader()
    val bw = System.out.bufferedWriter()
    val t = br.readLine().toInt()
    repeat(t) {
        val n = br.readLine().toInt()
        val x = IntArray(n)
        val y = IntArray(n)
        repeat(n) { i ->
            val (xi, yi) = br.readLine().split(' ').map{it.toInt()}
            x[i] = xi
            y[i] = yi
        }
        val order = MutableList(n) { it } // Create a list of point indices
        order.sortBy { x[it] } // Sort by x-coordinate to group similar x-values together
        val half = n / 2
        order.subList(0, half).sortBy { y[it] } // Sort first half by y-coordinate
        order.subList(half, n).sortBy { y[it] } // Sort second half by y-coordinate
        for (i in 0 until half) {
            bw.append("${order[i] + 1} ${order[n - 1 - i] + 1}\n") // Pair elements to maximize Manhattan distance
        }
    }
    bw.flush()
    bw.close()
}


// https://github.com/VaHiX/CodeForces/