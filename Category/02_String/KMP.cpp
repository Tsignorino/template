// KMP 利用 PMT 加速下一次匹配，并且原串指针不会进行回溯。
//
// 前缀函数表示 s[0:i]（闭区间）的相等的真前缀与真后缀的最大长度
// 实际编码过程中，把 PMT 右移一位，第 0 位的值设成了 -1，得到 nxt 数组
// nxt 数组表示不含当前字符的前后缀最大匹配长度（前后缀小于子串长度）


// 计算前缀函数
auto calcPi(const string& s) {
    int n = s.size();
    vector<int> pi(n);
    int match = 0;
    for (int i = 1; i < n; i++) {
        char ch = s[i];
        while (match > 0 && s[match] != ch) {
            match = pi[match - 1];
        }
        if (s[match] == ch) {
            match++;
        }
        pi[i] = match;
    }
    return pi;
}

// 返回文本串 s 中，模式串 p 所有成功匹配的下标（pattern[0] 在 s 中的下标）
auto kmpSearch(const string& s, const string p) {
    auto pi = calcPi(p);
    vector<int> pos;
    int match = 0;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        while (match > 0 && p[match] != ch) {
            match = pi[match - 1];
        }
        if (p[match] == ch) {
            match++;
        }
        if (match == p.size()) {
            pos.emplace_back(i - p.size() + 1);
            match = pi[match - 1]; // 不允许重叠则置零
        }
    }
    return pos;
}

// 生成 nxt 数组
auto nextArray(const string& s) {
    int n = s.size();
    vector<int> nxt(n + 1);
    nxt[0] = -1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j != -1 && s[i - 1] != s[j]) {
            j = nxt[j];
        }
        nxt[i] = ++j;
    }
    return nxt;
}

// 返回文本串 text 中，模式串 pattern 首次出现的下标（pattern[0] 在 text 中的下标）
int KMP(const string& text, const string& pattern) {
    vector<int> nxt(nextArray(pattern));
    int n = text.size(), m = pattern.size();
    int x = 0, y = 0;
    while (x < n && y < m) {
        if (text[x] == pattern[y]) {
            x++, y++;
        } else if (y == 0) {
            x++;
        } else {
            y = nxt[y];
        }
    }
    return y == m ? x - y : -1;
}

