// Problem: CF 2146 D2 - Max Sum OR (Hard Version)
// https://codeforces.com/contest/2146/problem/D2

/*
 * Problem: D2. Max Sum OR (Hard Version)
 * Purpose: Given interval [l, r], reorder array a to maximize sum of bitwise ORs 
 *          between elements of a and b (b = [l, l+1, ..., r])
 * Algorithms:
 *   - Compute maximum possible OR sum using bit counting techniques
 *   - Pair elements optimally using recursive interval partitioning
 * Time Complexity: O(30 * n) where n = r - l + 1
 * Space Complexity: O(n) for storing intermediate results and recursion stack
 */

import java.io.*;
import java.util.*;

public class ORMaximizer {
    private static void pairInterval(int left, int right, Map<Integer, Integer> partnerMap) {
        if (left > right) return;
        if (left == right) {
            partnerMap.put(left, left);
            return;
        }
        int length = right - left + 1;
        int bitCut = -1;
        // Find the highest bit where both 0s and 1s appear in range
        for (int b = 30; b >= 0; b--) {
            long mask = 1L << b;
            if (mask > right) continue;
            // Count how many 1-bits exist at position b in [left, right]
            long onesRight = ((right + 1) / (mask << 1)) * mask + Math.max(0L, (right + 1) % (mask << 1) - mask);
            long onesLeft = (left / (mask << 1)) * mask + Math.max(0L, left % (mask << 1) - mask);
            long count1 = onesRight - onesLeft;
            long count0 = length - count1;
            if (count0 > 0 && count1 > 0) {
                bitCut = b;
                break;
            }
        }
        // If no such bit found, pair elements directly
        if (bitCut == -1) {
            List<Integer> arr = new ArrayList<>();
            for (int i = left; i <= right; i++) arr.add(i);
            if (arr.size() % 2 == 1) {
                int rem = arr.remove(arr.size() - 1);
                partnerMap.put(rem, rem);
            }
            for (int i = 0; i < arr.size(); i += 2) {
                int a = arr.get(i), b = arr.get(i + 1);
                partnerMap.put(a, b);
                partnerMap.put(b, a);
            }
            return;
        }
        // Divide into two groups based on bitCut
        int pivotMask = 1 << bitCut;
        List<Integer> group0 = new ArrayList<>(), group1 = new ArrayList<>();
        for (int val = left; val <= right; val++) {
            if ((val & pivotMask) == 0) group0.add(val);
            else group1.add(val);
        }
        // Match elements in sorted groups optimally
        if (group0.size() <= group1.size()) {
            group0.sort(Collections.reverseOrder());
            Collections.sort(group1);
            for (int i = 0; i < group0.size(); i++) {
                int a = group0.get(i), b = group1.get(i);
                partnerMap.put(a, b);
                partnerMap.put(b, a);
            }
            if (group0.size() < group1.size()) {
                pairInterval(group1.get(group0.size()), group1.get(group1.size() - 1), partnerMap);
            }
        } else {
            Collections.sort(group0);
            Collections.sort(group1);
            for (int i = 0; i < group1.size(); i++) {
                int a = group0.get(group0.size() - 1 - i), b = group1.get(i);
                partnerMap.put(a, b);
                partnerMap.put(b, a);
            }
            if (group0.size() > group1.size()) {
                pairInterval(group0.get(0), group0.get(group0.size() - group1.size() - 1), partnerMap);
            }
        }
    }

    private static long computeMax(int l, int r) {
        long len = (long) r - l + 1;
        long res = 0;
        // For each bit position, calculate optimal contribution to sum
        for (int bit = 0; bit < 30; bit++) {
            long mask = 1L << bit;
            long onesR = ((r + 1) / (mask << 1)) * mask + Math.max(0L, (r + 1) % (mask << 1) - mask);
            long onesL = (l / (mask << 1)) * mask + Math.max(0L, l % (mask << 1) - mask);
            long cnt1 = onesR - onesL;
            res += (cnt1 * 2 >= len ? len : 2 * cnt1) * mask;
        }
        return res;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int tests = Integer.parseInt(in.readLine().trim());
        StringBuilder sb = new StringBuilder();
        while (tests-- > 0) {
            String[] tokens = in.readLine().split(" ");
            int l = Integer.parseInt(tokens[0]);
            int r = Integer.parseInt(tokens[1]);
            // Compute maximum sum
            sb.append(computeMax(l, r)).append("\n");
            Map<Integer, Integer> partnerMap = new HashMap<>();
            // Generate optimal pairing
            pairInterval(l, r, partnerMap);
            for (int x = l; x <= r; x++) {
                sb.append(partnerMap.get(x)).append(" ");
            }
            sb.append("\n");
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/CodeForces/