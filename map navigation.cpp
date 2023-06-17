#include <bits/stdc++.h>
using namespace std;
//the function shortest path returns a vector that contains the locations through which the shortest path from the source to destination exists.
vector<int> shortestpath(int no_of_locations,int no_of_connections,vector<vector<int>> &edges,int source_location,int destination)
{
    vector<string> paths[no_of_locations+1];
    //adj is the adjacency list used to perform dijsktra's algorithm.
    vector<pair<int,int>> adj[no_of_locations+1];
    //we store the possible locations that can be reached directly from a location along with the respective  weight.
    for(auto it:edges)
    {
        adj[it[0]].push_back({it[1],it[2]});
        adj[it[1]].push_back({it[0],it[2]});
    }
    priority_queue <pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(no_of_locations+1);
    vector<int> parent(no_of_locations+1);
    for(int i=0;i<no_of_locations+1;i++)
    {
        dist[i]=1e9;
        parent[i]=i;
    }
    dist[source_location]=0;
    pq.push({0,source_location});
    while(!pq.empty())
    {
        int dis=pq.top().first;
        int node=pq.top().second;
        pq.pop();
        for(auto it:adj[node])
        {
            int edgewieght=it.second;
            int adjnode=it.first;
            if(dis+edgewieght<dist[adjnode])
            {
                dist[adjnode]=dis+edgewieght;
                pq.push({dist[adjnode],adjnode});
                parent[adjnode]=node;
            }
        }
    }
    vector<int> path;
    int newnode=destination;
    while(parent[newnode]!=newnode)
    {
        path.push_back(newnode);
        newnode=parent[newnode];

    }
    path.push_back(source_location);
    reverse(path.begin(),path.end());
    path.push_back(dist[destination]);
    return path;
}

int main()
{
    //taking total no. of locations and total no. of paths available in the campus of IIT Ropar.
    int no_of_locations=26,no_of_connections=58;
    //source stores the location in the campus we want to start our journey from.
    string source="";
    cout<<"enter the source"<<endl;
    //taking the input of source.
    getline(cin,source);
    //the vector locations stores all the locations present in IIT Ropar.
    vector<string> locations{"","m visveswaraya block","satish dhawan block","ssb block",
    "sutlej hostel", "beas hostel", "chenab hostel", "jc bose blocak",
    "s ramanujan block","brahmaputra hostel","sports complex", "annapurna mess",
    "tennis court", "badminton court" , "dubey canteen", "volleyball court",
    "basketball court" , "maggi point" , "coffee day" , "raavi hostel","utility block",
     "medical center", "lecture hall complex" ,"workshop" ,"library block", "super academic block", "spiral"};
    //initializing the variable source_location with -1, which will later store the index of our source in the location vector defined by us.
    int source_location=-1;
    for(int i=0;i<27;i++)
    {
        if(source==locations[i])
        {
            source_location=i;
            break;
        }
    }
    //if we did not find the location in our pre-defined vector, we return "invalid location."
    if(source_location==-1)
    {
        cout<<"invalid location";
        return 0;
    }
    //the string dest stores the name of our destination.
    string dest;
    //similar to source_location, destination stores the index of the destination in the pre-defined vector.
    int destination=-1;
    cout<<"enter the destination"<<endl;
    getline(cin,dest);
    for(int i=0;i<27;i++)
    {
        if(dest==locations[i])
        {
            destination=i;
            break;
        }
    }
    //if we did not find the location in our pre-defined vector, we return "invalid location."
    if(destination==-1)
    {
        cout<<"invalid location";
        return 0;
    }
    //the vector edges stores the triplets which are actually paths and the weights associated with these paths.
    //the first and second elements are the source and destination of the respective path and the third element is the weight associated with that path
    //the weight is nothing but the total time in minutes taken on average to walk that path.
    vector<vector<int>> edges= {{6, 5, 1}, {5, 9, 3}, {9, 10, 10}, {5, 11, 3},
    {11, 9, 1}, {5, 14, 2}, {5, 4, 1}, {4, 12, 2}, {4, 13, 2}, {12, 13, 1}, {12, 14, 1},
    {13, 14, 1}, {4, 14, 2}, {14, 11, 2}, {14, 15, 1}, {14, 16, 1}, {15, 16, 1},
    {15, 11, 2}, {16, 11, 2}, {4, 3, 3}, {4, 17, 2}, {17, 15, 1}, {17, 16, 1},
    {17, 18, 1}, {18, 16, 1}, {18, 15, 1}, {18, 19, 1}, {19, 15, 1}, {19, 16, 1},
    {19, 11, 3}, {4,3,3},{4,17,2},{17,20,1},{17,21,2},{18,20,1},
    {18,21,2},{17,20,2},{17,21,1},{20,21,1},{3,20,3},{3,21,3},
    {3,2,3},{20,22,3},{21,22,3},{20,13,2},{21,13,2},{19,13,2},
    {2,22,2},{22,23,2},{2,1,4},{22,24,2},{1,24,2},
    {26,1,2},{1,24,2},{24,25,2},{1,25,2},{1,7,4},{7,8,3}};

    vector<int> path= shortestpath(no_of_locations,no_of_connections,edges,source_location,destination);
    cout<<"The shortest path from ";
    cout<<locations[source_location];
    cout<<" to ";
    cout<<locations[destination]<<endl;
    int i=0;
    for(int i=0;i<path.size()-2;i++)
    {
        cout<<locations[path[i]]+"->";
    }
    cout<<locations[path[path.size()-2]]<<endl;
    cout<<"The minimum time taken to cover the travel is"<<endl;
    cout<<path[path.size()-1]<<" minutes"<<endl;
    return 0;
}
