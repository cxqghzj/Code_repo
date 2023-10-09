#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
#define fi first
#define se second
const int N = 1e6 + 5;
deque <pii> q;
bitset <N> vis;
int ans;
void bfs(int k) {
	q.push_front(make_pair(1, 1));
	while (!q.empty()) {
		pii u = q.front();
		q.pop_front();
		if (vis[u.fi]) continue;
		vis[u.fi] = 1;
		if (!u.fi) ans = u.se;
		q.push_front(make_pair(u.fi * 10 % k, u.se));
		q.push_back(make_pair((u.fi + 1) % k, u.se + 1));
	}
}
signed main() {
	int k = read();
	bfs(k);
	write(ans), puts("");
	return 0;
}
