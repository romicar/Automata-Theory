#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    char state[n + 1];
    int inp[n + 1][3];
    char outstate[10000];
    int out[10000][3];
    for (int i = 0; i < n; i++)
    {
        cin >> state[i + 1];
        cin >> inp[i + 1][0] >> inp[i + 1][1] >> inp[i + 1][2];
    }
    set<int> init;
    for (int i = 0; i < n; i++)
        init.insert(i + 1);
    int nodetoadd = 1;
    queue<int> q;
    q.push(nodetoadd);
    nodetoadd++;
    map<set<int>, int> allsets;
    allsets[init] = 1;
    vector<set<int>> allsets2(10000);
    allsets2[1] = init;

    while (q.size() > 0)
    {
        int nownode = q.front();
        q.pop();
        set<int> current = allsets2[nownode];
        // now we have to give the state for this current node
        int cntR = 0;
        int cntP = 0;
        int cntS = 0;
        for (set<int>::iterator y = current.begin(); y != current.end(); y++)
        {
            int x = *y;
            if (state[x] == 'R')
                cntR++;
            else if (state[x] == 'P')
                cntP++;
            else
                cntS++;
        }
        int cntMx = cntR;
        if (cntP > cntMx)
            cntMx = cntP;
        if (cntS > cntMx)
            cntMx = cntS;
        int val = 0;
        if (cntMx == cntR)
        {
            outstate[nownode] = 'P';
            val = 1;
        }
        else if (cntMx == cntP)
        {
            outstate[nownode] = 'S';
            val = 2;
        }
        else if (cntMx == cntS)
        {
            outstate[nownode] = 'R';
            val = 0;
        }

        // now that we have assigned the state for the current node, we have to deal with its transitions

        set<int> rockchilds;

        for (set<int>::iterator y = current.begin(); y != current.end(); y++)
        {
            int x = *y;
            if (state[x] == 'R')
            {
                rockchilds.insert(inp[x][val]);
            }
        }

        // now that we have made the rock transition for the nownode, we check if we have to create a new node

        if (rockchilds.size() == 0)
        {
            out[nownode][0] = 1;
        }

        else if (allsets.find(rockchilds) != allsets.end())
        { // this set has come before
            int foundset = allsets[rockchilds];
            out[nownode][0] = foundset;
        }

        else
        { // we create a new node
            allsets[rockchilds] = nodetoadd;
            allsets2[nodetoadd] = rockchilds;
            out[nownode][0] = nodetoadd;
            q.push(nodetoadd);
            nodetoadd++;
        }

        set<int> paperchilds;

        for (set<int>::iterator y = current.begin(); y != current.end(); y++)
        {
            int x = *y;
            if (state[x] == 'P')
            {
                paperchilds.insert(inp[x][val]);
            }
        }

        if (paperchilds.size() == 0)
        {
            out[nownode][1] = 1;
        }

        else if (allsets.find(paperchilds) != allsets.end())
        { // this set has come before
            int foundset = allsets[paperchilds];
            out[nownode][1] = foundset;
        }

        else
        { // we create a new node
            allsets[paperchilds] = nodetoadd;
            allsets2[nodetoadd] = paperchilds;
            out[nownode][1] = nodetoadd;
            q.push(nodetoadd);
            nodetoadd++;
        }

        set<int> scissorchilds;

        for (set<int>::iterator y = current.begin(); y != current.end(); y++)
        {
            int x = *y;
            if (state[x] == 'S')
            {
                scissorchilds.insert(inp[x][val]);
            }
        }

        if (scissorchilds.size() == 0)
        {
            out[nownode][2] = 1;
        }

        else if (allsets.find(scissorchilds) != allsets.end())
        { // this set has come before
            int foundset = allsets[scissorchilds];
            out[nownode][2] = foundset;
        }

        else
        { // we create a new node
            allsets[scissorchilds] = nodetoadd;
            allsets2[nodetoadd] = scissorchilds;
            out[nownode][2] = nodetoadd;
            q.push(nodetoadd);
            nodetoadd++;
        }
    }

    cout << nodetoadd - 1 << endl;

    for (int i = 1; i < nodetoadd; i++)
    {
        cout << outstate[i] << " " << out[i][0] << " " << out[i][1] << " " << out[i][2] << endl;
    }

    return 0;
}