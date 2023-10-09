#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
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
const int N = 2e5 + 5, M = 1e6 + 5, inf = 0x7f7f7f7f;
namespace G {

array <int, N> fir;
array <int, M> nex, to, len;
int cnt;
void add(int x, int y, int z) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	len[cnt] = z;
	fir[x] = cnt;
}

}
using namespace G;
array <array <int, 3>, M> f, g;
void dfs(int x, int flg, int y, int lst) {
	if (~f[x][flg]) return;
	f[x][flg] = 0;
	int ans = flg ? inf : 0;
	for (int i = fir[y]; i; i = nex[i]) {
		if (len[i] <= len[x]) continue;
		dfs(i, flg ^ 1, to[i], y);
		ans = flg ? min(ans, f[i][flg ^ 1] + 1) : max(ans, f[i][flg ^ 1] + 1);
	}
	f[x][flg] = ans;
	g[lst][flg] = flg ? min(g[lst][flg], f[x][flg ^ 1] + 1) : max(g[lst][flg], f[x][flg ^ 1] + 1);
}
int main() {
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), z = read();
		add(x, y, z), add(y, x, z);
	}
	array <int, 3> tp;
	tp.fill(-1);
	f.fill(tp);
	for (int i = 1; i <= n; i++) {
		for (int j = fir[i]; j; j = nex[j]) {
			if (!~f[j][0]) dfs(j, 0, i, i);
			if (!~f[j][1]) dfs(j, 1, i, i);
		}
	}
	return 0;
}
