#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
const int N = 1e5 + 5, M = 1e5 + 5, inf = 0x7f7f7f7f;
array <array <int, 2>, N> f;
namespace G {

array <int, N> fir;
array <int, M> nex, to;
int cnt;
void add(int x, int y) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	fir[x] = cnt;
}

}
int dfs(int x, int p) {
	if (~f[x][p]) return f[x][p];
	f[x][p] = 0;
	int ans = p ? inf : 0;
	for (int i = G::fir[x]; i; i = G::nex[i]) {
		int res = dfs(G::to[i], p ^ 1);
		ans = p ? min(res, ans) : max(res, ans);
	}
	return f[x][p] = max(ans == inf ? 0 : ans, x);
}


int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);

	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read();
		G::add(x, y);
	}
	for (int i = 1; i <= n; i++) {
		for (int i = 1; i <= 1e5; i++)
			f[i][0] = f[i][1] = -1;
		/* dfs(i, 0); */
		write(dfs(i, 0)), putchar(32);
		/* if (i == 2) write(f[3][1]), puts(""); */
	}
	puts("");
	return 0;
}
