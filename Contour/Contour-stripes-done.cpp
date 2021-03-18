#include<bits/stdc++.h>
#include <algorithm>
using namespace std;


int counter = 0;
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
    edge_type e_type; // L R B T
}edge;

typedef struct lru{
    int val; //0,1,2 ==> left, right, undef
}lru;

typedef struct ctree{
    bool empty;
    float x;
    lru side;
    ctree *lson;
    ctree *rson;
    ctree(float a, int b){
        lson = NULL;
        rson = NULL;
        side.val = b;
        x = a;
        empty = false;
    }  
    ctree(bool x){
        empty = true;
    }
}ctree;

typedef struct stripe_contour{
    interval x_inter;
    interval y_inter;
    ctree *tree; //vector<interval> x_union
}stripe_contour;

struct cmp{
    bool operator()(cord a, cord y){
        return a.x<y.x;
    }
};

struct cmp_partition{
    bool operator()(const cord &a, const cord &b){
        return a.x<b.x;
    }
};

bool cmp_stripe(stripe_contour a, stripe_contour b){
        if(a.y_inter.bottom.x<b.y_inter.bottom.x || (a.y_inter.bottom.x==b.y_inter.bottom.x && a.y_inter.top.x<b.y_inter.top.x ))
            return true;
        return false;
}

bool cmp_edge(edge a, edge b){
    if(a.inter.bottom.x<b.inter.bottom.x || (a.inter.bottom.x==b.inter.bottom.x && a.inter.top.x<b.inter.top.x))
        return true;
    return false;
}

bool stripe_subset(stripe_contour s1, stripe_contour s2){
    if((s1.y_inter.bottom.x <= s2.y_inter.bottom.x) && (s1.y_inter.top.x >= s2.y_inter.top.x)) 
        return true;
    return false; 
}

bool interval_subset(interval i1, interval i2){
    if((i1.bottom.x <= i2.bottom.x) && (i1.top.x >= i2.top.x)) 
        return true;
    return false; 
}

bool comparatorSort_yinter(stripe_contour S1, stripe_contour S2){
    if(S1.y_inter.bottom.x < S2.y_inter.bottom.x) return true;
    if(S1.y_inter.bottom.x == S2.y_inter.bottom.x && S1.y_inter.top.x < S2.y_inter.top.x) return true;
    return false;
}

bool comparatorSort_interval(interval i1, interval i2){
    if(i1.bottom.x < i2.bottom.x) return true;
    if(i1.bottom.x == i2.bottom.x && i1.top.x < i2.top.x) return true;
    return false;
}

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
    for(auto i: cord_set)
        cord_set_vector.push_back(i);
    return cord_set_vector;
}

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

void copy(vector<stripe_contour> Sx1, vector<cord> &P,cord bottom,int xm, vector<stripe_contour> &Sleft){
    cout << "****************************Copy Started********************************" << endl;
    interval Ix;
    Ix.bottom = bottom; Ix.top.x = xm;
    vector <interval> all_Iy = partition(P);
    for(auto intv:all_Iy){
        stripe_contour strp;
        strp.x_inter = Ix; 
        strp.y_inter = intv;
        strp.tree = new ctree(true);
        Sleft.push_back(strp);
    }
    vector<stripe_contour> stripe_to_ret;
    for(auto sdash:Sleft){
        for(auto inner:Sx1){
            if(stripe_subset(sdash,inner)){
                cout<<"Inside if \n";
                sdash.tree = inner.tree;
                cout << "Tree Node = " << sdash.tree->x << endl;;
            }
        }
        stripe_to_ret.push_back(sdash);
        // auto it = lower_bound(Sx1.begin(), Sx1.end(), sdash, stripe_subset);
        // if(it!=Sx1.end()) sdash.tree = (*it).tree;
    }
    cout<<"%%%%%%%%% After Loop %%%%%%%%%%% \n";
    for(auto i: stripe_to_ret){
        cout<<"y_inter: "<<"["<<i.y_inter.bottom.x<<","<<i.y_inter.top.x<<"]"<<endl;
    }
    Sleft.clear();
    Sleft=stripe_to_ret;
    cout << "****************************Copy Complted********************************" << endl;
}

