#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>


/**
 * @brief 图的边结构
 * 
 * 在邻接表表示中，每个顶点的邻接表中存储着与其相连的边。
 * 由于这是一个无向图的实现，每条边会在两个顶点的邻接表中各存储一次。
 */
struct Edge {
    int to;      // 边的目标顶点编号
    int weight;  // 边的权重（距离/成本）
};

/**
 * @brief 用于Dijkstra算法的节点结构
 * 
 * 在优先队列中使用，用于维护当前待处理的节点集合。
 * 通过重载运算符保证优先队列能够按照距离从小到大排序。
 */
struct Node {
    int id;    // 节点编号
    int dist;  // 从源点到该节点的当前最短距离
    
    /**
     * @brief 重载大于运算符，用于优先队列的比较
     * 
     * 在使用std::greater<Node>作为比较器的优先队列中：
     * 1. 如果a > b返回true，意味着a的优先级低于b
     * 2. 优先队列会将优先级低的元素放在后面
     * 3. 因此，当dist值大的元素返回true时，它们会被放在队列后面
     * 
     * 例如，对于两个节点：
     * A(dist=2) 和 B(dist=5)
     * A > B 返回 false（因为2 > 5为false）
     * 所以A的优先级高于B，A会被放在B前面
     * 
     * @param other 要比较的另一个节点
     * @return 如果当前节点的距离大于other的距离，返回true
     */
    bool operator>(const Node& other) const {
        return dist > other.dist;  // 距离大的节点返回true，会被放在队列后面
    }
};

/**
 * @brief 图的邻接表表示
 * 
 * 使用邻接表存储图的结构，适合存储稀疏图（边数远小于顶点数的平方）。
 * 优点：
 * 1. 空间效率高，只需要存储实际存在的边
 * 2. 快速获取一个顶点的所有邻接点
 * 3. 适合进行图的遍历操作
 */
struct Graph {
    std::vector<std::vector<Edge>> adj;  // 邻接表，adj[i]存储顶点i的所有邻接边
    int n;                               // 图中顶点的数量（编号从1到n）
};

/**
 * @brief 打印图的结构
 * 
 * 按照邻接表的形式打印图，格式为：
 * 顶点编号: [邻接点1 权重1] [邻接点2 权重2] ...
 * 用于调试和验证图的构建是否正确
 * 
 * @param g 要打印的图
 */
