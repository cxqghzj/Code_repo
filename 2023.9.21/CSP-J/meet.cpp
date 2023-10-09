#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
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

const int N = 1e6 + 5;
int f[N];
queue <int> q;
void bfs(int x) {
	q.push(x);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u * 2 <= 1e6 && !f[u * 2]) {
			f[u * 2] = f[u] + 1;
			q.push(u * 2);
		}
		if (u + 1 <= 1e6 && !f[u + 1]) {
			f[u + 1] = f[u] + 1;
			q.push(u + 1);
		}
		if (u - 1 && !f[u - 1]) {
			f[u - 1] = f[u] + 1;
			q.push(u - 1);
		}
	}
}
signed main() {
	freopen("meet.in", "r", stdin);
	freopen("meet.out", "w", stdout);
	int n = read(), k = read();
	f[n] = 1;
	bfs(n);
	write(f[k] - 1), puts("");
	return 0;
}
