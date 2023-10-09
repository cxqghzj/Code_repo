## 题意

给定一个整数 $K$。求一个 $K$ 的正整数倍 $S$，使得 $S$ 的数位累加和最小。

**【数据范围】**

- $2 \le K \le {10}^5$；
- $K$ 是整数。

**【输入格式】**

一行一个正整数 $K$。

**【输出格式】**

输出 $K$ 的正整数倍的最小数位累加和。

## Sol

很考验思维能力的思维题。

不难想到（，每个数都能通过类似数位dp的方式生成。

也就是：

- 个位 $ + 1$，贡献为 $1$
- 整体 $\times 10$，贡献为 $0$

然后对于这个东西做一遍膜 $k$ 意义下的 $01 bfs$ 就做完了。

## Code

``` cpp
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
```
