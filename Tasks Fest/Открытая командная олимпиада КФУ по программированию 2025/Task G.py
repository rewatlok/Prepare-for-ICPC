Mn = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def F(s):
    return (sum(Mn[:int(s[3:5]) - 1]) + (int(s[0:2]) - 1)) * 24 * 60 + int(s[11:13]) * 60 + int(s[14:16])

n, m = map(int, input().split())
evs = []

for _ in range(n):
    s = input().strip()
    parts = s[s.find(']') + 2:].split()
    if len(parts) > 2:
        page = parts[2]
    else:
        page = ""
    if parts[1] == "enter":
        typ = 0
    else:
        typ = 1
    evs += [((F(s[1:s.find(']')]), typ, int(parts[0]), page, 0, -1))]

for i in range(m):
    s = input().strip()
    q = s[s.find(']') + 2:]
    if q[:6] == "online":
        typ = 3
        k = 0
    else:
        typ = 2
        k = int(q.split()[-1])
    evs += [((F(s[1:s.find(']')]), typ, 0, "", k, i))]

evs.sort()

act = {}
online = set()
pages = {}
ans = [""] * m

for e in evs:
    t, typ, uid, page, k, idx = e
    if typ == 0:
        if uid not in act:
            act[uid] = 1
        else:
            act[uid] += 1
        if act[uid] == 1:
            online.add(uid)
        if page not in pages:
            pages[page] = set()
        if uid not in pages[page]:
            pages[page].add(uid)
    elif typ == 1:
        act[uid] -= 1
        if act[uid] == 0:
            online.discard(uid)
    elif typ == 3:
        ans[idx] = str(len(online))
    elif typ == 2:
        mas = []
        for p, u in pages.items():
            if u:
                mas.append((-len(u), p))
        mas.sort()
        if not mas:
            ans[idx] = "-1"
        else:
            mas_ = []
            for i in range(min(k, len(mas))):
                cnt = -mas[i][0]
                mas_.append(str(cnt))
            ans[idx] = " ".join(mas_)

for a in ans:
    print(a)
