// Problem: CF 1533 J - Pawns
// https://codeforces.com/contest/1533/problem/J

/*
 * J. Pawns
 *
 * Problem: Minimum number of white pawns to capture all black pawns on an infinite chessboard.
 * 
 * Algorithm:
 * - Sort pawns by y-coordinate (and then by x-coordinate for tie-breaking).
 * - For each parity (even/odd y), process the pawns and try to pair them up such that
 *   one white pawn can capture two pawns: one from above and one from below.
 * - Use greedy matching to minimize white pawns needed.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is number of pawns.
 * Space Complexity: O(n) for storing pawns and auxiliary arrays.
 */

import java.io.*
import java.util.*

object program {
    @JvmStatic
    fun main(args: Array<String>) {
        val inputStream = System.`in`
        val outputStream: OutputStream = System.out
        val `in` = InputReader(inputStream)
        val out = PrintWriter(outputStream)
        val solver = JPeshki()
        solver.solve(1, `in`, out)
        out.close()
    }
    
    internal class JPeshki {
        fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
            val n = `in`.nextInt()
            val pawns = arrayOfNulls<Pawn>(n)
            for (i in 0 until n) {
                pawns[i] = Pawn()
                pawns[i]!!.x = `in`.nextInt()
                pawns[i]!!.y = `in`.nextInt()
            }
            
            // Sort pawns by y-coordinate, then by x-coordinate
            Arrays.sort(pawns) { o1, o2 ->
                var z = Integer.compare(o1!!.y, o2!!.y)
                if (z == 0) {
                    z = Integer.compare(o1.x, o2.x)
                }
                z
            }
            
            var res = n // Initially assume we need n white pawns
            
            // Process both parities (even and odd y-coordinates)
            for (parity in 0..1) {
                var nthis = 0 // Count of pawns with this parity (y % 2 == parity)
                var nthat = 0 // Count of pawns with other parity (y % 2 != parity)
                val id = IntArray(n)
                
                for (i in 0 until n) {
                    if (pawns[i]!!.y % 2 == parity) {
                        id[i] = nthis++ // Assign index within same parity group
                    } else {
                        id[i] = nthat++ // Assign index within different parity group
                    }
                }
                
                val done = BooleanArray(n)
                var i = 0
                
                while (i < n) {
                    var j = i
                    // Find end of current y-level
                    while (j < n && pawns[j]!!.y == pawns[i]!!.y) ++j
                    
                    // Only process if this level has parity equal to the loop parity
                    if (pawns[i]!!.y % 2 == parity) {
                        // Find start of previous y-level (where pawns can attack)
                        var pi = i
                        while (pi > 0 && pawns[pi - 1]!!.y == pawns[i]!!.y - 1) --pi
                        
                        // Find end of next y-level
                        var nj = j
                        while (nj < n && pawns[nj]!!.y == pawns[i]!!.y + 1) ++nj
                        
                        var ptr = j - 1 // Pointer to previous y-level for matching
                        // Try to match pawns from current level with those in previous level
                        for (o in i - 1 downTo pi) {
                            if (!done[o]) {
                                while (ptr >= i && (done[ptr] || pawns[ptr]!!.x >= pawns[o]!!.x)) --ptr
                                if (ptr >= i) {
                                    --res // Reduce count of needed white pawns
                                    done[o] = true
                                    done[ptr] = true
                                }
                            }
                        }
                        
                        ptr = j // Pointer to next y-level for matching
                        // Try to match pawns from current level with those in next level
                        for (u in i until j) {
                            if (!done[u]) {
                                while (ptr < nj && (done[ptr] || pawns[ptr]!!.x <= pawns[u]!!.x)) ++ptr
                                if (ptr < nj) {
                                    --res // Reduce count of needed white pawns
                                    done[u] = true
                                    done[ptr] = true
                                }
                            }
                        }
                    }
                    i = j
                }
            }
            out.println(res)
        }
    }
    
    internal class InputReader(stream: InputStream?) {
        var reader: BufferedReader
        var tokenizer: StringTokenizer?
        
        operator fun next(): String {
            while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
                tokenizer =
                    try {
                        StringTokenizer(reader.readLine())
                    } catch (e: IOException) {
                        throw RuntimeException(e)
                    }
            }
            return tokenizer!!.nextToken()
        }
        
        fun nextInt(): Int {
            return next().toInt()
        }
        
        init {
            reader = BufferedReader(InputStreamReader(stream), 32768)
            tokenizer = null
        }
    }

    internal class Pawn {
        var x = 0
        var y = 0
    }
}


// https://github.com/VaHiX/codeForces/