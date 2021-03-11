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
}stripe;

set<point> union_ret(set<rectangle> R)
{

}

vector<cord> y_set(set<rectangle> R)
{
    vector<cord> cord_set;
    for (int i=0; i< R.size(); i++){
        cord c1, c2;
        c1.x= R[i].y_bottom;
        c2.x= R[i].y_top;
        vector<cord>::iterator itr1, itr2;
        itr1=find(cord_set.begin(), cord_set.end(), c1);
        if(itr1==cord_set.end()){
            cord_set.push_back(c1);
        }
        itr2=find(cord_set.begin(), cord_set.end(), c2);
        if(itr2==cord_set.end()){
            cord_set.push_back(c2);
        }
    }
    return cord_set;
}

vector<interval> partition(vector<cord> Y)
{   
    vector <interval> interval_set;
    int y_max=INT_MIN, y_min=INT_MAX;
    for(int i=0; i<Y.size(); i++){
        if(Y[i].x>=y_max){
            y_max=Y[i].x;
        }
        if(Y[i].x<=y_min){
            y_min=Y[i].x;
        }
    }
    for(int i=0; i<Y.size(); i++){
        int y1=Y[i].x;
        for(int j=0; j<Y.size(); j++){
            if(i==j){
                continue;
            }
            int y2=Y[j].x;
            if(y1<y2){
                if(y_max<=y1 || y_min>=y2){
                    interval in1;
                    in1.bottom.x=y1;
                    in1.top.x=y2;
                    vector<interval>::iterator itr1;
                    itr1=find(interval_set.begin(), interval_set.end(), in1);
                    if(itr1==interval_set.end()){
                        interval_set.push_back(in1);
                    }
                }
            }
        }
    }
    return interval_set;
}

set<cord> x_proj(set<point> p){

}

set<interval> intervals(set<cord> c){

}

typedef struct newPtype{
    int aext,b,c,dext;
}newPtype;

//set<stripe> Stripes(set<rectangle> R, rectangle f, )

bool comp(interval &i, interval &j) { 
    if(i.bottom.x<j.bottom.x || (i.bottom.x==j.bottom.x && i.top.x<j.top.x))
        return true;
    return false;
} // must check

bool comp2_P(){ 
    if(1)
        return true;
    return false;
} // must check

// copy(Sx1,P,x_ext.bottom,xm,Sleft);
void copy(vector<stripe> &Sx1, vector<vector<int>> &P,cord bottom,int xm, vector<stripe> &Sleft){
    vector <stripe> Sprime;
    interval Ix;
    Ix.bottom = bottom;
    Ix.top.cord.x = xm;
    for(intervalsinP:P){
        interval Iy;
        Iy.bottom.cord.x = intervalsinp[1];
        Iy.top.cord.x = intervalsinp[2];
        Stripe tmpStrp;
        tmpstrp.x_inter = Ix;
        tmpstrp.y_inter = Iy;
        Sprime.push_back(tmpStrp);
    }
    for(strp:Sx1){
        if(strp.y_inter ) // ye kya bakchodi hai paper me koi samjhao
    }
}
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
            if(S[i].y_inter.bottom.x == V[0].inter.bottom.x  && S[i].y_inter.top.x == V[0].inter.top.x )
            {
                if(V[0].e_type.type == 0){
                  interval int1;
                  int1.bottom = V[0].cordinate;
                  int1.top = x_ext.top;
                  S[i].x_union = vector<interval>{int1};
                }
                else{
                  interval int1;
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
            pts.push_back(V[i].cordinate.x); // sort by x-coords
        }
        sort(pts.begin(),pts.end());
        int xm = pts[(pts.size()+1)/2];
        // vector<interval> L1,L2,R1,R2;
        for(int i=0;i<V.size();i++){
            if(V[i].cordinate.x<=xm){
                V1.push_back(V[i]);
            }
            else{
                V2.push_back(V[i]);
            }
        }

        // Conquer
        interval intt;
        cord c1;
        c1.x = xm;
        intt.bottom = x_ext.bottom;
        intt.top = c1;
        Stripes(V1,intt,Lx1,Rx1,Sx1,Px1);
        interval intt2;
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
        
        sort(Px2.begin(),Px2.end(),comp2_P);
        sort(Px1.begin(),Px1.end(),comp2_P);

        set_difference(Lx2.begin(), Lx2.end(), LR.begin(), LR.end(),
            L.begin(), comp); 
        set_union(L.begin(),L.end(),Lx2.begin(),Lx2.end(),L.begin(),comp);

        set_difference(Rx2.begin(), Rx2.end(), LR.begin(), LR.end(),
            R.begin(), comp); 
        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp);

        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp);

        vector<stripe> &Sleft,
        vector<stripe> &Sright,
        copy(Sx1,P,x_ext.bottom,xm,Sleft);
        copy(Sx2,P,x_ext.bottom,xm,Sright);
        //blacken
        //concat results

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

    vector<interval> L,Rt;
    vector<stripe> S;
    vector<vector<int>> P;
    Stripes(VRX, base, L, Rt, S, P); // check return type
    
}