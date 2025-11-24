// Problem: CF 2150 A - Incremental Path
// https://codeforces.com/contest/2150/problem/A

/*
A. Incremental Path
Algorithms/Techniques: Simulation with Set-based tracking of black cells
Time Complexity: O(n * m + k * log k), where n is the length of string s, m is the number of initial black cells, and k is the final number of black cells.
Space Complexity: O(m + k), for storing initial black cells and final black cells.

The problem simulates a process where multiple people follow commands on a strip of cells,
starting from cell 1. Each person follows a prefix of the command string s, and after
executing all commands in that prefix, colors the last visited cell black (if it wasn't already).
We track all black cells and output them sorted at the end.
*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.*
import kotlin.system.exitProcess

val inf = BufferedReader(InputStreamReader(System.`in`))
val ouf = PrintWriter(System.out)

fun BufferedReader.readInt() = readLine()!!.toInt()
fun BufferedReader.readInts() = readLine()!!.split(' ').map(String::toInt)
fun BufferedReader.readLong() = readLine()!!.toLong()
fun BufferedReader.readLongs() = readLine()!!.split(' ').map(String::toLong)
fun BufferedReader.readString() = readLine()!!

const val INF = Long.MAX_VALUE / 3

fun solve() {
    val (n, m) = inf.readInts()
    val s = inf.readString()
    val a = inf.readInts().toMutableSet() // Set of initially black cells
    var cur = 1 // Current position, starts at cell 1
    
    for (c in s) {
        when (c) {
            'A' -> {
                cur++ // Move to next cell
            }
            'B' -> {
                cur++
                // Skip all black cells until we find a white one
                while (cur in a) cur++
            }
        }
        a.add(cur) // Color the final position black
        if (c == 'B') {
            // After executing B command, ensure that cur is not in black set
            while (cur in a) cur++
        }
    }
    
    ouf.println(a.size)
    ouf.println(a.sorted().joinToString(separator = " "))
}

fun main() {
    try {
        for (t in 1..inf.readLine()!!.toInt())
            solve()
    } catch (e: Exception) {
        e.printStackTrace()
        exitProcess(1)
    }
    ouf.close()
}


// https://github.com/VaHiX/CodeForces/