void blacken(vector<stripe_contour> &S, vector<interval> &J){
    cout<<"blacken \n";
    sort(J.begin(), J.end(), comparatorSort_interval);
    sort(S.begin(), S.end(), comparatorSort_yinter);
    for(int i=0; i < S.size(); i++){
        stripe_contour testBlacken; //to get the lower bound limits
        testBlacken.y_inter.bottom = S[i].y_inter.bottom;
        testBlacken.y_inter.top =  S[i].y_inter.top;
        testBlacken.tree = new ctree(true);
        auto it = lower_bound(J.begin(), J.end(), testBlacken.y_inter, interval_subset);
        if(it != J.end()){
            S[i].tree->empty = true;
        }
    }
}

bool stripe_match(stripe_contour i1, stripe_contour i2){
    if( (i1.y_inter.bottom.x == i2.y_inter.bottom.x) && (i1.y_inter.top.x == i2.y_inter.top.x) ) 
        return true;
    return false; 
}

vector<stripe_contour> concat(vector<stripe_contour> S1, vector<stripe_contour> S2, vector<cord> P, interval x_int){
    vector<stripe_contour> S;
    cout<<"concat \n";
    sort(S1.begin(), S1.end(), comparatorSort_yinter);
    sort(S2.begin(), S2.end(), comparatorSort_yinter);
    vector<interval> Iy = partition(P);
    for(auto intv:Iy){
        stripe_contour temp;
        temp.x_inter = x_int;
        temp.y_inter = intv;
        temp.tree = new ctree(true);
        S.push_back(temp);
    }
    vector<stripe_contour> ans;
    for(auto strp:S){
        stripe_contour st1;
        st1.tree = new ctree(true);
        stripe_contour st2;
        st2.tree = new ctree(true);
        for(auto strp1:S1){
            if(strp1.y_inter.top.x==strp.y_inter.top.x && strp1.y_inter.bottom.x==strp.y_inter.bottom.x){
                st1 = strp1;
                break;
            }
        }
        for(auto strp2:S2){
            if(strp2.y_inter.top.x==strp.y_inter.top.x && strp2.y_inter.bottom.x==strp.y_inter.bottom.x){
                st2 = strp2;
                break;
            }
        }
        if(st1.tree->empty==false && st2.tree->empty==false){
            strp.tree->x = st1.x_inter.top.x;
            strp.tree->side.val = 2;
            strp.tree->lson = st1.tree;
            strp.tree->rson = st2.tree;
        }
        else if(st1.tree->empty==false && st2.tree->empty==true){
            strp.tree = st1.tree;
        }
        else if(st1.tree->empty==true && st2.tree->empty==false){
            strp.tree = st2.tree;
        }
        else strp.tree->empty = true;
        ans.push_back(strp);
    }
    return ans;
}

struct comp{
    bool operator()(const interval &i,const interval &j){ 
        if(i.bottom.x<j.bottom.x || (i.bottom.x==j.bottom.x && i.top.x<j.top.x))
            return true;
        return false;
    }
};

bool comp2_P(cord a,cord b){
    return a.x<b.x;
}

vector <interval> Intervals_union(vector<interval> arr1, vector<interval> arr2){ 
    if(arr1.size()==0){
        return arr2;
    }
    else if(arr2.size()==0){
        return arr1;
    }
    cout<<"Intervals_union 1\n";
    vector <interval> arr;
    for(auto intr:arr1)
        arr.push_back(intr);
    for(auto intr:arr2)
        arr.push_back(intr);
    sort(arr.begin(),arr.end(),comp());
    cout<<"Intervals_union 2\n";
    int index = 0;  
    for(int i=1; i<arr.size(); i++) { 
        if (arr[index].top.x >= arr[i].bottom.x){  
            arr[index].top.x = max(arr[index].top.x, arr[i].top.x); 
            arr[index].bottom.x = min(arr[index].bottom.x, arr[i].bottom.x); 
        }
        else{
            index++;
            arr[index] = arr[i]; 
        } 
    } 
    cout<<"Intervals_union 3\n";
    vector<interval> ans; 
    for(int i = 0; i <= index; i++){
        interval newI;
        newI.bottom.x = arr[i].bottom.x;
        newI.top.x = arr[i].top.x;
        ans.push_back(newI); 
    } 
    cout<<"Intervals_union 4\n";
    return ans;
}

