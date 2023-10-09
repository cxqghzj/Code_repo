/* #define debug */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#define int long long
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 1e5 + 5, mod = 998244353;
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
struct Matrix {
	int A[3][3];
	int n, m;
	int* operator [](int x) {
		return A[x];
	}
	Matrix () {
		A[1][1] = A[1][2] = 0;
		A[2][1] = A[2][2] = 0;
		n = 2, m = 2;
	}
	Matrix (int flg) {
		A[1][1] = A[2][2] = 1;
		A[2][1] = A[1][2] = 0;
		n = 2, m = 2;
	}
	Matrix (int a, int b) {
		A[1][1] = a, A[1][2] = 1;
		A[2][1] = -b, A[2][2] = 0;
		n = 2, m = 2;
	}
	Matrix friend operator *(Matrix a, Matrix b) {
		Matrix ans = Matrix();
		for (int i = 1; i <= a.n; i++)
			for (int k = 1; k <= a.m; k++)
				for (int j = 1; j <= b.m; j++)
					ans[i][j] += a[i][k] * b[k][j] % mod, Mod(ans[i][j]);
		return ans;
	}
	Matrix friend operator ^(Matrix x, int k) {
		Matrix ans = Matrix(1);
		while (k) {
			if (k & 1) ans = ans * x;
			x = x * x;
			k >>= 1;
		}
		return ans;
	}
};

namespace subtask1 {

array <int, N> f;
void main(int x, int y, int n) {
	f[1] = x;
	f[2] = (x * x % mod - 2 * y + mod) % mod;
	for (int i = 3; i <= n; i++) {
		f[i] = f[i - 1] * x % mod - f[i - 2] * y % mod;
		Mod(f[i]);
	}
	write(f[n]), puts("");
}

}

namespace subtask2 {

void main(int x, int y, int n) {
	Matrix T = Matrix(x, y);
	Matrix G = Matrix();
	G.n = 1, G.m = 2;
	G[1][2] = x, G[1][1] = (x * x % mod - 2 * y + mod) % mod;
	T = T ^ (n - 2);
	G = G * T;
	write(G[1][1]), puts("");
}

}
signed main() {
	/* freopen("poly.in", "r", stdin); */
	/* freopen("poly.out", "w", stdout); */
	int x = read(), y = read(), n = read();
	if (n <= 1e5) subtask1::main(x, y, n);
	else subtask2::main(x, y, n);
	return 0;
}
