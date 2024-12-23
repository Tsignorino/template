// 选择排序：每次找出第 i 小的元素，与数组第 i 个位置上的元素交换
void selection_sort(int* a, int n) {
    if (n < 2) {
        return;
    }
    for (int i = 0; i < n - 1; ++i) {
        int idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[idx]) {
                idx = j;
            }
        }
        if (idx != i) {
            swap(a[i], a[idx]);
        }
    }
}

// 冒泡排序：每次检查相邻两个元素（可以用 flag 标记是否交换过元素）
void bubble_sort(int* a, int n) {
    if (n < 2) {
        return;
    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] > a[i + 1]) {
                flag = true;
                swap(a[i], a[i + 1]);
            }
        }
    }
}

// 插入排序：从后往前找，比当前值大的右移一位（将数组分成了有序和无序两部分）
void insertion_sort(int* a, int n) {
    if (n < 2) {
        return;
    }
    for (int i = 1; i < n; ++i) {
        int v = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > v) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = v;
    }
}

void insertion_sort() {
    std::cout << "\n" "用 `rotate` 实现插入排序，逐步运行:\n";

    s = {'2', '4', '2', '0', '5', '9', '7', '3', '7', '1'};

    for (auto i = s.begin(); i != s.end(); ++i) {
        std::cout << "i = " << std::ranges::distance(s.begin(), i) << ": ";
        std::ranges::rotate(std::ranges::upper_bound(s.begin(), i, *i), i, i + 1);
        std::cout << s << '\n';
    }
    std::cout << (std::ranges::is_sorted(s) ? "已排序!" : "未排序.") << '\n';
}

// 折半插入排序
void half_insertion_sort(int* a, int n) {
    if (n < 2) {
        return;
    }
    for (int i = 1; i < n; ++i) {
        int v = a[i];
        auto idx = upper_bound(a, a + i, v) - a;
        memmove(a + idx + 1, a + idx, (i - idx) * sizeof(int));
        a[idx] = v;
    }
}

// 计数排序：需要一个额外空间存储待排序数组中相应元素的个数，还需要计算前缀和解决元素重复的情况
const int N = 10'010;
const int W = 10'010;
vector<int> a(N), b(N), cnt(W);
int n, w;
void counting_sort() {
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
    }
    for (int i = 1; i <= w; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[cnt[a[i]]--] = a[i];
    }
}
