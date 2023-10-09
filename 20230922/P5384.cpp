#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#define pii pair <int, int>
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
#define fi first
#define se second
const int N = 1e6 + 5;
namespace G {

array <int, N> fir, nex, to;
int cnt;
void add(int x, int y) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	fir[x] = cnt;
}

}

array <pii, N> qs;

namespace Hpt {

using G::fir, G::nex, G::to;
array <int, N> siz, dep, dfn;
array <int, N> prl;
array <vector <int>, N> isl, cur;
int cnt;
void dfs(int x) {
	cnt++;
	prl[dep[x]] = x;
	for (auto y : cur[x]) {
		if (dep[x] < qs[y].se) {
			qs[y].fi = -1;
			continue;
		}
		qs[y].fi = prl[dep[x] - qs[y].se];
	}
	siz[x] = 1;
	dfn[x] = cnt;
	isl[dep[x]].push_back(cnt);
	for (int i = fir[x]; i; i = nex[i]) {
		dep[to[i]] = dep[x] + 1;
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}

}
int main() {
	int n = read(), q = read();
	for (int i = 2; i <= n; i++) {
		int x = read();
		G::add(x, i);
	}
	for (int i = 1; i <= q; i++) {
		qs[i].fi = read(), qs[i].se = read();
		Hpt::cur[qs[i].fi].push_back(i);
	}
	Hpt::dfs(1);
	using Hpt::dep, Hpt::isl, Hpt::siz, Hpt::dfn;
	for (int i = 1; i <= q; i++) {
		if (!(~qs[i].fi)) {
			printf("0 ");
			continue;
		}
		int pos = dep[qs[i].fi] + qs[i].se;
		int ans = upper_bound(isl[pos].begin(), isl[pos].end(), dfn[qs[i].fi] + siz[qs[i].fi] - 1)
				- lower_bound(isl[pos].begin(), isl[pos].end(), dfn[qs[i].fi]) - 1;
		/* for (auto x : isl[pos]) { */
			/* write(x), putchar(32); */
		/* } */
		/* puts(""); */
		write(ans), putchar(32);
	}
	puts("");
	return 0;
}
