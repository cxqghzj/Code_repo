#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
#include <bitset>
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
const int N = 2e5 + 5, M = 4e5 + 5;

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

array <tuple <int, int, int>, N> isl;

namespace Subtask1 {

bitset <N> vis;
array <array <int, 3005>, 3005> f;

using G::fir, G::to, G::nex;


void dfs(int x, int k) {
	if (~f[x][k]) return;
	f[x][k] = get <2>(isl[x]);
	for (int i = fir[x]; i; i = nex[i]) {
		if (get <1>(isl[to[i]]) < k) continue;
		int _k = get <0>(isl[to[i]]);
		dfs(to[i], _k);
		f[x][k] = max(f[x][k], f[to[i]][_k]);
	}
}
void main(int n, int m) {
	for (int i = 1; i <= 3000; i++)
		for (int j = 1; j <= 3000; j++)
			f[i][j] = -1;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		dfs(i, get <0>(isl[i]));
	}
	for (int i = 1; i <= n; i++)
		write(f[i][get <0>(isl[i])]), putchar(32);
}

}
namespace Subtask2 {

array <vector <int>, N> isl;
array <int, N> f;
using G::fir, G::nex, G::to, G::cnt;
void main(int n, int m) {
	for (int i = 1; i <= n; i++)
		get <1>(::isl[i]) = i;
	sort(::isl.begin() + 1, ::isl.begin() + 1 + n, greater <tuple <int, int, int> >());
	cnt = 0, fir.fill(0);
	for (int i = 1; i <= n; i++) {
		f[get <1>(::isl[i])] = get <2>(::isl[i]);
		for (auto x : isl[get <1>(::isl[i])])
			f[get <1>(::isl[i])] = max(f[get <1>(::isl[i])], f[x]);
	}
	for (int i = 1; i <= n; i++)
		write(f[i]), putchar(32);
	puts("");
}

}
vector <int> prl;
int main() {
	/* freopen("journey.in", "r", stdin); */
	/* freopen("journey.out", "w", stdout); */
	int n = read(), m = read();
	bool flg1 = true, flg2 = true;
	for (int i = 1; i <= n; i++) {
		get <0>(isl[i]) = read(), get <1>(isl[i]) = read(), get <2>(isl[i]) = read();
		if (get <0>(isl[i]) > 1) flg1 = false;
		if (get <0>(isl[i]) != get <1>(isl[i])) flg2 = false;
		prl.push_back(get <0>(isl[i])), prl.push_back(get <1>(isl[i]));
	}
	sort(prl.begin(), prl.end());
	auto it = unique(prl.begin(), prl.end());
	prl.erase(it, prl.end());
	for (int i = 1; i <= n; i++) {
		get <0>(isl[i]) = lower_bound(prl.begin(), prl.end(), get <0>(isl[i])) - prl.begin() + 1;
		get <1>(isl[i]) = lower_bound(prl.begin(), prl.end(), get <1>(isl[i])) - prl.begin() + 1;
		/* write(get <0>(isl[i])), putchar(32); */
		/* write(get <1>(isl[i])), puts(""); */
	}
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
		Subtask2::isl[x].push_back(y);
	}
	if (flg1 || n <= 3000) Subtask1::main(n, m);
	if (flg2) Subtask2::main(n, m);
	return 0;
}