vector <interval> Intervals_subtraction(vector<interval> arrA, vector<interval> arrB){
    cout << "In subtraction\n";
    vector<interval> temp; //empty
    vector <interval> arr1 = Intervals_union(arrA,temp);
    vector <interval> arr2 = Intervals_union(arrB,temp);
    sort(arr1.begin(),arr1.end(),comp());
    sort(arr2.begin(),arr2.end(),comp());
    int i=0,j=0;
    vector <interval> ans;
    while(i<arr1.size() && j<arr2.size()){
        if(arr1[i].bottom.x == arr2[j].bottom.x){
            if(arr1[i].top.x<arr2[j].top.x){
                arr1[i].bottom.x = arr1[i].top.x;
                arr2[j].bottom.x = arr1[i].top.x;
                i++;    
            }
            else if(arr1[i].top.x>arr2[j].top.x){
                arr1[i].bottom.x = arr2[j].top.x;
                arr2[j].bottom.x = arr2[j].top.x;
                j++;    
            }
            else{
                i++;
                j++;
            }
        }
        else if(arr1[i].bottom.x < arr2[j].bottom.x){
            interval int1;
            int1.bottom.x = arr1[i].bottom.x;
            int1.top.x = min(arr2[j].bottom.x,arr1[i].top.x);
            // i++;
            if(arr1[i].top.x>arr2[j].bottom.x){
                arr1[i].bottom.x = min(arr1[i].top.x,arr2[j].bottom.x);
            }
            else{
                i++;
            }
            ans.push_back(int1);
        }
        else if(arr1[i].bottom.x > arr2[j].bottom.x){
            // interval int1;
            // int1.bottom.x = arr2[j].bottom.x;
            // int1.top.x = min(arr1[i].bottom.x,arr2[j].top.x);
            j++;
            //ans.push_back(int1);
        }
    }
    if(j>=arr2.size()){
        while(i<arr1.size()){
            interval int1;
            int1.bottom.x = arr1[i].bottom.x;
            int1.top.x = arr1[i].top.x;
            i++;
            ans.push_back(int1);
        }
    }
    return ans;
}

struct cmpx{
    bool operator()(cord a, cord b){
        return a.x < b.x;    
    }
};
vector<cord> cords_union(vector<cord> A, vector<cord> B){
    set<cord,cmpx> un;
    vector <cord> ans;
    for(auto c:A)
        un.insert(c);
    for(auto c:B)
        un.insert(c);
    for(auto c:un)
        ans.push_back(c);
    return ans;
}
vector <interval> Intervals_intersection(vector<interval> arr1, vector<interval> arr2) { 
    cout << "In intersection\n";
    if(arr1.empty())
        return arr1;
    if(arr2.empty())
        return arr2;
    int i = 0, j = 0; 
    vector <interval> ans;
    int n = arr1.size(), m = arr2.size(); 
    while (i < n && j < m) { 
        int l = max(arr1[i].bottom.x, arr2[j].bottom.x);  
        int r = min(arr1[i].top.x, arr2[j].top.x); 
        if (l <= r) {
            interval newI;
            newI.bottom.x = l;
            newI.top.x = r;
            ans.push_back(newI); 
        }
        if(arr1[i].top.x < arr2[j].top.x) 
            i++; 
        else
            j++; 
    } 
    return ans;
} 


