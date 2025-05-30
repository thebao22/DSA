#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <cctype>
#include<stack>
#include <queue>
using namespace std;
//----Khai bao ham----
vector<vector<int>> convertMatrixToList(const string& filename);
vector<vector<int>> convertListToMatrix(const string& filename);
bool isDirected(const vector<vector<int>>& adjMatrix);
int countVertices(const vector<vector<int>>& adjMatrix);
int countEdges(const vector<vector<int>>& adjMatrix);
bool isCompleteGraph(const vector<vector<int>>& adjMatrix);
bool isBipartite(const vector<vector<int>>& adjMatrix);
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);
vector<vector<int>> convertToUndirected(const vector<vector<int>>& adjMatrix);
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix);
vector<int> findEulercycle(const vector<vector<int>>& adjMatrix);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);
vector<int> Dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> BellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);
//----Dinh nghia ham----
vector<vector<int>> convertMatrixToList(const string& filename) {
    vector<vector<int>> matrix;
    int n;
    int j = 0;
    string line;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return matrix; // Return empty matrix if file cannot be opened
    }
    getline(file, line);
    n = stoi(line);
    matrix.resize(n);
    while(getline(file, line)) {
        if(line.empty()) continue;
        //deleteSpaces(line);
        int count = 0;
        for(int i = 0; i < line.size(); i++) {
           char c = line[i];
            if (isdigit(c)) {
                if(c == '0') count++;
                if(c == '1') {
                    if(count > 0) {
                        matrix[j].push_back(count);
                        count++;
                    }
                    if (count == 0) {
                        matrix[j].push_back(0);
                        count++;
                    }
                }
            } else if (!isspace(c) || (isspace(c) && i == 0)) {
                continue;
            }
        }
        count = 0;
        j++;
    }
    return matrix;
}
vector<vector<int>> convertListToMatrix(const string& filename) {
    vector<vector<int>> matrix;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return matrix; // Return empty matrix if file cannot be opened
    }
    string line;
    int j = 0;
    int n;
    getline(file, line);;
    n = stoi(line);
    if(n <= 0) {
        cerr << "Invalid matrix size: " << n << endl;
        return matrix; // Return empty matrix if size is invalid
    }
    matrix.resize(n, vector<int>(n, 0));
    while(getline(file, line)) {
        if(line.empty()) continue;
        int nums = 0;
        line += ' ';
        vector<int> index;
        int k = 0;
        for(int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (isdigit(c)) 
            {
                nums = nums * 10 + (c - '0');
            }
            else if (!isspace(c) || (isspace(c) && i == 0)) {
                continue; // bỏ qua ký tự lạ
            }
            else {
                if(k == 0){
                    k = 1;
                    nums = 0;
                } 
                else {
                    index.push_back(nums);
                }
                nums = 0; 
            }
               
        } 
        for (int i = 0; i < index.size(); i++) {
            if (index[i] < 0 || index[i] >= n) {
                continue;
            }
            matrix[j][index[i]] = 1;
        }
        j++;
        if (j >= n) {
            break; // Prevent overflow if more rows than specified
        }
    }
    return matrix;
}
bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(adjMatrix[i][j] == 1 && adjMatrix[j][i] == 1){
                return false;
            }
        }
    }
    return true;
}
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}
int coutEdges(const vector<vector<int>>& adjMatrix){
    int count = 0;
    int n = adjMatrix.size();
    int m = adjMatrix[0].size();
    for(int i = 0; i< n; i++){
        for(int j = 0; j<m; j++){
            if(adjMatrix[i][j] == 1){
                count += 1;
            }
        }
    }
    if(isDirected(adjMatrix)){
        return count;
    }
    else return count / 2;
}
bool isCOmpleteGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int m = adjMatrix[0].size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if( i ==j && adjMatrix[i][j] == 0){
                return false;
            }
            if(adjMatrix[i][j] == 0 && i != j){
                return false;
            }
        }
    }
    return true;
}
bool isBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int m = adjMatrix[0].size();
    if(isDirected(adjMatrix)){
        return false;
    }
    queue<int> q;
    vector<int> color(n, -1);
    for(int i = 0; i < n; i++){
        if(color[i] == -1){
            color[i] = 0;
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v = 0; v < n; v++){
                    if(adjMatrix[u][v]){
                        if(color[v] == -1){
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if(color[v] == color[u]){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int m = adjMatrix[0].size();
    if(isDirected(adjMatrix)){
        return false;
    }
    queue<int> q;
    vector<int> color(n, -1);
    for(int i = 0; i < n; i++){
        if(color[i] == -1){
            color[i] = 0;
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v = 0; v < n; v++){
                    if(adjMatrix[u][v]){
                        if(color[v] == -1){
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if(color[v] == color[u]){
                            return false;
                        }
                    }
                }
            }
        }
    }
    vector<int> part1 ,part2;
    for(int i = 0; i < color.size(); i++){
       if(color[i] == 0){
            part1.push_back(i);
        } else {
            part2.push_back(i);
        }
    }
    for(int i = 0; i < part1.size(); i++){
        for(int j = 0; j < part2.size(); j++){
            if(adjMatrix[part1[i]][part2[j]] != 1){
                return false;
            }
        }
    }
    for(int i = 0; i < part1.size(); i++){
        for(int j = 0; j < part2.size(); j++){
            if(adjMatrix[part1[i]][part1[j]] == 1){
                return false;
            }
            if(adjMatrix[part2[i]][part2[j]] == 1){
                return false;
            }
        }
    }
    return true;
}
vector<vector<int>> convertToUndirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0;j < n; j++){
           if(adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1){
                result[i][j] = 1;
                result[j][i] = 1;
            }
        }
    }
    return result;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    if(isDirected(adjMatrix)){
        return result; // Return empty matrix if the graph is directed
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(i != j && adjMatrix[i][j] == 0){
                result[i][j] = 1;
                result[j][i] = 1;
            }
        }
    }
    return result;
}
vector<int> findEulercycle(const vector<vector<int>>& adjMatrix) {
    vector<int> eulerCycle;
    vector<vector<int>> adjMatrixCopy = adjMatrix;
    stack<int> s;
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++){
        int degree = 0;
        for(int j = 0; j<n; j++){
            if(adjMatrixCopy[i][j] == 1){
                degree++;
            }
        }
        if(degree > 0){
            s.push(i);
            break;
        }
    }
    while(!s.empty()){
        int u = s.top();
        bool check = false;
        for(int v = 0; v<n; v++){
            if(adjMatrixCopy[u][v] == 1){
                check = true;
            }
        }
        if(!check){
            eulerCycle.push_back(u);
            s.pop();
        } else {
            for(int v = 0; v<n; v++){
                if(adjMatrix[u][v] == 1){
                    adjMatrixCopy[u][v] = 0;
                    adjMatrixCopy[v][u] = 0;
                    s.push(v);
                    break;
                }
            }
        }
    }
    return eulerCycle; // Return empty vector if not implemented
}
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> result;
    result.resize(n);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    while(!s.empty()){
        int u = s.top();
        s.pop();
        for(int v = 0; v < n; v++){
            if(visited[v] == false && adjMatrix[u][v] == 1){
                visited[v] = true;
                result[u].push_back(v);
                result[v].push_back(u);
                s.push(v);
                break;
            }
        }
    }
    return result;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> result;
    result.resize(n);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v = 0; v < n; v++){
            if(visited[v] == false && adjMatrix[u][v] == 1){
                visited[v] = true;
                result[u].push_back(v);
                result[v].push_back(u);
                q.push(v);
            }
        }
    }
    return result;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    if(u < 0 || u >= n || v < 0 || v >= n) {
        return false;
    }
    return adjMatrix[u][v] == 1 || adjMatrix[v][u] == 1;
}
vector<int> Dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> Weight(n, INT_MAX);
    vector<int> shortestWay(n, -1);
    vector<bool> visited(n, false);
    Weight[start] = 0;
    pq.push({0, start});
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(int v = 0; v < n; v++){
            if(adjMatrix[u][v] == 1 && !visited[v]){
                int weight = adjMatrix[u][v]; // Assuming all edges have weight 1
                if(Weight[u] + weight < Weight[v]){
                    Weight[v] = Weight[u] + weight;
                    shortestWay[v] = u;
                    pq.push({Weight[v], v});
                }
            }
        }
    }    
    vector<int> result;
    if(Weight[end] == INT_MAX) {
        return result;
    }
    for(int v = end; v != -1; v = shortestWay[v]) {
        result.push_back(v);
    }
    reverse(result.begin(), result.end());
    return result;
}
vector<int> BellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> Weight(n ,INT_MAX);
    vector<int> shortestWay(n, -1);
    Weight[start] = 0;
    for(int i = 0; i < n - 1; i++){
        for(int u = 0; u < n; u++){
            for(int v = 0; v < n; v++){
                if(adjMatrix[u][v] != 0 && Weight[u] != INT_MAX && Weight[u] + adjMatrix[u][v] < Weight[v]){
                    Weight[v] = Weight[u] + adjMatrix[u][v];
                    shortestWay[v] = u;
                }
            }
        }
    }
    vector<int> result;
    if(Weight[end] == INT_MAX) {
        return result;
    }
    for(int v = end; v != -1; v = shortestWay[v]) {
        result.push_back(v);
    }
    reverse(result.begin(), result.end());
    return result;
}
