#include<bits/stdc++.h>
using namespace std;

typedef struct cord{
    int x;
}cord;

typedef struct point{
    cord x;
    cord y;
}point;

typedef struct interval{
    cord bottom;
    cord top;
}interval;

typedef struct line_segment{
    interval inter;
    cord cordinate;
}line_segment;

typedef struct rectangle{
    cord x_left;
    cord x_right;
    cord y_bottom;
    cord y_top;
}rectangle;

typedef struct edge_type{
    int type; // 0,1,2,3 - left,right,bottom,top
}edge_type;



typedef struct edge{
    interval inter;
    cord cordinate;
    edge_type e_type;
}edge;

typedef struct stripe{
    interval x_inter;
    interval y_inter;
    set<interval> x_union;
}point;

set<point> union_ret(set<rectangle> R)
{

}

cord y_set(set<rectangle> R)
{

}

set<interval> partition(set<cord> Y)
{

}

set<cord> x_proj(set<point> p)
{

}

set<interval> intervals(set<cord> c)
{

}

//set<stripe> Stripes(set<rectangle> R, rectangle f, )

void Stripes(vector<edge> V, interval x_ext)
{
    vector<interval> L, R;
    vector<vector<int>> P; // check this defination
    vector<stripe> S; //check defination
    if(V.size() == 1)
    {
        if(V[0].e_type.type == 0)
        {
            L.push_back(V[0].inter);
        }
        else
        {
            R.push_back(V[0].inter);
        }

        P.push_back(vector<int>());
        P[0].push_back(INT_MIN);
        P[0].push_back(V[0].inter.bottom.x);
        P[0].push_back(V[0].inter.top.x);
        P[0].push_back(INT_MAX);

        stripe s1;
        s1.x_inter = x_ext;
        s1.y_inter = partition();
        S.push_back(s1);

        for(int i=0; i< S.size(); i++)
            if(S[i].y_inter == V[0].inter)
            {
                if(V[0].e_type == 0) S[i].x_union = 
                else S[i]
            }
    }
    else
    {

    }
}

set<stripe> recatngle_dac(vector<rectangle> R)
{
    vector<edge> VRX;
    for(int i=0;i < R.size(); i++)
    {
        edge e1;
        e1.inter.bottom = R[i].y_bottom;
        e1.inter.top = R[i].y_top;
        e1.cordinate = R[i].x_left;
        e1.e_type.type = 0;


        edge e2;
        e2.inter.bottom = R[i].y_bottom;
        e2.inter.top = R[i].y_top;
        e2.cordinate = R[i].x_right;
        e2.e_type.type = 1;

        VRX.push_back(e1);
        VRX.push_back(e2);
    }

    interval base;
    base.bottom.x = INT_MIN;
    base.top.x = INT_MAX;
    Stripes(VRX, base); // check return type
    
}