void Stripes(vector<edge> V, interval x_ext, vector<interval> &L,vector<interval> &R,vector<stripe_contour> &S,vector<cord> &P){
    vector<interval> Lx1,Lx2,Rx1,Rx2;
    vector<stripe_contour> Sx1,Sx2;
    vector<cord> Px1,Px2;
    counter ++; 
    cout << "Inside Stripe call no = " << counter << "\n";
    cout<<"Stripes, x_ext recieved as:["<<x_ext.bottom.x<<","<<x_ext.top.x<<"]"<<endl;
    getchar();
    interval x_ext_save;
    cout << "V size = " << V.size() << "\n";
    if(V.size()==0)
        return;
    if(V.size() == 1){
        cout << "Stripe Base Case Entered" <<endl;
        if(V[0].e_type.type == 0)
            L.push_back(V[0].inter);
        else
            R.push_back(V[0].inter);
        cord c1,c2,c3,c4;
        c1.x = INT_MIN; c2.x = V[0].inter.bottom.x; c3.x = V[0].inter.top.x; c4.x = INT_MAX; 
        P.push_back(c1); P.push_back(c2); P.push_back(c3); P.push_back(c4);
        vector <interval> tmp_intrv = partition(P);
        cout<<"Number of intervals returned: "<<tmp_intrv.size()<<endl;
        for(auto intrv:tmp_intrv){
            stripe_contour s1;
            s1.x_inter = x_ext;
            s1.y_inter = intrv; // TO DO  
            cout << "After Partition Top and bottom are - " << intrv.bottom.x << " " << intrv.top.x <<  endl; 
            s1.tree = new ctree(true);
            S.push_back(s1);
        }

        cout<<"After partition in Base case \n";
        for(int i=0; i< S.size(); i++){
            if(S[i].y_inter.bottom.x == V[0].inter.bottom.x  && S[i].y_inter.top.x == V[0].inter.top.x ){
                if(V[0].e_type.type == 0){
                  //interval int1;int1.bottom = V[0].cordinate;int1.top = x_ext.top; S[i].x_union = vector<interval>{int1}; // B
                  S[i].tree = new ctree((float)V[0].cordinate.x, 0); // left
                    cout << "Create tree in base case 1\n";
                }
                else{
                    S[i].tree = new ctree((float)V[0].cordinate.x, 1); // right
                    cout << "Create tree in base case 2\n";
                }
            }
        }
        counter--;
        cout<<"Returning base case "<<counter<<" \n";
    }
    else{
        // Divide
        vector <int> pts;
        vector<edge> V1,V2;
        sort(V.begin(),V.end(),cmp_edge);
        int xm;
        if(V.size()%2==0) xm = ((V[V.size()/2].cordinate.x) + (V[(V.size()/2)-1].cordinate.x) )/ 2;
        else xm = V[V.size()/2].cordinate.x;
        cout << "Xm is : " << xm << "\n";
        for(int i=0;i<V.size();i++){
            if(V[i].cordinate.x<=xm) V1.push_back(V[i]);
            else V2.push_back(V[i]);
        }
        cout << "V1 size : " << V1.size() << " V2 size : " << V2.size() << "\n";
        // Conquer
        interval intt;
        cord c1; 
        c1.x = xm;
        intt.bottom = x_ext.bottom;
        intt.top.x = xm;
        Stripes(V1,intt,Lx1,Rx1,Sx1,Px1);
        // x_ext_save=x_ext;
        cout<<"**********After returning from Left Half*************\n";
        for(auto i: Sx1)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl;
        interval intt2;
        cord c2; 
        c2.x = xm;
        intt2.bottom.x = xm;
        intt2.top = x_ext.top;
        Stripes(V2,intt2,Lx2,Rx2,Sx2,Px2);
        cout<<"**********After returning from Right Half*************\n";
        for(auto i: Sx2)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl;
        
        // Merge 
        sort(Lx1.begin(),Lx1.end(),comp()); sort(Lx2.begin(),Lx2.end(),comp());
        sort(Rx1.begin(),Rx1.end(),comp()); sort(Rx2.begin(),Rx2.end(),comp());
        sort(Px2.begin(),Px2.end(),comp2_P); sort(Px1.begin(),Px1.end(),comp2_P);
        sort(Sx1.begin(),Sx1.end(),cmp_stripe); sort(Sx2.begin(),Sx2.end(),cmp_stripe);
        cout<<"Before Set operations inside stripes \n";
        vector<interval> LR = Intervals_intersection(Lx1,Rx2);
        cout<<"AFTER Set operations inside stripes \n";
        vector<interval> Lm = Intervals_subtraction(Lx1,LR);
        cout<<"Subtraction worked \n";
        cout<<"Lm Size: "<<Lm.size()<<endl;
        L = Intervals_union(Lm,Lx2);
        cout<<"After intervals \n";
        Lm = Intervals_subtraction(Rx2,LR);
        R = Intervals_union(Rx1,Lm);
        P = cords_union(Px1,Px2);
        vector<stripe_contour> Sleft,Sright;
        copy(Sx1,P,x_ext.bottom,xm,Sleft);
        copy(Sx2,P,x_ext.bottom,xm,Sright);
        cout<<"After copy (Sleft): \n";
        for(auto i: Sleft)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl; 
        cout<<"After copy (Sright): \n";
        for(auto i: Sright)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl; 
        //blacken
        Lm = Intervals_subtraction(Rx2,LR);
        blacken(Sleft, Lm);
        Lm = Intervals_subtraction(Lx1,LR);
        blacken(Sright, R);
        cout<<"After blacken (Sleft): \n";
        for(auto i: Sleft)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl;
        cout<<"After blacken (Sright): \n";
        for(auto i: Sright)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl;

        //concat
        vector<stripe_contour> S_ret;
        S.clear();
        S = concat(Sleft,Sright,P,x_ext);
        cout<<"After concat: \n";
        for(auto i: S)
            cout<<"y_inter: ["<<i.y_inter.bottom.x<<", "<<i.y_inter.top.x<<"]"<<endl;
        counter--;
        cout << "Retuning from Stripes Case 2" << counter <<"..............................................." <<'\n';
        // answer in S*/
    }
}

