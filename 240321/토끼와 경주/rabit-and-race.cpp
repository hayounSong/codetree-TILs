#include <iostream>
#include <cmath>
using namespace std;

long Q, N, M, P;
pair<long, long> rabit[20001];
pair<int, int> where[20001];
long score[100001];
long pidw[10000001];
long jump[20001] = {0};
int direcx[4] = {0, 1, 0, -1};
int direcy[4] = {1, 0, -1, 0};
long isjump[20001] = {0};
void moving(long S)
{
    long sj = 999999;
    long sn = -1;
    for (long i = 0; i < P; i++)
    {
        if (jump[i] < sj)
        {
            sj = jump[i];
            sn = i;
        }
        else if (jump[i] == sj)
        {
            if (where[sn].first + where[sn].second > where[i].first + where[i].second)
            {
                sj = jump[i];
                sn = i;
            }
            else if (where[sn].first + where[sn].second == where[i].first + where[i].second)
            {
                if (where[sn].first > where[i].first)
                {
                    sj = jump[i];
                    sn = i;
                }
                else if (where[sn].first == where[i].first)
                {
                    if (where[sn].second > where[i].second)
                    {
                        sj = jump[i];
                        sn = i;
                    }
                    else if (where[sn].second == where[i].second)
                    {
                        if (rabit[sn].first > rabit[i].first)
                        {
                            sj = jump[i];
                            sn = i;
                        }
                    }
                }
            }
        }
    }
    // 토끼 찾음
    long cx = where[sn].first;
    long cy = where[sn].second;
    long cd = rabit[sn].second;
    long bx = -1;
    long by = -1;
    long bs = -1;
    isjump[sn]++;
    jump[sn]++;
    for (long i = 0; i < 4; i++)
    {
        long fx = cx + direcx[i] * cd;
        long fy = cy + direcy[i] * cd;

        if (fx >= N)
        {
            fx = fx % (2 * (N - 1));
            if (fx >= N)
            {
                fx = N - 1 - (fx - (N - 1));
            }
        }
        else if (fx < 0)
        {
            fx = fx % (2 * (N - 1));
            fx = abs(fx);
            if (fx >= N)
            {
                fx = N - 1 - (fx - (N - 1));
            }
        }
        if (fy >= M || fy < 0)
        {
            fy = fy % (2 * (M - 1));
            fy = abs(fy);
            if (fy >= M)
            {
                fy = M - 1 - (fy - (M - 1));
            }
        }
        // 이동 완료
        if (fx + fy > bs)
        {
            bs = fx + fy;
            bx = fx;
            by = fy;
        }
        else if (fx + fy == bs)
        {
            if (fx > bx)
            {
                bs = fx + fy;
                bx = fx;
                by = fy;
            }
            else if (fx == bx)
            {
                if (fy > by)
                {
                    bs = fx + fy;
                    bx = fx;
                    by = fy;
                }
            }
        }
    }
    // 최고값 찾기
    where[sn].first = bx;
    where[sn].second = by;
    for (long i = 0; i < P; i++)
    {
        if (i == sn)
        {
            continue;
        }
        else
        {
            score[i] = score[i] + bx + by + 2;
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> Q;
    for (long qq = 0; qq < Q; qq++)
    {
        long sc;
        cin >> sc;
        if (sc == 100)
        {
            cin >> N >> M >> P;

            for (long i = 0; i < P; i++)
            {
                long id, d;
                cin >> id >> d;
                rabit[i] = {id, d};
                pidw[id] = i;
            }
        }
        else if (sc == 200)
        {
            long K, S;
            cin >> K >> S;
            for (long i = 0; i < P; i++)
            {
                isjump[i] = 0;
            }
            for (long i = 0; i < K; i++)
            {
                moving(S);
            }
            long bw = -1;
            long br = -1;
            long bx = -1;
            long by = -1;
            for (long i = 0; i < P; i++)
            {
                if (isjump[i] == 0)
                {
                    continue;
                }
                else
                {
                    if (where[i].first + where[i].second > br)
                    {
                        bw = i;
                        br = where[i].first + where[i].second;
                        bx = where[i].first;
                        by = where[i].second;
                    }
                    else if (where[i].first + where[i].second == br)
                    {
                        if (where[i].first > bx)
                        {
                            bw = i;
                            br = where[i].first + where[i].second;
                            bx = where[i].first;
                            by = where[i].second;
                        }
                        else if (where[i].first == bx)
                        {
                            if (where[i].second > by)
                            {
                                bw = i;
                                br = where[i].first + where[i].second;
                                bx = where[i].first;
                                by = where[i].second;
                            }
                            else if (where[i].second == by)
                            {
                                if (rabit[br].first > rabit[i].first)
                                {
                                    bw = i;
                                    br = where[i].first + where[i].second;
                                    bx = where[i].first;
                                    by = where[i].second;
                                }
                            }
                        }
                    }
                }
            }
            score[bw] = score[bw] + S;
        }
        else if (sc == 300)
        {
            long id, L;
            cin >> id >> L;
            long wh = pidw[id];
            rabit[wh].second = rabit[wh].second * L;
        }
        else if (sc == 400)
        {
            long maxi = 0;
            for (long i = 0; i < P; i++)
            {
                if (maxi < score[i])
                {
                    maxi = score[i];
                }
            }
            cout << maxi;
        }
    }
}