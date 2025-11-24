// Problem: CF 2136 D - For the Champion
// https://codeforces.com/contest/2136/problem/D

/**
 * Problem: D. For the Champion
 * 
 * Purpose: This program finds the initial coordinates (X, Y) of a robot on an infinite 2D plane,
 *          given n anchor points. The robot can make up to 10 moves in four directions (U, D, L, R)
 *          and receives feedback as the minimum Manhattan distance to any anchor point after each move.
 * 
 * Algorithm: The approach uses coordinate transformation based on the properties of Manhattan distance.
 *            By moving in specific patterns and analyzing the distances returned, we can compute:
 *            - A = max(x_i + y_i) among all anchors
 *            - B = max(x_i - y_i) among all anchors
 *            Then we perform strategic moves to get S1 and S2 values that let us compute X and Y.
 * 
 * Time Complexity: O(n) per test case for pre-processing + O(1) for solving each query.
 * Space Complexity: O(n) for storing anchor points.
 * 
 * Techniques: Interactive problem solving, Manhattan distance properties, coordinate transformation.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer
import kotlin.system.exitProcess
import kotlin.math.max

fun ask(out: PrintWriter, dir: Char, k: Long, br: BufferedReader): Long {
    out.println("? $dir $k")
    out.flush()
    val line = br.readLine() ?: exitProcess(0)
    val s = line.toLongOrNull() ?: exitProcess(0)
    if (s == -1L) exitProcess(0)
    return s
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val out = PrintWriter(System.out, false)
    val tLine = br.readLine() ?: return
    val t = tLine.toIntOrNull() ?: return
    repeat(t) {
        val nLine = br.readLine() ?: return
        val n = nLine.toInt()
        val x = LongArray(n)
        val y = LongArray(n)
        repeat(n) { i ->
            val st = StringTokenizer(br.readLine())
            x[i] = st.nextToken().toLong()
            y[i] = st.nextToken().toLong()
        }
        var A = Long.MIN_VALUE
        var B = Long.MIN_VALUE
        for (i in 0 until n) {
            A = max(A, x[i] + y[i])      // Compute maximum of x+y for all anchors
            B = max(B, x[i] - y[i])      // Compute maximum of x-y for all anchors
        }
        val K = 1_000_000_000L
        // First set of moves to get s_pp (distance when moving up+right)
        ask(out, 'R', K, br)
        ask(out, 'R', K, br)
        ask(out, 'U', K, br)
        val s_pp = ask(out, 'U', K, br)   // Distance after U 1e9, R 2*1e9
        // Second set of moves to get s_pn (distance when moving down+right) 
        ask(out, 'D', K, br)
        ask(out, 'D', K, br)
        ask(out, 'D', K, br)
        val s_pn = ask(out, 'D', K, br)   // Distance after D 3*1e9, R 1e9
        // Calculate S1 and S2 using the transformations derived from Manhattan distance properties
        val S1 = s_pp - 4L * K + A          // Transformation to get x+y coordinate
        val S2 = s_pn - 4L * K + B          // Transformation to get x-y coordinate
        // Calculate final coordinates (X, Y) using system of equations derived from transformations
        val X = (S1 + S2) / 2               // X = (S1 + S2)/2 
        val Y = (S1 - S2) / 2               // Y = (S1 - S2)/2
        out.println("! $X $Y")
        out.flush()
    }
}


// https://github.com/VaHiX/CodeForces/