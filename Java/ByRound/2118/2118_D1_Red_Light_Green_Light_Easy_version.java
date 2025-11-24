// Problem: CF 2118 D1 - Red Light, Green Light (Easy version)
// https://codeforces.com/contest/2118/problem/D1

/**
 * Problem: Red Light, Green Light (Easy version)
 * 
 * Purpose: Simulate a traveler moving on a strip of length 10^15, facing red/green traffic lights.
 *          For each starting position, determine if the traveler will eventually leave the strip within 10^100 seconds.
 *
 * Algorithm/Techniques:
 * - Simulation with cycle detection using HashSet
 * - TreeMap for efficient ceiling/floor lookups of next traffic light position
 * - Direction tracking (1 for right, -1 for left) to simulate movement
 * - Time modulo k to determine if a light is red at a given time
 *
 * Time Complexity: O(n * log n + q * n * log n) where n is number of lights and q is number of queries.
 * Space Complexity: O(n) for TreeMap and HashSet storage
 */
import java.util.*;
public class RedLightGreenLight {
    static class Node {
        long x;
        int dir, mod;
        Node(long a, int b, int c) { x = a; dir = b; mod = c; }
        public boolean equals(Object o) {
            if (!(o instanceof Node)) return false;
            Node n = (Node) o;
            return x == n.x && dir == n.dir && mod == n.mod;
        }
        public int hashCode() { return Objects.hash(x, dir, mod); }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- > 0) {
            int n = in.nextInt();
            int k = in.nextInt();
            long[] posArr = new long[n];
            int[] colorArr = new int[n];
            for (int i = 0; i < n; i++) posArr[i] = in.nextLong(); // Read positions
            for (int i = 0; i < n; i++) colorArr[i] = in.nextInt(); // Read delays
            TreeMap<Long, Integer> map = new TreeMap<>();
            long minX = Long.MAX_VALUE, maxX = Long.MIN_VALUE;
            for (int i = 0; i < n; i++) {
                map.put(posArr[i], colorArr[i]); // Map positions to delays
                minX = Math.min(minX, posArr[i]);
                maxX = Math.max(maxX, posArr[i]);
            }
            int q = in.nextInt();
            for (int i = 0; i < q; i++) {
                long st = in.nextLong(); // Read query start position
                System.out.println(run(st, k, map, minX, maxX)); // Run simulation
            }
        }
        in.close();
    }
    static String run(long start, int cycle, TreeMap<Long, Integer> map, long minX, long maxX) {
        long cur = start;
        int dir = 1; // Direction: 1 means right, -1 means left
        long time = 0;
        Set<Node> seen = new HashSet<>(); // To detect cycles in state (pos, direction, time_mod)
        while (true) {
            if (cur < minX || cur > maxX) return "YES"; // If out of bounds, exit the strip
            Node node = new Node(cur, dir, (int)(time % cycle)); // Create current state for cycle detection
            if (!seen.add(node)) return "NO"; // If already visited this state, loop detected
            if (map.containsKey(cur)) { // Check if there's a traffic light at current position
                int val = map.get(cur); // Get delay of the light
                if (time % cycle == val) { // If time is red for this light, turn around
                    dir *= -1;
                }
            }
            Map.Entry<Long, Integer> nxt; // Find next traffic light
            if (dir == 1)
                nxt = map.ceilingEntry(cur + 1); // Next on the right
            else
                nxt = map.floorEntry(cur - 1); // Next on the left
            long nxtPos;
            if (nxt == null) {
                return "YES"; // No more lights in direction of movement, exit possible
            } else {
                nxtPos = nxt.getKey(); // Get next position
            }
            long dist = Math.abs(nxtPos - cur); // Distance to move
            time += dist; // Update total time
            cur = nxtPos; // Move to next position
        }
    }
}


// https://github.com/VaHiX/CodeForces/