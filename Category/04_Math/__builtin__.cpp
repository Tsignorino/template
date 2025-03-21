// __builtin_popcount()  求 x 置位数
int popcount(int x) {
    int cnt = 0;
    while (x) {
        cnt++;
        x &= x - 1; // x -= x & -x
    }
    return cnt;
}


// __lg(x)  不超过 x 的最大的 2 的幂次
int lg(int x) {
    int power = 0;
    while((1 << power) <= (x >> 1)) {
        power++;
    }
    return power;
}


// gcd & lcm
int gcd_(int a, int b) {
    if (b > a) {
        std::swap(a, b);
    }
    return b == 0 ? a : gcd_(b, a % b);
}
int gcd_(int a, int b) {
    while (a != 0) {
        int tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}
int lcm_(int a, int b) {
    return a / gcd_(a, b) * b;
}
