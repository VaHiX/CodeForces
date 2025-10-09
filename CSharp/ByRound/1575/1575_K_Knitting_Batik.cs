using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace ConsoleApp
{
    class Program
    {
        const double DefaultEpsilon = 1e-18;

        struct Vector
        {
            public double X;
            public double Y;

            public Vector(double x, double y)
            {
                X = x;
                Y = y;
            }
            public Vector(double angle)
            {
                X = Math.Cos(angle);
                Y = Math.Sin(angle);
            }

            public double Hypot()
            {
                return Math.Sqrt((X * X) + (Y * Y));
            }
            public double HypotSquared()
            {
                return (X * X) + (Y * Y);
            }
            public Vector RotateClockwise(double angle)
            {
                double cos = Math.Cos(angle);
                double sin = Math.Sin(angle);

                return new Vector(X * cos + Y * sin, X * -sin + Y * cos);
            }
            public Vector Perpendicular()
            {
                return new Vector(-Y, X);
            }
            public bool IsEqual(Vector vector, double epsilon = DefaultEpsilon)
            {
                return Equal(this.X, vector.X, epsilon) && Equal(this.Y, vector.Y, epsilon);
            }

            public static Vector operator +(Vector a)
            {
                return a;
            }
            public static Vector operator -(Vector a)
            {
                return new Vector(-a.X, -a.Y);
            }
            public static Vector operator +(Vector a, Vector b)
            {
                return new Vector(a.X + b.X, a.Y + b.Y);
            }
            public static Vector operator -(Vector a, Vector b)
            {
                return new Vector(a.X - b.X, a.Y - b.Y);
            }
            public static double Determinant(Vector a, Vector b)
            {
                return (a.X * b.Y) - (a.Y * b.X);
            }
            public static double DotProduct(Vector a, Vector b)
            {
                return (a.X * b.X) + (a.Y * b.Y);
            }
        }
        struct Line
        {
            public double A;
            public double B;
            public double C;

            public double slopeY => -A / B; // y = f'(x)
            public double slopeX => -B / A; // x = f'(y)

            public Line(Vector p1, Vector p2)
            {
                A = p2.Y - p1.Y;
                B = p1.X - p2.X;
                C = p2.X * p1.Y - p1.X * p2.Y;
            }
        }
        struct Segment
        {
            public Vector Left;
            public Vector Right;

            public Segment(Vector left, Vector right)
            {
                Left = left;
                Right = right;
            }

            public Line GetLine()
            {
                return new Line(Left, Right);
            }
            public bool IsOnTheSegment(Vector point, double epsilon = DefaultEpsilon)
            {
                Vector v1 = point - Left;
                Vector v2 = point - Right;
                double det = Vector.Determinant(v1, v2);
                double dotProd = Vector.DotProduct(v1, v2);

                return Equal(det, 0, epsilon) && LessOrEqual(dotProd, 0, epsilon);
            }
        }

        static Program()
        {
            // Comment this before submitting (in case of strandard input)
            //Console.SetIn(new StreamReader("input.txt"));
            //Console.SetOut(new StreamWriter("output.txt"));
        }
        static void Main()
        {
            //int testCases = int.Parse(Console.ReadLine());
            //for (int z = 0; z < testCases; z++)
            //{

            //}

            int[] data = ReadIntData();
            int n = data[0];
            int m = data[1];
            int k = data[2];
            int r = data[3];
            int c = data[4];

            data = ReadIntData();
            int ax = data[0];
            int ay = data[1];
            int bx = data[2];
            int by = data[3];

            if (ax > bx)
            {
                Swap(ref ax, ref bx);
            }
            if (ay > by)
            {
                Swap(ref ay, ref by);
            }

            //int dx = bx - ax;
            //int dy = by - ay;

            long total = (long)n * m;
            if ((ax != bx) || (ay != by))
            {
                total -= (long)r * c;
            }
            
            //total += (long)(ax - bx + r) * (ay - by + c);

            Console.WriteLine(PowQuick(k, total, 1_000_000_007));

            Console.Out.Close();
        }

        static bool Equal(double a, double b, double epsilon = DefaultEpsilon)
        {
            return Math.Abs(a - b) < epsilon;
        }
        static bool Greater(double a, double b, double epsilon = DefaultEpsilon)
        {
            return (a > b) && !Equal(a, b, epsilon);
        }
        static bool Less(double a, double b, double epsilon = DefaultEpsilon)
        {
            return (a < b) && !Equal(a, b, epsilon);
        }
        static bool GreaterOrEqual(double a, double b, double epsilon = DefaultEpsilon)
        {
            return (a > b) || Equal(a, b, epsilon);
        }
        static bool LessOrEqual(double a, double b, double epsilon = DefaultEpsilon)
        {
            return (a < b) || Equal(a, b, epsilon);
        }
        static double DegToRad(double angle)
        {
            return (angle / 180) * Math.PI;
        }
        static long LCM(long a, long b)
        {
            return (a / GCD(a, b)) * b;
        }
        static long GCD(long a, long b)
        {
            while (a != 0)
            {
                b %= a;
                Swap(ref a, ref b);
            }

            return b;
        }
        static long PowQuick(long b, long p)
        {
            long exp = b;
            long res = 1;

            while (p > 0)
            {
                if ((p % 2) == 1)
                {
                    res *= exp;
                }

                exp *= exp;
                p /= 2;
            }

            return res;
        }
        static long PowQuick(long b, long p, long mod)
        {
            long exp = b;
            long res = 1;

            while (p > 0)
            {
                if ((p % 2) == 1)
                {
                    res *= exp;
                    res %= mod;
                }

                exp *= exp;
                exp %= mod;
                p /= 2;
            }

            return res;
        }
        static uint BitCount(uint a)
        {
            a = ((a >> 1) & 0x55555555u) + (a & 0x55555555u);
            a = ((a >> 2) & 0x33333333u) + (a & 0x33333333u);
            a = ((a >> 4) & 0x0F0F0F0Fu) + (a & 0x0F0F0F0Fu);
            a = ((a >> 8) & 0x00FF00FFu) + (a & 0x00FF00FFu);
            a = ((a >> 16) & 0x0000FFFFu) + (a & 0x0000FFFFu);
            return a;
        }
        static bool AreAlmostEqual(double a, double b, double epsilon)
        {
            return Math.Abs(a - b) < epsilon;
        }
        static int Binary(int[] array, int val)
        {
            return Binary(array, val, 0, array.Length);
        }
        static int Binary(int[] array, int val, int left, int right)
        {
            if (val < array[0])
            {
                return 0;
            }

            while (right - left > 1)
            {
                int mid = (right + left) / 2;

                if (array[mid] <= val)
                {
                    left = mid;
                }
                else
                {
                    right = mid;
                }
            }

            return right;
        }
        static void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
        static void Swap(ref long a, ref long b)
        {
            long temp = a;
            a = b;
            b = temp;
        }
        static double[] ReadDoubleData(TextReader input)
        {
            return input.ReadLine()
                .Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                .Select(val => double.Parse(val))
                .ToArray();
        }
        static double[] ReadDoubleData()
        {
            return ReadDoubleData(Console.In);
        }
        static int[] ReadIntData(TextReader input)
        {
            return input.ReadLine()
                .Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                .Select(val => int.Parse(val))
                .ToArray();
        }
        static int[] ReadIntData()
        {
            return ReadIntData(Console.In);
        }
        static long[] ReadLongData(TextReader input)
        {
            return input.ReadLine()
                .Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                .Select(val => long.Parse(val))
                .ToArray();
        }
        static long[] ReadLongData()
        {
            return ReadLongData(Console.In);
        }
    }
}