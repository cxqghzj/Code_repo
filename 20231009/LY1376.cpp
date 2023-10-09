#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
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
const int N = 2e5 + 5, inf = 0x7f7f7f7f;
array <tuple <int, int, int>, N> isl;
array <array <int, 2>, N> f;
/*
 * 0 Alice
 * 1 Bob
 */
int main() {
#ifdef ONLINE_JUDGE
	freopen("increase.in", "r", stdin);
	freopen("increase.out", "w", stdout);
#endif
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		get <1>(isl[i]) = read(), get <2>(isl[i]) = read();
		get <0>(isl[i]) = read();
	}
	sort(isl.begin() + 1, isl.begin() + 1 + m, greater <tuple <int, int, int> >());
	for (int i = 1; i <= n; i++)
		f[i][1] = 0x7f7f7f7f;
	for (int i = 1; i <= m; i++) {
		int u = get <1>(isl[i]), v = get <2>(isl[i]);
		int pu = f[u][0], ku = (f[u][1] == inf ? 0 : f[u][1]),
			pv = f[v][0], kv = (f[v][1] == inf ? 0 : f[v][1]);
		f[u][0] = max(f[u][0], kv + 1), f[u][1] = min(f[u][1], pv + 1);
		f[v][0] = max(f[v][0], ku + 1), f[v][1] = min(f[v][1], pu + 1);
		/* write(f[u][0]), putchar(32); */
		/* write(f[u][1]), putchar(32); */
		/* write(f[v][0]), putchar(32); */
		/* write(f[v][1]), puts(""); */
	}
	for (int i = 1; i <= n; i++)
		write(f[i][0]), putchar(32);
	puts("");
	return 0;
}
