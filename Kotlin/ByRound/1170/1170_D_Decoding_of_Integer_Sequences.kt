// Problem: CF 1170 D - Decoding of Integer Sequences
// https://codeforces.com/contest/1170/problem/D

/**
 * Decodes a sequence that was encoded using a specific interleaving method.
 * 
 * Algorithm:
 * 1. Parse input to determine number of sequences (k) by counting -1 markers.
 * 2. Initialize k empty sequences and a queue to track which sequences are still active.
 * 3. Process each number in the input:
 *    - Take the first sequence from the queue.
 *    - Add the number to that sequence.
 *    - If the number is not -1, add the sequence index back to the queue.
 * 4. Output the decoded sequences, excluding the trailing -1.
 * 
 * Time Complexity: O(m), where m is the length of the encoded sequence.
 * Space Complexity: O(m), for storing the input and sequences.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.ArrayDeque
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val m = br.readLine().trim().toInt()
  val st = StringTokenizer(br.readLine())
  val numbers = IntArray(m)
  var k = 0
  for (i in 0 until m) {
    numbers[i] = st.nextToken().toInt()
    if (numbers[i] == -1) k++
  }
  val seqs = Array(k) { mutableListOf<Int>() }
  val q = ArrayDeque<Int>(k)
  repeat(k) { q.addLast(it) }
  for (v in numbers) {
    val row = q.removeFirst() // Get the sequence index that the value belongs to
    seqs[row].add(v)
    if (v != -1) q.addLast(row) // If not end marker, re-add sequence index to queue
  }
  val out = StringBuilder()
  out.appendLine(k)
  for (lst in seqs) {
    out.append(lst.size - 1) // The size minus 1, as the last element is -1
    for (i in 0 until lst.size - 1) {
      out.append(' ').append(lst[i])
    }
    out.appendLine()
  }
  print(out)
}


// https://github.com/VaHiX/CodeForces/