#include <bits/stdc++.h>
#include <windows.h>
#include <omp.h>
#include <thread>
using namespace std;
using ll = int;
using ld = long double;
vector<pair<ll,ll>> moves = {{+1,0},{0,+1},{-1,0},{0,-1}};
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
bool BFS(vector<vector<char>> &vec)
{
    queue<pair<ll,ll>> q;
    q.push({1,1});
    ll n = vec.size();
    ll m = vec[0].size();
    vector<vector<ll>> passed(n,vector<ll> (m,-1));
    passed[1][1] = 1;
    while (!q.empty())
    {
        auto from = q.front();
        q.pop();
        for (auto el : moves)
        {
            ll nextI = from.first + el.first;
            ll nextJ = from.second + el.second;
            if (nextI<n && nextJ<m && nextI>=0 && nextJ>=0 && vec[nextI][nextJ]!='#' && passed[nextI][nextJ]==-1)
            {
                passed[nextI][nextJ] =1;
                q.push({nextI,nextJ});
            }
        }
    }
    if (passed[n-2][m-2]==-1)
    {
        return 0;
    }
    return 1;
}
ll checker(vector<vector<char>> vec)
{
    if (!BFS(vec) || vec[1][1] == '#')
    {
        return -1e9;
    }
    ll n,m;
    n = vec.size();
    m = vec[0].size();
    ll matrix[n][m];
    ll ans =-1e9;
    for (ll i=0; i<n; ++i)
    {
        for (ll j=0; j<m; ++j)
        {
            matrix[i][j] = 0;
        }
    }

    matrix[1][1] = 1;
    ll i= 1;
    ll j = 1;
    ll orient = 2;
    ll step =-1;
    vector<ll> next(4,1e9);
    vector<ll> vals(4,1e9);
    #pragma omp parallel
    #pragma omp for
    while (1)
    {
        step++;
        if (ans>=1e5)
        {
            return 1e9;
        }
        if (i == n-2 && j == m-2)
        {
            ans = step;
            break;
        }
        next[0]=1e9;
        next[1]=1e9;
        next[2]=1e9;
        next[3]=1e9;
        vals[0] = 1e9;
        vals[1] = 1e9;
        vals[2] = 1e9;
        vals[3] = 1e9;
        ll ind =0;
        for (auto el : moves)
        {
            ll nextI = i + el.first;
            ll nextJ = j + el.second;
            if (nextI>=0 && nextJ>=0 && nextI<n && nextJ<m && vec[nextI][nextJ]=='.')
            {
                next[ind] = matrix[nextI][nextJ];
                vals[ind] = matrix[nextI][nextJ];
            }
            ind++;
        }
        sort(vals.begin(),vals.end());
        if (next[0]<next[1] && next[0]<next[2] && next[0]<next[3])
        {
            auto el = moves[0];
            orient = 0;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[1]<next[0] && next[1]<next[2] && next[1]<next[3])
        {
            auto el = moves[1];
            orient = 1;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[2]<next[0] && next[2]<next[1] && next[2]<next[3])
        {
            auto el = moves[2];
            matrix[i+el.first][j+el.second]++;
            orient = 2;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[3]<next[0] && next[3]<next[1] && next[3]<next[2])
        {
            auto el = moves[3];
            matrix[i+el.first][j+el.second]++;
            orient = 3;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[orient]!=1e9 && next[orient] == vals[0])
        {
            auto el = moves[orient];
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[0]!=1e9 && next[0] == vals[0])
        {
            auto el = moves[0];
            orient = 0;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            //  step++;
            continue;
        }
        if (next[1]!=1e9 && next[1] == vals[0])
        {
            auto el = moves[1];
            orient = 1;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[2]!=1e9 && next[2] == vals[0])
        {
            auto el = moves[2];
            orient = 2;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        if (next[3]!=1e9 &&  next[3] == vals[0])
        {
            auto el = moves[3];
            orient = 3;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            // step++;
            continue;
        }
        break;
        // step++;
    }

    return ans;
}
void draw_point (vector<vector<char>> &vec, ll row, ll col)
{
    if (vec[row][col] == '#')
    {
        vec[row][col] = '.';
    }
    else
    {
        vec[row][col] ='#';
    }
}
ll best_score =0;
vector<vector<char>> best_matrix(21,vector<char>(31,'#'));
mutex mtx;
void toParallel(){
    ll n = 21;
    ll m = 31;
    vector<vector<char>> cur_matrix(21,vector<char>(31,'#'));
    for (ll i = 1; i<20; ++i)
    {
        for (ll j = 1; j<30; ++j)
        {
            cur_matrix[i][j] = '.';
        }
    }
    ld T = 100.0;
    ld coef = 0.85;
    srand(time(0));
    #pragma omp parallel for
    #pragma omp for

    for (ll i =0; i<1e8; i++)
    {
        if (T < 0.00001){
            T=100;
        }

        if (best_score>1e5)
        {
            break;
        }

        mtx.lock();
        gotoxy(0,0);
        if (i%1000==0){
            cout<<best_score<<' '<<T<<'\n';
            for (ll i=0; i<n; ++i)
            {
                for (ll j=0; j<m; ++j)
                {
                    cout<<best_matrix[i][j];
                }
                cout<<'\n';
            }
        }

        mtx.unlock();
        ll row = rand()%n;
        ll col = rand()%m;
        if (row == 0)
        {
            ++row;
        }
        if (col==0)
        {
            ++col;
        }
        if (row == n-1)
        {
            --row;
        }
        if (col == m-1)
        {
            --col;
        }
        auto temp = cur_matrix;

        draw_point(cur_matrix,row,col);
        ll temp_score = checker(temp);
        ll cur_score = checker(cur_matrix);

        if (checker(cur_matrix)>=temp_score)
        {
            if (cur_score>=best_score)
            {
                mtx.lock();
                best_matrix = cur_matrix;
                best_score = cur_score;
                mtx.unlock();
            }
            T*=coef;
            continue;
        }
        else
        {
            if (rand()%101<T && cur_score>=0)
            {

            }
            else
            {
                cur_matrix = temp;
            }
        }



        T*=coef;
    }

}
void solve()
{
    thread t1(toParallel);
    thread t2(toParallel);
    thread t3(toParallel);
    thread t4(toParallel);
    thread t5(toParallel);
    thread t6(toParallel);
    thread t7(toParallel);
    thread t8(toParallel);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}
int main()
{
    //freopen("out.txt","w",stdout);
    solve();
}
