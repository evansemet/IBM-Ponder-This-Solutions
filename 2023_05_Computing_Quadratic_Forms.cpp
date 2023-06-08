#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

double calc(const std::vector<double> &x, const std::vector<double> &a, const std::vector<std::vector<int> > &Q, int n) {
    double result = 0.0;

    for (int i = 0; i < n; ++i) {
        double x_i = x[i];
        result += x_i * x_i;
        for (int j = i + 1; j < n; ++j) {
            int sum = 0;
            for (size_t k = 0; k < 5; ++k) {
                sum += (Q[i][k] == Q[j][k]) << k;
            }
            result += 2 * x_i * a[sum] * x[j];
        }
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    int n = 1 << N;

    clock_t start = clock();

    std::vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = -1.0 + 2.0 * i / (n - 1);
    }

    std::vector<double> a(32);
    for (int i = 0; i < 32; ++i) {
        a[i] = static_cast<double>(i) / 31;
    }

    std::vector<std::vector<int>> Q(n, std::vector<int>(5));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            Q[i-1][j-1] = static_cast<int>(32 * (std::sin(i*j) - std::floor(std::sin(i*j))));
        }
    }

    double result = calc(x, a, Q, n);

    std::cout.precision(3);
    std::cout << std::fixed << result << std::endl;
    std::cout << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;

    return 0;
}
