#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Human {
    int y, x;
    bool is_escape;
};

struct YX {
    int y, x;
};

int n, m;
int map[20][20];
int visited[20][20];

vector<YX> base;
vector<YX> store;
vector<Human> human;
queue<YX> escape;

int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };

int find_base(int num) {
    queue<YX> q;
    q.push({ store[num].y,store[num].x });
    visited[store[num].y][store[num].x] = 1;
    while (!q.empty()) {
        YX now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny > n || nx > n || ny < 1 || nx < 1) { continue; }
            if (map[ny][nx] == 2) { continue; }
            if (visited[ny][nx]) { continue; }
            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny,nx });
        }
    }
    int min_dist = 21e8;
    int base_idx = -1;
    for (int i = 0; i < base.size(); i++) {
        if (visited[base[i].y][base[i].x] != 0 && visited[base[i].y][base[i].x] < min_dist) {
            min_dist = visited[base[i].y][base[i].x];
            base_idx = i;
        }
    }
    memset(visited, 0, sizeof(visited));

    return base_idx;
}

YX find_dir(int num) {
    queue<YX> q;
    q.push({ store[num].y,store[num].x });
    visited[store[num].y][store[num].x] = 1;
    while (!q.empty()) {
        YX now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny > n || nx > n || ny < 1 || nx < 1) { continue; }
            if (map[ny][nx] == 2 && !(human[num].y==ny && human[num].x==nx)) { continue; }
            if (visited[ny][nx]) { continue; }
            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny,nx });

        }
    }

    int max_dist = visited[human[num].y][human[num].x];
    YX result = { 0,0 };
    for (int i = 0; i < 4; i++) {
        int human_ny = human[num].y + dy[i];
        int human_nx = human[num].x + dx[i];
        if (human_ny > n || human_nx > n || human_nx < 1 || human_ny < 1) { continue; }
        if (visited[human_ny][human_nx] == max_dist - 1) {
            result = { human_ny,human_nx };
            break;
        }
    }
    memset(visited, 0, sizeof(visited));
    return result;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                base.push_back({ i,j });
            }
        }
    }
    store.push_back({ -1,-1 });
    human.push_back({ -1,-1,0 });

    int st_y, st_x;
    for (int i = 0; i < m; i++) {
        cin >> st_y >> st_x;
        store.push_back({ st_y,st_x });
    }
    int time = 1;
    int count = 1;
    bool flag = 0;


    while (1) {
        int cnt = 0;
        for (int i = 1; i <= count; i++) {
            if (human.size() >= i + 1) {
                if (human[i].is_escape) { continue; }
                YX res = find_dir(i);
                human[i].y = res.y;
                human[i].x = res.x;
                if (human[i].y == store[i].y && human[i].x == store[i].x) {
                    human[i].is_escape = 1;
                    escape.push({ human[i].y,human[i].x });
                }
            }
           
            else if (human.size() < i + 1) {
                while (!escape.empty()) {
                    YX now = escape.front();
                    escape.pop();
                    map[now.y][now.x] = 2;
                }
                int bs_idx = find_base(i);
                human.push_back({ base[bs_idx].y,base[bs_idx].x ,0 });
                map[base[bs_idx].y][base[bs_idx].x] = 2;

                base.erase(base.begin() + bs_idx);
                continue;
            }
        }

        for (int i = 1; i <= count; i++) {
            if (human[i].is_escape == 0) { break; }
            if (i == count) {
                flag = 1;
            }
        }

        if (flag) {
            break;
        }

        while (!escape.empty()) {
            YX now = escape.front();
            escape.pop();
            map[now.y][now.x] = 2;
        }
        if (count < m) {
            count++;
        }
        time++;
    }
    cout << time;


}