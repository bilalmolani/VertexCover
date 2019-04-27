#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <queue>
#include <list>
#include <algorithm>
#include<pthread.h>
#include <time.h>


// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"



using namespace std;
int vertx=0;
list<int>* AdjList = NULL;
list<int>* AdjList1 = NULL;
vector<int> edges;
bool noedge;
static double timespec_to_double(struct timespec &ts)
{
    const double ns_to_sec= 1.0e-9;
    double t= double(ts.tv_sec) + double(ts.tv_nsec)*ns_to_sec;
    return t;
}

void* solve_minisat(void *used){
	clockid_t clock_id;
    struct timespec ts;
	pthread_getcpuclockid(pthread_self(),&clock_id);
    clock_gettime(clock_id,&ts);
	double cpuTime0=clock_gettime(clock_id,&ts);
for(int k =1; k<= vertx; k++){
 std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    vector<Minisat::Lit> allLits;
    vector<int> minVC;
    minVC.clear();
    bool minvcfound = false;
					allLits.clear();

					for(int atoms =0; atoms < (vertx*k); atoms++){
						Minisat::Lit lit1;
		   				lit1 = Minisat::mkLit(solver->newVar());
		   				allLits.push_back(lit1);
					}

				

					Minisat::vec<Minisat::Lit> clause1, clause2, clause3, clause4;
					for(int abc = 0; abc < k; abc++) {
						clause1.clear();
						for(int clauseSize = 0; clauseSize < vertx; clauseSize++){
							clause1.push(allLits[(abc*vertx)+clauseSize]);
						}
						solver->addClause(clause1);
					}

					for (int abc = 0; abc < vertx; abc++) {
						for(int p=0; p<k;p++){
							for(int q=p+1; q<k; q++){
								clause2.clear();
								clause2.push(~allLits[(p*vertx)+abc]);
								clause2.push(~allLits[(q*vertx)+abc]);
								solver->addClause(clause2);
							}
						}
					}

					for(int abc = 0; abc < k; abc++){
						for(int p =0; p< vertx; p++){
							for(int q=p+1; q< vertx; q++){
								clause3.clear();
								clause3.push(~allLits[(abc*vertx)+p]);
								clause3.push(~allLits[(abc*vertx)+q]);
								solver->addClause(clause3);
							}
						}
					}

				

					for(unsigned int abc =0; abc<edges.size(); abc=abc+2){
						clause4.clear();
						for(int clauseSize = 0; clauseSize < k; clauseSize++){
							clause4.push(allLits[edges[abc]+(clauseSize*vertx)]);
							clause4.push(allLits[edges[abc+1]+(clauseSize*vertx)]);
						}
						solver->addClause(clause4);
					}

					bool res = solver->solve();
		    	
		    		if (res == true){
		    			minVC.clear();
		    			minvcfound = true;
		    		
		    			 for(int atoms =0; atoms < (vertx*k); atoms++){
		    			 	if (Minisat::toInt(solver->modelValue(allLits[atoms])) == 0){
		    			 		if (atoms<vertx){
		    			 			minVC.push_back(atoms);
		    			 		}
		    			 		else {
		    			 			minVC.push_back(atoms%vertx);
		    			 		}
		    			 	}
		    			 }
		    			 std::sort(minVC.begin(), minVC.end());
		    			 cout<<"CNF-SAT-VC: ";
		    			 for(unsigned int minvc=0; minvc < minVC.size(); minvc++){
		    			 	cout << minVC[minvc];
		    			 	if (minvc < minVC.size()-1){
		    			 		cout << ",";
		    			 	}
		    			 	else {
		    			 		cout << endl;
		    			 	}
		    			 }
		    		}
		    		else {
		    			
		    			;
		    		}
                   
		    		if(minvcfound == true){
		    			minvcfound = false;
		    			break;
		    		}
               //noedge=true;
		    	
		    		solver.reset (new Minisat::Solver());
		    	} 
	clock_gettime(clock_id,&ts);
    double cpuTime1=timespec_to_double(ts);
 //   std::cout << "Time: MINISAT solver:  " << cpuTime1-cpuTime0 << std::endl;	    	

}

void* Approx_1(void *unused){
	clockid_t clock_id;
    struct timespec ts;
	pthread_getcpuclockid(pthread_self(),&clock_id);
    clock_gettime(clock_id,&ts);
	double cpuTime0=clock_gettime(clock_id,&ts);
         // 	AddLists_cp = new list<int>[vertexx];
                vector<int> A2VC_cp;
                A2VC_cp.clear();
                int vertexx = vertx;
                list<int>* AddLists_cp = AdjList;
                bool noedge = true;
				while (noedge==true){
			//	int ivert=vertx;
				int max_size=-1;
				int temp=-1;
				int f_u;
				int temp2;
//				list <int> :: iterator it;
//				for (int u=0;u<vertexx;u++){
//
//					for(it = AddLists_cp[u].begin(); it != AddLists_cp[u].end(); it++){
//
//					cout<<*it<<" ";
//						}
//					cout<<endl;
//				}
				//cout<<"Testing"<<endl;
				for (int v=0;v<vertexx;v++){



					//	cout<<temp<<endl;
						max_size=AddLists_cp[v].size();
						if (max_size>temp)
						{
						temp=max_size;
						f_u=v;
						}


				}
//cout<<"printing here"<<endl;
                     
				if (temp==0)
				{ noedge=false;
				}
				A2VC_cp.push_back(f_u);
//cout<<"before"<<endl;
				for (int eraser=0;eraser<temp;eraser++){
                                //cout<<"eraser ="<<eraser<<endl;
				temp2=AddLists_cp[f_u].back();
                                //cout<<"temp2= "<<temp2<<endl;
                                //cout<<"f_u ="<<f_u<<endl;
				AddLists_cp[f_u].pop_back();
                                //cout<<"one"<<endl;
				AddLists_cp[temp2].remove(f_u);
                                //cout<<"two"<<endl;

			}
//cout<<"after"<<endl;

		}
		std::sort(A2VC_cp.begin(), A2VC_cp.end());
		cout<<"APPROX-VC-1: ";
		for (unsigned int vc=1; vc< A2VC_cp.size();vc++)
          {cout <<A2VC_cp[vc];
          if (vc!=A2VC_cp.size()-1)
          cout<<",";
							}
							cout<<endl;
							A2VC_cp.clear();
    clock_gettime(clock_id,&ts);
    double cpuTime1=timespec_to_double(ts);
 //   std::cout << "Time: Approx-1-VC solver:  " << cpuTime1-cpuTime0 << std::endl;
							
						}

