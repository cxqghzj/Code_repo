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
const int N = 305, inf = 2e18;
array <int, N> s;
array <array <int, N>, N> f, g;
signed main() {
	/* freopen("river.in", "r", stdin); */
	/* freopen("river.out", "w", stdout); */
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	for (int i = 1; i <= n; i++) {
		g[i][i] = s[i];
		for (int j = i + 1; j <= n; j++) {
			g[i][j] = __gcd(g[i][j - 1], s[j]);
			f[i][j] = inf;
		}
	}
	for (int l = 1; l <= n; l++) {
		for (int i = 1; i + l <= n; i++) {
			int j = i + l;
			for (int k = i; k < j; k++) {
				f[i][j] = min(f[i][k] + f[k + 1][j] + g[i][k] + g[k + 1][j], f[i][j]);
			}
		}
	}
	write(f[1][n]), puts("");
	return 0;
}