vector <stripe_contour> rectangle_dac(vector<rectangle> R,vector<edge> &VRX ){
    cout<<"Entering Rectangle_Dac \n";
    for(int i=0;i < R.size(); i++){
        edge e1;
        e1.inter.bottom.x = R[i].y_bottom.x;
        e1.inter.top.x = R[i].y_top.x;
        e1.cordinate.x = R[i].x_left.x;
        e1.e_type.type = 0;
        edge e2;
        e2.inter.bottom.x = R[i].y_bottom.x;
        e2.inter.top.x = R[i].y_top.x;
        e2.cordinate.x = R[i].x_right.x;
        e2.e_type.type = 1;
        VRX.push_back(e1);
        VRX.push_back(e2);
    }
    cout << '\n';
    interval base;
    base.bottom.x = INT_MIN;
    base.top.x = INT_MAX;
    vector<interval> L,Rt;
    vector<stripe_contour> S;
    vector<cord> P;
    Stripes(VRX, base, L, Rt, S, P); // check return type
    cout <<"Stipes Completed" << endl;
    cout<<"Returning from rectangle_dac\n";
    return S;
}

bool interval_sort_cmp (interval a, interval b){
    if(a.bottom.x<b.bottom.x || (a.bottom.x==b.bottom.x && a.top.x<b.top.x))
        return true;
    return false;
}

// TO DO
vector <int> ass;
void union_intervals(ctree *tree){
    if(tree==NULL) return;
    else if(tree->lson==NULL && tree->rson==NULL){
        cout << "Pushing " << tree->x << "\n";
        ass.push_back((int)tree->x);
    }
    else{
        union_intervals(tree->lson);
        union_intervals(tree->rson);
    }
}

void intervals(edge h, stripe_contour s,vector <interval> &J){
    union_intervals(s.tree);
    vector <interval> uintervals;
    for(int i=0;i<ass.size()-1;i+=2){
        interval tmp;
        tmp.bottom.x = ass[i];
        tmp.top.x = ass[i+1];
        uintervals.push_back(tmp);
    }
    // intersection of h.x_interval and sx_union
    vector<interval> tmp1; 
    tmp1.push_back(h.inter);
    vector<interval> int_interval = Intervals_intersection(tmp1,uintervals);
    J = Intervals_subtraction(tmp1,int_interval);
}

vector<line_segment> cpieces;
void contour_pieces(edge h, vector<stripe_contour> S){
    // stripe_contour s;
    // s.tree = new ctree(true);
    vector <interval> J;
    if(h.e_type.type==2){
        for(auto strp:S){
            if(strp.y_inter.top.x == h.cordinate.x){
                cout << "Contour Pieces 1 " ;
                cout << strp.tree->x << endl;
                vector <interval> J;
                intervals(h,strp,J);
                for(auto intrv:J){
                    line_segment LS;
                    LS.inter = intrv;
                    LS.cordinate = h.cordinate;
                    cpieces.push_back(LS);
                }
            }
        }
    }
    else{
        for(auto strp:S){
            if(strp.y_inter.bottom.x  == h.cordinate.x){
                cout << "Contour Pieces 2 " ;
                cout << strp.tree->x << endl;
                vector <interval> J;
                intervals(h,strp,J);
                for(auto intrv:J){
                    line_segment LS;
                    LS.inter = intrv;
                    LS.cordinate = h.cordinate;
                    cpieces.push_back(LS);
                }
            }
        }
    }
    cout << "Contour Pieces End\n" ;
}