void* printVertexCover(void *unused)
{   clockid_t clock_id;
    struct timespec ts;
	pthread_getcpuclockid(pthread_self(),&clock_id);
    clock_gettime(clock_id,&ts);
	double cpuTime0=clock_gettime(clock_id,&ts);
    // Initialize all vertices as not visited.
    int V = vertx;
    list<int>* adj = AdjList1;

    bool visited[V];
    for (int i=0; i<V; i++)
        visited[i] = false;

    list<int>::iterator i;

    // Consider all edges one by one
    for (int u=0; u<V; u++)
    {
        // An edge is only picked when both visited[u] and visited[v]
        // are false
        if (visited[u] == false)
        {
            // Go through all adjacents of u and pick the first not
            // yet visited vertex (We are basically picking an edge
            // (u, v) from remaining edges.
            for (i= adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if (visited[v] == false)
                {
                     // Add the vertices (u, v) to the result set.
                     // We make the vertex u and v visited so that
                     // all edges from/to them would be ignored
                     visited[v] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }

vector<int>A1VC;
  for (int i=0; i<V; i++)
      if (visited[i])
         A1VC.push_back(i);
    // Print the vertex cover
    std::sort(A1VC.begin(), A1VC.end());
    cout<<"APPROX-VC-2: ";
    		for (unsigned int vc=0; vc< A1VC.size();vc++)
          {cout <<A1VC[vc];
          if (vc!=A1VC.size()-1)
          cout<<",";
							}
							cout<<endl;
							A1VC.clear();
	clock_gettime(clock_id,&ts);
    double cpuTime1=timespec_to_double(ts);
   // std::cout << "Time: APPROX-VC-2 solver:  " << cpuTime1-cpuTime0 << std::endl;
 }

void* getting_input(void *unused){

string line;
        getline(cin, line);
        if (line.length()==0){
		
        exit(0);
		}
		while(!line.empty() && isspace(*line.begin()))
            line.erase(line.begin());
		if (line[0] == 'V' || line[0] == 'v') {

              //  cout<<"here"<<endl;
				vertx = 0;
				istringstream input(line);
				string subs;
				input >> subs;
				input >> vertx;
			//	cout<<"vertex = "<<vertx<<endl;
				//if(AdjList != NULL){
					//delete [] AdjList;
				//}
                                

				AdjList = new list<int>[vertx];
				AdjList1 = new list<int>[vertx];


		}
		string str;
        getline(cin, str);
		while(!str.empty() && isspace(*str.begin()))
            str.erase(str.begin());

        if (str[0] == 'E' || str[0] == 'e') {
               // cout<<"here edges"<<endl;
                                vector<int> e;
				e.clear();
                                edges =e;
				 int stop=0;

       while(stop>=0){
       int temp1= str.find("<");
       int  temp2= str.find(">");
       int var = str.find(",");

       edges.push_back(atoi(str.substr(temp1+1,var-temp1-1).c_str()));
       edges.push_back(atoi(str.substr(var+1,temp2-var-1).c_str()));


       //cout<<"Start = "<<e.start<<" End= "<<e.dest<<endl;
       //cout<<"String left = "<<str.substr(temp2+1)<<endl;
       string str1 =str.substr(temp2+1);
       stop = str1.find("<");
       if (stop>=0){
        str = str.substr(temp2+2);
        //cout<<"In if , stop = "<<stop<<endl;
       }
       else if (stop<0){
        //cout <<"In else if "<< "stop = "<<stop<<endl;
        break;
       }
       }
//cout<<"edge set made"<<endl;

				if (!edges.empty()){
					for(unsigned j =0; j< edges.size(); j=j+2){
						AdjList[edges[j]].push_back(edges[j+1]);
						AdjList[edges[j+1]].push_back(edges[j]);
						AdjList1[edges[j]].push_back(edges[j+1]);
						AdjList1[edges[j+1]].push_back(edges[j]);

					}
				}



			}


}


int main(){
while(true){
//thread th(getting_input);
//th.join();
pthread_t thread_id1;
pthread_create (&thread_id1, NULL,&getting_input,NULL);
pthread_join(thread_id1,NULL);


pthread_t thread_id2;
pthread_create (&thread_id2, NULL, &solve_minisat,NULL);
//thread th1(Approx_1,AdjList1,vertx); // Approx-1-VC
//thread th2(printVertexCover,AdjList,vertx); // Approx-2-VC
//th1.join();
//th2.join();

pthread_join (thread_id2, NULL);


pthread_t thread_id3;
pthread_create (&thread_id3, NULL, &Approx_1,NULL);

pthread_join (thread_id3, NULL);


pthread_t thread_id4;
pthread_create(&thread_id4,NULL,&printVertexCover,NULL);

pthread_join(thread_id4,NULL);
}




}