void printGraph(Graph &g) {
    for (int i = 1; i <= g.n; i++) {
        std::cout << i << ": ";  // 打印当前顶点编号
        for (auto &e : g.adj[i]) {
            // 打印所有邻接边：目标顶点和权重
            std::cout << e.to << " " << e.weight << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 创建一个新的图
 * 
 * 初始化一个具有n个顶点的空图。
 * 注意：顶点编号从1开始到n，所以邻接表大小为n+1
 * 
 * @param n 图中顶点的数量
 * @param m 预期的边的数量（用于内存预分配，可选）
 * @return 初始化后的图
 */
Graph buildGraph(int n, int m) {
    Graph g;
    g.adj.resize(n + 1);  // 创建n+1大小的邻接表（0号位置不使用）
    g.n = n;              // 记录顶点数量
    return g;
}

/**
 * @brief 向图中添加一条无向边
 * 
 * 由于是无向图，一条边需要在两个顶点的邻接表中各添加一次。
 * 例如边(1,2)需要在顶点1的邻接表中添加2，在顶点2的邻接表中添加1。
 * 
 * @param g 要添加边的图
 * @param u 边的起点
 * @param v 边的终点
 * @param w 边的权重
 */
void addEdge(Graph &g, int u, int v, int w) {
    g.adj[u].push_back({v, w});  // 在u的邻接表中添加v
    g.adj[v].push_back({u, w});  // 在v的邻接表中添加u（无向图）
}

/**
 * @brief Dijkstra算法实现 - 计算从源点到所有其他点的最短路径
 * 
 * Dijkstra算法的核心思想：
 * 1. 维护一个距离数组dist[]，记录源点s到每个顶点的最短距离
 * 2. 使用优先队列（最小堆）维护候选节点，每次取出距离最小的节点进行扩展
 * 3. 使用pre[]数组记录最短路径的前驱节点，用于重建路径
 * 
 * 时间复杂度：O((V+E)logV)，其中V是顶点数，E是边数
 * 空间复杂度：O(V)
 * 
 * @param g 图的邻接表表示
 * @param s 源点
 * @param pre 记录最短路径的前驱节点
 * @param dist 记录源点到每个顶点的最短距离
 */
void dijkstra(Graph &g, int s, std::map<int, int> &pre, std::vector<int> &dist) {
    // vis数组标记节点是否已确定最短路径
    std::vector<int> vis(g.n + 1, 0);
    // 初始化源点距离为0
    dist[s] = 0;
    
    // 优先队列，按照距离从小到大排序
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({s, 0});  // 将源点加入队列
    
    while (!pq.empty()) {
        // 取出当前距离最小的节点
        Node cur = pq.top();
        pq.pop();
        
        // 如果该节点已访问，说明已找到最短路径，跳过
        if (vis[cur.id]) continue;
        
        // 标记当前节点已确定最短路径
        vis[cur.id] = 1;
        
        // 扫描当前节点的所有邻接边
        for (auto &e : g.adj[cur.id]) {
            // 松弛操作：如果通过当前节点cur到达节点e.to的距离更短
            if (dist[e.to] > dist[cur.id] + e.weight) {
                // 更新最短距离
                dist[e.to] = dist[cur.id] + e.weight;
                // 记录前驱节点，用于重建路径
                pre[e.to] = cur.id;
                // 将更新后的节点加入优先队列
                pq.push({e.to, dist[e.to]});
            }
        }
    }
    return;
}

/**
 * @brief 根据前驱数组重建最短路径
 * 
 * 从终点开始，通过前驱数组不断往回找，直到找到起点，
 * 然后将路径反转得到从起点到终点的最短路径
 * 
 * @param pre 前驱数组，pre[v]表示到达v的最短路径上v的前一个顶点
 * @param s 起点
 * @param e 终点
 * @return 包含最短路径上所有顶点的数组（从起点到终点的顺序）
 */
std::vector<int> getPath(std::map<int, int> pre, int s, int e) {
    std::vector<int> path;
    int cur = e;  // 从终点开始
    // 不断往回找前驱节点，直到找到起点
    while (cur != s) {
        path.push_back(cur);
        cur = pre[cur];  // 通过前驱数组往回走
    }
    path.push_back(s);  // 加入起点
    std::reverse(path.begin(), path.end());  // 反转得到从起点到终点的路径
    return path;
}

/**
 * @brief Dijkstra算法的优化版本 - 当找到目标节点时立即停止
 * 
 * 这是Dijkstra算法的一个优化版本，适用于只需要找到起点到特定终点的最短路径的情况。
 * 主要优化点：
 * 1. 一旦找到目标节点，立即停止算法
 * 2. 不需要计算到其他所有节点的最短路径
 * 3. 在终点路径确定时及时退出，节省计算资源
 * 
 * 时间复杂度：最坏情况仍为O((V+E)logV)，但平均情况会更好
 * 空间复杂度：O(V)
 * 
 * @param g 图的邻接表表示
 * @param s 起点
 * @param e 终点（目标节点）
 * @param pre 记录最短路径的前驱节点
 * @param dist 记录源点到每个顶点的最短距离
 */
void dijkstra_target(Graph &g, int s, int e, std::map<int, int> &pre, std::vector<int> &dist) {
    std::vector<int> vis(g.n + 1, 0);  // 访问标记数组
    dist[s] = 0;  // 初始化起点距离为0
    
    // 优先队列，按照距离从小到大排序
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({s, 0});  // 将起点加入队列
    
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        
        // 如果节点已访问，跳过
        if (vis[cur.id]) continue;
        
        // 标记当前节点已访问
        vis[cur.id] = 1;
        
        // 如果到达目标节点，立即停止
        // 这是该版本与标准Dijkstra算法的主要区别
        if (cur.id == e) break;
        
        // 扫描当前节点的所有邻接边
        for (auto &e : g.adj[cur.id]) {
            // 松弛操作
            if (dist[e.to] > dist[cur.id] + e.weight) {
                dist[e.to] = dist[cur.id] + e.weight;
                pre[e.to] = cur.id;  // 记录前驱节点
                pq.push({e.to, dist[e.to]});
            }
        }
    }
    return;
}

int main() {
    std::cout << "Graph: " << std::endl;
    Graph g = buildGraph(5, 7);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 4);
    addEdge(g, 2, 3, 2);
    addEdge(g, 2, 4, 6);
    addEdge(g, 3, 4, 3);
    addEdge(g, 3, 5, 5);
    addEdge(g, 4, 5, 1);
    printGraph(g);
    std::cout << "Dijkstra: " << std::endl;
    std::map<int, int> pre;
    std::vector<int> dist(g.n + 1, INT_MAX);
    dijkstra_target(g, 1, 5, pre, dist);
    for (int i = 1; i <= 5; i++) {
        std::cout << "dist[" << i << "] = " << dist[i] << std::endl;
    }
    for (auto &p : pre) {
        std::cout << "pre[" << p.first << "] = " << p.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Path: " << std::endl;
    std::vector<int> path = getPath(pre, 1, 5);
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
