/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * Created By : Aditya Agarwal
 * IT, MNNIT-ALLAHABAD 
 * aditya.mnnit15@gmail.com
 _._._._._._._._._._._._._._._._._._._._._.*/


#include<bits/stdc++.h>
using namespace std;

#define MP make_pair
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define PER(i,a,b) for(int i=b;i>=a;i--)
#define X first
#define Y second

 //i/o
#define inp(n) scanf("%d",&n)
#define inpl(n) scanf("%lld",&n)
#define inp2(n,m) inp(n), inp(m)
#define inp2l(n,m) inpl(n), inpl(m)


//cost
#define MOD 1000000007
#define MOD_INV 1000000006
#define MAX 100009
#define INF 999999999
#define mp make_pair
typedef long long ll;
typedef pair< pair<ll,ll>,ll > pairs;

void print_result(vector<pair<int,int> > points,
				vector<pair<int,int> > centroids,int points_centroid[10000],int n,int k){
	rep(j,k){
		cout<<"Cluster "<<j+1<<" with centroid at "<<centroids[j].X<<" "<<centroids[j].Y<<endl;
		rep(i,n){
			if(points_centroid[i]==j){
				cout<<points[i].X<<" "<<points[i].Y<<endl;
			}
		}
	}

}

vector<pair<int,int> > generate_random_centroids(int k,int maxx,int minx,int maxy,int miny){

	int dx=(maxx-minx)/k,dy=(maxy-miny)/k;
	cout<<dx<<" "<<dy<<endl;
	vector<pair<int,int> > ans;
	REP(i,1,k){
		ans.pb(MP(minx+i*dx,miny+i*dy));
	}

	return ans;
}

int calculate_distance(pair<int,int> x,pair<int,int> y){
	int dist=sqrt((x.X-y.X)*(x.X-y.X)+(x.Y-y.Y)*(x.Y-y.Y));
	return dist;
}

void allocate_centroids(int points_centroid[10000],vector<pair<int,int> > points,
						vector<pair<int,int> > centroids,int n,int k){
	rep(i,n){
		int min=INF;
		rep(j,k){
			int dist=calculate_distance(points[i],centroids[j]);
			if(dist<min){
				min=dist;
				points_centroid[i]=j;
			}
		}
	}
}

void K_means_algorithm(vector<pair<int,int> > points,int n,int k){
	vector<pair<int,int> > centroids(k+1);
	int maxx=-INF,minx=INF,maxy=-INF,miny=INF;
	rep(i,n){
		maxx=max(maxx,points[i].X);
		minx=min(minx,points[i].X);
		maxy=max(maxy,points[i].Y);
		miny=min(miny,points[i].Y);
	}
	centroids = generate_random_centroids(k,maxx,minx,maxy,miny);
	int points_centroid[n+1];

	//Initial Distribution

	allocate_centroids(points_centroid,points,centroids,n,k);

	int p=1;
	while(1){
		int flag=0;

		cout<<"Centroids in "<<p<<" iterations are"<<endl;
		rep(i,k){
			cout<<centroids[i].X<<" "<<centroids[i].Y<<endl;
		}
		rep(i,k){

			int sumx=0,sumy=0,total_points=0;
			rep(j,n){
				if(points_centroid[j]==i){
					sumx+=points[j].X;
					sumy+=points[j].Y;
					total_points++;
				}
			}

			sumx/=total_points;
			sumy/=total_points;

			if(centroids[i].X!=sumx || centroids[i].Y!=sumy){
				flag=1;
				centroids[i].X=sumx;
				centroids[i].Y=sumy;
			}
		}
		if(flag==0){
			cout<<"The k means algorithm terminated in the "<<p<<" iteration"<<endl;
			print_result(points,centroids,points_centroid,n,k);
			break;
		}
		else
			allocate_centroids(points_centroid,points,centroids,n,k);
		p++;
	}
}

int main(){
	int n,k;
	cout<<"Enter the value of k"<<endl;
	inp(k);
	cout<<"Enter the value of n"<<endl;
	inp(n);
	int x,y;
	cout<<"Enter the points"<<endl;
	vector<pair<int,int> > points;
	rep(i,n){
		inp2(x,y);
		points.pb(MP(x,y));
	}
	K_means_algorithm(points,n,k);

	return 0;
}
