// 卡特兰数 (Catalan)
//
// 通项公式： C(2n, n) - C(2n, n-1) 或者 C(2n, n) / (n + 1)
// 递推式： f(n) = sum(f(k)*f(n-k-1))  k=0,1,...,n-1
//
// 已知一个栈（无穷大）的进栈序列，有多少种不同的出栈序列？
// n 个节点的无标号二叉树有多少种？
// 一个凸 n 边形，每次连接两个顶点可以将其划分成三角形，有多少种不同的剖分方法？

// 前 10 项
int Catalan[] {
    1,
    2,
    5,
    14,
    42,
    132,
    429,
    1430,
    4862,
    16796
};
