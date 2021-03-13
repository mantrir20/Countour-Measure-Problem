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

struct cmp{
    bool operator()(cord a, cord y){
        return a.x<y.x;
    }
};
vector<cord> y_set(vector <rectangle> R){
    vector<cord> cord_set_vector;
    set <cord,cmp> cord_set;
    for (int i=0; i< R.size(); i++){
        cord c1, c2;
        c1.x= R[i].y_bottom.x;
        c2.x= R[i].y_top.x;
        cord_set.insert(c1);
        cord_set.insert(c2);
    }
    for(auto i: cord_set){
        cord_set_vector.push_back(i);
    }
    return cord_set_vector;
}

struct cmp_partition{
    bool operator()(const cord &a, const cord &b){
        return a.x<b.x;
    }
};

vector<interval> partition(vector<cord> Y){  
    vector <interval> interval_set;
    sort(Y.begin(),Y.end(),cmp_partition());
    for(int i=0;i<Y.size()-1;i++){
        if(Y[i].x==Y[i+1].x)
            continue;
        interval in1;
        in1.bottom.x=Y[i].x;
        in1.top.x=Y[i+1].x;
        interval_set.push_back(in1);
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

bool cmp_stripe(stripe a, stripe b){
        if(a.y_inter.bottom.x<b.y_inter.bottom.x || (a.y_inter.bottom.x==b.y_inter.bottom.x && a.y_inter.top.x<b.y_inter.top.x ))
            return true;
        return false;
}

struct cmp_stripe2{
    bool operator() (const stripe & a, const stripe & b){
        if(a.y_inter.top.x<b.y_inter.top.x || (a.y_inter.top.x==b.y_inter.top.x && a.y_inter.bottom.x<b.y_inter.bottom.x ))
             return true;
         return false;
    }
    bool operator() (const stripe & left, int right){
        return left.y_inter.top.x < right;
    }
    bool operator() (int left, const stripe & right){
        return left < right.y_inter.top.x;
    }
};

// copy(Sx1,P,x_ext.bottom,xm,Sleft);
void copy(vector<stripe> Sx1, vector<cord> &P,cord bottom,int xm, vector<stripe> &Sleft){
    //vector <stripe> Sprime;
    interval Ix;
    Ix.bottom = bottom;
    Ix.top.x = xm;
    vector <interval> all_Iy = partition(P);
    for(auto intv:all_Iy){
        stripe strp;
        strp.x_inter = Ix;
        strp.y_inter = intv;
        Sleft.push_back(strp);
    }
    sort(Sx1.begin(),Sx1.end(),cmp_stripe);
    sort(Sleft.begin(),Sleft.end(),cmp_stripe);
    for(auto sdash:Sleft){
        // sdash.y_inter.bottom >=  sdash.y_inter.top <=
        auto it = upper_bound(Sx1.begin(),Sx1.end(),sdash.y_inter.bottom.x,cmp_stripe2());
        while(prev(it)->y_inter.bottom.x==sdash.y_inter.bottom.x)
            it = prev(it);
        auto it2 = upper_bound(it,Sx1.end(),sdash.y_inter.top.x,cmp_stripe2()); // NOT SURE IF THIS COMPARATOR WORKS FINE and 
                                                                            // if the above while loop is required because it messes complexity
        if(it>it2) continue;
        else{
            sdash.x_union = it->x_union;
        }
    }
}

bool interval_subset(interval i1, interval i2){
    if( (i2.bottom.x <= i1.bottom.x) && (i2.top.x >=i1.top.x) ) 
        return true;
    return false; 
}

void blacken(vector<stripe> &S, vector<interval> &J){
    for(int i=0;i < S.size();i++){
        for(int j=0; j < J.size(); j++){
            if(interval_subset(S[i].y_inter, J[i])){
                S[i].x_union.push_back(S[i].x_inter); // Doubt if it is push pack or clear and push_back
            }
        }
    }
}

struct comp{
    bool operator()(const interval &i,const interval &j){ 
        if(i.bottom.x<j.bottom.x || (i.bottom.x==j.bottom.x && i.top.x<j.top.x))
            return true;
        return false;
    }
};

// TO DO HAI YE COMPLETE NHI
bool comp2_P(cord a,cord b){
    return a.x<=b.x;
}

void Stripes(vector<edge> V, interval x_ext, vector<interval> &L,
    vector<interval> &R,vector<stripe> &S,vector<cord> &P){ 
    //check definition
    // Case 1
    vector<interval> Lx1,Lx2;
    vector<interval> Rx1,Rx2;
    vector<stripe> Sx1,Sx2;
    vector<cord> Px1,Px2;
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

        cord c1,c2,c3,c4;
        c1.x = INT_MIN; c2.x = V[0].inter.bottom.x; c3.x = V[0].inter.top.x; c4.x = INT_MAX; 
        P.push_back(c1);
        P.push_back(c2);
        P.push_back(c3);
        P.push_back(c4);

        stripe s1;
        s1.x_inter = x_ext;
        //s1.y_inter = partition(); // TO DO
        S.push_back(s1);

        for(int i=0; i< S.size(); i++){
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
        set_intersection(Lx1.begin(),Lx1.end(),Rx2.begin(),Rx2.end(),LR.begin(),comp());
        sort(Lx1.begin(),Lx1.end(),comp());
        sort(Lx2.begin(),Lx2.end(),comp());
        sort(Rx1.begin(),Rx1.end(),comp());
        sort(Rx2.begin(),Rx2.end(),comp());
        
        sort(Px2.begin(),Px2.end(),comp2_P);
        sort(Px1.begin(),Px1.end(),comp2_P);

        set_difference(Lx2.begin(), Lx2.end(), LR.begin(), LR.end(),
            L.begin(), comp()); 
        set_union(L.begin(),L.end(),Lx2.begin(),Lx2.end(),L.begin(),comp());

        set_difference(Rx2.begin(), Rx2.end(), LR.begin(), LR.end(),
            R.begin(), comp()); 
        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp());

        set_union(Rx1.begin(),Rx1.end(),R.begin(),R.end(),R.begin(),comp());

        vector<stripe> Sleft,Sright;
        copy(Sx1,P,x_ext.bottom,xm,Sleft);
        copy(Sx2,P,x_ext.bottom,xm,Sright);
        
        
        //blacken

        set_difference(Rx2.begin(), Rx2.end(), LR.begin(), LR.end(), R.begin(), comp()); 
        blacken(Sleft, R);
        set_difference(Lx1.begin(), Lx1.end(), LR.begin(), LR.end(), R.begin(), comp()); 
        blacken(Sright, R);
        
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
    vector<cord> P;
    Stripes(VRX, base, L, Rt, S, P); // check return type
    
}