void create_horizontal_edge(vector<rectangle> R, vector<edge> &VRX_horizontal){
    cout << "Creating Horizontal Edges" << endl;
    for(int i=0;i < R.size(); i++){
        edge e1;
        e1.inter.bottom.x = R[i].x_left.x;
        e1.inter.top.x = R[i].x_right.x;
        e1.cordinate.x = R[i].y_bottom.x;
        e1.e_type.type = 2;
        edge e2;
        e2.inter.bottom.x = R[i].x_left.x;
        e2.inter.top.x = R[i].x_right.x;
        e2.cordinate.x = R[i].y_top.x;
        e2.e_type.type = 3;
        VRX_horizontal.push_back(e1);
        VRX_horizontal.push_back(e2);
        cout << "## EDGE ADDED ##" << endl;
        cout << "EDGE BOTTOM = " << e1.inter.bottom.x << endl;
        cout << "EDGE TOP = " << e1.inter.top.x << endl; 
        cout << "EDGE Y-Intercept = " << e1.cordinate.x << endl; 
        cout << "EDGE TYPE = " << e1.e_type.type << "\n";
        cout << endl;
        cout << "## EDGE ADDED ##" << endl;
        cout << "EDGE BOTTOM = " << e2.inter.bottom.x << endl;
        cout << "EDGE TOP = " << e2.inter.top.x << endl; 
        cout << "EDGE Y-Intercept = " << e2.cordinate.x << endl; 
        cout << "EDGE TYPE = " << e2.e_type.type << "\n";
    }
}

int main(){
    int n;
    cout << "Number of Rectangles?\n";
    cin >> n;
    cout << "Enter L(x) R(x) B(y) T(y)\n";
    vector <rectangle> R;
    int x1,x2,y1,y2;
    for(int i=0;i<n;i++){
        cin >> x1 >> x2 >> y1 >> y2;
        rectangle newR;
        newR.x_left.x = x1;
        newR.x_right.x = x2;
        newR.y_bottom.x = y1;
        newR.y_top.x = y2;
        R.push_back(newR);
    }
    vector <edge> VRX;
    vector <stripe_contour> S = rectangle_dac(R, VRX);
    cout << "Stripes obtained : \n";
    for(auto strp:S){
        cout << strp.y_inter.bottom.x << " " << strp.y_inter.top.x << " " << "\n";
        cout << strp.x_inter.bottom.x << " " << strp.x_inter.top.x << " " << "\n";    
    }
    vector<edge> VRX_horizontal;
    create_horizontal_edge(R, VRX_horizontal);
    for(auto edg: VRX_horizontal)
        contour_pieces(edg,S);
    // for(int i=0;i<S.size();i++){
    //    // cout << S[1].tree->lson->rson;
    // }
    cout << "*****Printing ass ******" << endl;
    for(int i=0;i<ass.size();i++)
        cout << ass[i] << " ";
    cout << endl;
    //sort(cpieces.begin(),cpieces.end(),cpieces);
    // int clength_top_bottom = 0;
    // int clength_left_right = 0;
    // map <pair<int,int>,int> mp;
    // for(auto ls:cpieces){
    //     cout << ls.inter.bottom.x << " " << ls.inter.top.x << " " << ls.cordinate.x << "\n";
    //     x1 = ls.inter.bottom.x;
    //     x2 = ls.inter.top.x;
    //     y1 = y2 = ls.cordinate.x;
    //     //clength_top_bottom += x1-x2;
    //     //if(mp.find({x1,x2})!=mp.end()){ // vertical edge contour
    //       //  clength_left_right =  clength_left_right + (2*(y1 - mp[{x1,x2}]));
    //     //}
    // }
}