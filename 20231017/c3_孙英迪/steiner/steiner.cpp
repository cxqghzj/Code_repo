#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#include <queue>
#include <bitset>
#define int long long
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

const int N = 2e5 + 5, M = 4e5 + 5, inf = 2e18;

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
#define fi first
#define se second

array <int, N> dis1, dis2;

array <int, N> dis, dis_;
bitset <N> vis;

priority_queue <pii, vector <pii>, greater <pii> > q;


void dijkstra(vector <int> s) {
	using G::fir, G::to, G::len, G::nex;
	dis.fill(inf);
	for (auto x : s)
		dis[x] = dis_[x], q.push(make_pair(dis[x], x));
	vis = 0;
	while (!q.empty()) {
		int u = q.top().se;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = fir[u]; i; i = nex[i]) {
			if (dis[to[i]] <= dis[u] + len[i]) continue;
			dis[to[i]] = dis[u] + len[i];
			q.push(make_pair(dis[to[i]], to[i]));
		}
	}
}
signed main() {
	freopen("steiner.in", "r", stdin);
	freopen("steiner.out", "w", stdout);
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), z = read();
		G::add(x, y, z);
		G::add(y, x, z);
	}
	dijkstra(vector <int>(1, 1)), dis1 = dis;
	dijkstra(vector <int>(1, 2)), dis2 = dis;
	vector <int> tp;
	for (int i = 1; i <= n; i++)
		dis_[i] = dis1[i] + dis2[i], tp.push_back(i);
	dijkstra(tp);
	for (int i = 3; i <= n; i++)
		write(dis[i]), putchar(32);
	puts("");
	return 0;
}
