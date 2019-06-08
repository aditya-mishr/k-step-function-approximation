#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;


int main()
{
	int k , f;
	//ifstream infile;
	//infile.open("input1.txt");
	int size;
	cin>>k>>f;
	cin>>size;



	//vector <vector <int> > points;
	int points[size][2];
	//vector <vector <float> > E;
	//vector <vector <int> > G;
	
	//cout<<"r"<<endl;
	//vector <vector<float> > D;
	cout<<k<<endl;
	//vector <int > p;
	int a,b;
	for (int i=0; i<size;i++)
	{
		//cout<<i<<endl;
		cin>>points[i][0]>>points[i][1];
		//infile>>a>>b;
		//p.push_back(a);
		//p.push_back(b);
		//points.push_back(p);
		//vector<int>().swap(p);
		//cout<<"r"<<endl;
	}

	if(k==size)
	{
		int i;
		for( i=0;i<size;i++)
		{
			cout<<points[i][0]<<" "<<points[i][1]<<endl;
		}
		//cout<<i<<endl;
	}
	else
	{

		float E[k+1][size];
		float G[k+1][size];
		//cout<<"r"<<endl;
		float D[size][size];
	
	
		if(f==0)
		{
			//vector < vector <float> > A;
			//vector <float> a;
			//vector <float> d;
			//cout<<"a"<<endl;
			float A[size][size];
			//cout<<"a"<<endl;
			for(int i=0;i<size;i++)
			{
				float sum=0.0;
			
				for (int j=0;j<size;j++)
				{
					if (j<i)
					A[i][j]=0.0;
				//a.push_back(0);

					else
					{
						sum =sum+points[j][1];
						A[i][j]=sum/(j-i+1);
					//a.push_back(sum/(j-i+1));
					}
				}
				//A.push_back(a);
				//vector<float>().swap(a);
			}
			//cout<<"A complete"<<endl;
			for(int i=0;i<size;i++)
				{
				float sum=0;
				for (int j=0;j<size;j++)
				{
					if(j<i)
					D[i][j]=0.0;
					//d.push_back(0);
					
					else
					{
				  		sum=sum+points[j][1]*points[j][1];

		 				
						//d.push_back(sum/(j-i+1));
						D[i][j]=(sum-A[i][j]*A[i][j]*(j-i+1))/(j-i+1);
						//cout<<D[i][j]<<endl;
			 		}
				}
					//D.push_back(d);
					//cout<<"a"<<endl;
				//vector<float>().swap(d);
	 		}


			//cout<<"D complete"<<endl;
	 		//vector<float> e ;
	 		//vector<int>g;
			for(int j=0;j<size;j++)
				{
			
					//e.push_back(D[0][j]);
					E[0][j]=D[0][j];
					G[0][j]=0;
				}
				//E.push_back(e);
				//G.push_back(g);
				//vector<float>().swap(e);
				//vector<int>().swap(g);

			for(int i=1;i<(k+1);i++)
				{
					for (int j=0;j<size;j++)
					{
						float min_val=1000000000000000000000000.0;
						int min_x;
						if (j<=i)
						{
							E[i][j]=0.0;
							G[i][j]=j;
						}
			
						else
						{
							for (int s=0;s<j;s++)
							{
								float val=E[i-1][s]*(s-i+2)+D[s+1][j]*(j-s);
									if(val< min_val)
									{
										min_val=val;
										min_x=s+1;
									}
							}
							E[i][j]=(min_val/(j-i+1));
							G[i][j]=(min_x);
						}
					}
						//E.push_back(e);
						//G.push_back(g);	
						//vector<float>().swap(e);
						//vector<int>().swap(g);
				}
			//cout<<"E G complete"<<endl;
			int s, j;
			s=k;
			j=size-1;
			stack < pair <int,float> > out;
			for (int i=0;i<k;i++)
				{
					int x=G[s-1][j];
					out.push(make_pair(points[x][0],A[x][j]));
					s--;
					j=x-1;

				}

			while(!out.empty())
			{
				cout<< out.top().first << " "<< out.top().second <<endl;
				out.pop();
			}
		}



		if(f==1)
		{	
			float m[size][size];
			for(int i=0;i<size;i++)
			{	
				float min=100000000.0,max=0;
				for (int j=0;j<size;j++)
				{
					if(i==j)
					{
						
						m[i][j]=points[i][1];
					}
					else if(j<i)
					{
						
						m[i][j]=m[j][i];
					}
					else{
						
							if(min>points[j][1])
							min=points[j][1];
							if(max<points[j][1])
							max=points[j][1];
							m[i][j]=(min+max)/2.0;	
					}
				}
			}

			for(int i=0;i<size;i++)
			{	
				float min=0,max=0;
				for (int j=0;j<size;j++)
				{
					if(i==j)
					{	
						max=min=points[j][1];
						D[i][j]=0;
					}
					else if(j<i)
					{
						D[i][j]=D[j][i];
					}
					else
					{		
						if(min>points[j][1])
						min=points[j][1];
						if(max<points[j][1])
						max=points[j][1];
						float abs = max-m[i][j];
						float abs1= m[i][j]-min;
						D[i][j]=abs > abs1 ? abs : abs1;
					}
				}
			}

			for(int j=0;j<size;j++)
			{
				E[0][j]=D[0][j];
				G[0][j]=0;
			}

			for(int i=1;i<(k+1);i++)
			{
				for (int j=0;j<size;j++)
				{
					float min_val=10000000000000000.0;
					int min_x;
					if(j<=i)
					{
						E[i][j]=0.0;
						G[i][j]=j;
					}
					else
					{
						for(int s=0;s<j;s++)
						{
							float val = (E[i-1][s] > D[s+1][j] ? E[i-1][s] : D[s+1][j]);
							if(val< min_val)
							{
								min_val=val;
								min_x=s+1;
							}

						}
						E[i][j]=min_val;
						G[i][j]=min_x;
					}
				}
			}
			int s, j;
			s=k;
			j=size-1;
			stack < pair <int,float> > out;
			for (int i=0;i<k;i++)
			{
				int x=G[s-1][j];
				out.push(make_pair(points[x][0],m[x][j]));
					s--;
				j=x-1;

			}
			while(!out.empty())
			{
				cout<< out.top().first << " "<< out.top().second <<endl;
				out.pop();
			}
		}
	}

	return 0;
}
