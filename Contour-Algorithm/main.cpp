#include<bits/stdc++.h>
#include <algorithm>
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
    interval inter; // length
    cord cordinate; // x coord 
    edge_type e_type; // l R B T
}edge;

typedef struct stripe{
    interval x_inter;
    interval y_inter;
    vector <interval> x_union;
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

typedef struct newPtype{
    int aext,b,c,dext;
}
//set<stripe> Stripes(set<rectangle> R, rectangle f, )

bool comp(interval &i, interval &j) { 
    if(i.bottom<j.bottom || (i.bottom==j.bottom && i.top<b.top))
        return true;
    return false;
} // must check

bool comp2(,) { 
    if())
        return true;
    return false;
} // must check

void Stripes(vector<edge> V, interval x_ext, 
    vector<interval> &L,
    vector<interval> &R,
    vector<stripe> &S,
    vector<vector<int>> &P
    )
{ //check defination

    // Case 1
    vector<interval> Lx1,Lx2;
    vector<interval> Rx1,Rx2;
    vector<stripe> Sx1,Sx2;
    vector<vector<int>> Px1,Px2;
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
        s1.y_inter = partition(); // TO DO
        S.push_back(s1);

        for(int i=0; i< S.size(); i++)
            if(S[i].y_inter == V[0].inter)
            {
                if(V[0].e_type == 0){
                  Interval int1;
                  int1.bottom = V[0].cordinate;
                  int1.top = x_ext.top;
                  S[i].x_union = vector<interval>{int1};
                }
                else{
                  Interval int1;
                  int1.bottom = x_ext.bottom;
                  int1.top = V[0].cordinate;
                  S[i].x_union = vector<interval>{int1};
                }
            }
    }
    else{
        // Divide
        vector <int> pts;
        vector<edge> V1,V2;
        for(int i=0; i<V.size();i++){
            pts.push_back(V[i].cordinate); // sort by x-coords
        }
        sort(pts.begin(),pts.end());
        int xm = pts[(pts.size()+1)/2];
        // vector<interval> L1,L2,R1,R2;
        for(int i=0;i<V.size();i++){
            if(V[i].cordinate<=xm){
                V1.push_back(V[i]);
            }
            else{
                V2.push_back(V[i]);
            }
        }

        // Conquer
        Interval intt;
        cord c1;
        c1.x = xm;
        intt.bottom = x_ext.bottom;
        intt.top = c1;
        Stripes(V1,intt,Lx1,Rx1,Sx1,Px1);
        Interval intt2;
        cord c2;
        c2.x = xm;
        intt.top = x_ext.top;
        intt.bottom = c2;
        Stripes(V2,intt2,Lx2,Rx2,Sx2,Px2);

        // Merge Merge to get LR = (L1ANDR2)
        vector<interval> LR;
        set_intersection(Lx1.begin(),Lx1.end(),Rx2.begin(),Rx2.end(),LR.begin(),comp);
        sort(Lx1.begin(),Lx1.end(),comp);
        sort(Lx2.begin(),Lx2.end(),comp);
        sort(Rx1.begin(),Rx1.end(),comp);
        sort(Rx2.begin(),Rx2.end(),comp);
        
        sort(Px2.begin(),Px2.end(),comp_P);
        sort(Px1.begin(),Px1.end(),comp_P);

        set_difference(Lx2.begin(), Lx2.end(), LR.begin(), LR.end(),
            L.begin(), comp); 
        set_union(L.begin(),L.end(),L2.begin(),L2.end(),L.begin(),comp);

        set_difference(Rx2.begin(), Rx2.end(), LR.begin(), LR.end(),
            R.begin(), comp); 
        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp);

        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp);

    }
}

set<stripe> rectangle_dac(vector<rectangle> R)
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



