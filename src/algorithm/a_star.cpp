
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cmath>
// #include <fstream>
// #include <cstdlib>
// #include <ctime>
// #include <algorithm>

// using namespace std;

// // 定义节点结构
// struct Node {
//     int x, y;          // 坐标
//     int g;             // 从起点到当前节点的代价
//     int h;             // 从当前节点到终点的估计代价
//     int f;             // f = g + h
//     bool is_obstacle;  // 是否是障碍物
//     Node* parent;      // 父节点指针

//     Node(int x_, int y_) : x(x_), y(y_), g(0), h(0), f(0), 
//                           is_obstacle(false), parent(nullptr) {}
// };

// // 比较函数，用于优先队列
// struct CompareNode {
//     bool operator()(Node* a, Node* b) {
//         return a->f > b->f;  // 小的f值优先
//     }
// };

// // 计算启发式距离（曼哈顿距离）
// int calculateH(int x1, int y1, int x2, int y2) {
//     return abs(x1 - x2) + abs(y1 - y2);
// }

// // 生成随机地图
// vector<vector<Node*>> generateMap(int width, int height, float obstacleRate) {
//     vector<vector<Node*>> map(height, vector<Node*>(width));
    
//     // 初始化节点
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             map[y][x] = new Node(x, y);
//         }
//     }
    
//     // 随机生成障碍物
//     srand(time(nullptr));
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             // 边缘设置为障碍物
//             if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
//                 map[y][x]->is_obstacle = true;
//             } else {
//                 // 随机生成障碍物
//                 if ((float)rand() / RAND_MAX < obstacleRate) {
//                     map[y][x]->is_obstacle = true;
//                 }
//             }
//         }
//     }
    
//     return map;
// }

// // 获取邻居节点
// vector<Node*> getNeighbors(vector<vector<Node*>>& map, Node* node, int width, int height) {
//     vector<Node*> neighbors;
//     int x = node->x;
//     int y = node->y;
    
//     // 8个方向的邻居
//     int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
//                       {0, -1},          {0, 1},
//                       {1, -1},  {1, 0}, {1, 1}};
    
//     for (auto& dir : dirs) {
//         int nx = x + dir[0];
//         int ny = y + dir[1];
        
//         // 检查是否在地图范围内且不是障碍物
//         if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
//             !map[ny][nx]->is_obstacle) {
//             neighbors.push_back(map[ny][nx]);
//         }
//     }
    
//     return neighbors;
// }

// // A*搜索算法
// vector<Node*> aStarSearch(vector<vector<Node*>>& map, int width, int height, 
//                          Node* start, Node* end, vector<Node*>& closedList) {
//     // 开放列表（优先队列）
//     priority_queue<Node*, vector<Node*>, CompareNode> openList;
    
//     // 初始化起点
//     start->g = 0;
//     start->h = calculateH(start->x, start->y, end->x, end->y);
//     start->f = start->g + start->h;
//     openList.push(start);
    
//     // 搜索主循环
//     while (!openList.empty()) {
//         // 获取f值最小的节点
//         Node* current = openList.top();
//         openList.pop();
        
//         // 如果到达终点，回溯路径
//         if (current == end) {
//             vector<Node*> path;
//             while (current != nullptr) {
//                 path.push_back(current);
//                 current = current->parent;
//             }
//             reverse(path.begin(), path.end());
//             return path;
//         }
        
//         // 将当前节点加入关闭列表
//         closedList.push_back(current);
        
//         // 获取邻居节点
//         vector<Node*> neighbors = getNeighbors(map, current, width, height);
        
//         for (Node* neighbor : neighbors) {
//             // 如果邻居在关闭列表中，跳过
//             bool inClosed = false;
//             for (Node* n : closedList) {
//                 if (n == neighbor) {
//                     inClosed = true;
//                     break;
//                 }
//             }
//             if (inClosed) continue;
            
//             // 计算临时g值
//             int tentativeG = current->g + (abs(neighbor->x - current->x) == 1 && 
//                                            abs(neighbor->y - current->y) == 1 ? 14 : 10);
            
//             // 检查邻居是否在开放列表中
//             bool inOpen = false;
//             // 这里简化处理，实际应用中可能需要更高效的检查方式
//             vector<Node*> temp;
//             while (!openList.empty()) {
//                 Node* n = openList.top();
//                 openList.pop();
//                 if (n == neighbor) {
//                     inOpen = true;
//                     if (tentativeG < neighbor->g) {
//                         // 更新g值
//                         neighbor->g = tentativeG;
//                         neighbor->h = calculateH(neighbor->x, neighbor->y, end->x, end->y);
//                         neighbor->f = neighbor->g + neighbor->h;
//                         neighbor->parent = current;
//                     }
//                 }
//                 temp.push_back(n);
//             }
//             // 将节点放回开放列表
//             for (Node* n : temp) {
//                 openList.push(n);
//             }
            
//             // 如果不在开放列表中，添加进去
//             if (!inOpen) {
//                 neighbor->g = tentativeG;
//                 neighbor->h = calculateH(neighbor->x, neighbor->y, end->x, end->y);
//                 neighbor->f = neighbor->g + neighbor->h;
//                 neighbor->parent = current;
//                 openList.push(neighbor);
//             }
//         }
//     }
    
//     // 如果没有找到路径，返回空向量
//     return vector<Node*>();
// }

// // 输出地图到文本文件
// void outputMapToFile(vector<vector<Node*>>& map, int width, int height, 
//                     vector<Node*>& path, vector<Node*>& closedList,
//                     Node* start, Node* end, const string& filename) {
//     ofstream file(filename);
    
//     if (!file.is_open()) {
//         cerr << "无法打开文件: " << filename << endl;
//         return;
//     }
    
//     // 创建一个字符矩阵来表示地图
//     vector<vector<char>> output(height, vector<char>(width, ' '));
    
//     // 标记障碍物
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             if (map[y][x]->is_obstacle) {
//                 output[y][x] = '#';
//             }
//         }
//     }
    
//     // 标记关闭列表中的节点
//     for (Node* node : closedList) {
//         if (!map[node->y][node->x]->is_obstacle && 
//             node != start && node != end) {
//             output[node->y][node->x] = '.';
//         }
//     }
    
//     // 标记路径
//     for (Node* node : path) {
//         if (node != start && node != end) {
//             output[node->y][node->x] = '*';
//         }
//     }
    
//     // 标记起点和终点
//     output[start->y][start->x] = 'S';
//     output[end->y][end->x] = 'E';
    
//     // 写入文件
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             file << output[y][x];
//         }
//         file << endl;
//     }
    
//     file.close();
//     cout << "地图已输出到文件: " << filename << endl;
// }

// // 保存地图数据用于可视化
// void saveMapData(vector<vector<Node*>>& map, int width, int height, 
//                 vector<Node*>& path, Node* start, Node* end,
//                 const string& filename) {
//     ofstream file(filename);
    
//     if (!file.is_open()) {
//         cerr << "无法打开文件: " << filename << endl;
//         return;
//     }
    
//     // 先写入起点和终点
//     file << start->x << " " << start->y << endl;
//     file << end->x << " " << end->y << endl;
    
//     // 写入路径
//     file << path.size() << endl;
//     for (Node* node : path) {
//         file << node->x << " " << node->y << endl;
//     }
    
//     // 写入障碍物
//     int obstacleCount = 0;
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             if (map[y][x]->is_obstacle) {
//                 obstacleCount++;
//             }
//         }
//     }
//     file << obstacleCount << endl;
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             if (map[y][x]->is_obstacle) {
//                 file << x << " " << y << endl;
//             }
//         }
//     }
    
//     file.close();
//     cout << "地图数据已保存到文件: " << filename << endl;
// }

// int main() {
//     const int WIDTH = 50;
//     const int HEIGHT = 50;
//     const float OBSTACLE_RATE = 0.3f;  // 障碍物比例
    
//     // 生成地图
//     cout << "生成 " << WIDTH << "x" << HEIGHT << " 的随机地图..." << endl;
//     vector<vector<Node*>> map = generateMap(WIDTH, HEIGHT, OBSTACLE_RATE);
    
//     // 设置起点和终点（避开障碍物）
//     Node* start = map[10][10];
//     Node* end = map[HEIGHT-10][WIDTH-10];
    
//     // 确保起点和终点不是障碍物
//     start->is_obstacle = false;
//     end->is_obstacle = false;
    
//     cout << "开始A*搜索..." << endl;
//     vector<Node*> closedList;
//     vector<Node*> path = aStarSearch(map, WIDTH, HEIGHT, start, end, closedList);
    
//     if (path.empty()) {
//         cout << "未找到从起点到终点的路径!" << endl;
//     } else {
//         cout << "找到路径，长度为: " << path.size() << endl;
//     }
    
//     // 输出文本地图
//     outputMapToFile(map, WIDTH, HEIGHT, path, closedList, start, end, "astar_result.txt");
    
//     // 保存用于可视化的数据
//     saveMapData(map, WIDTH, HEIGHT, path, start, end, "map_data.txt");
    
//     // 释放内存
//     for (int y = 0; y < HEIGHT; y++) {
//         for (int x = 0; x < WIDTH; x++) {
//             delete map[y][x];
//         }
//     }
    
//     return 0;
// }


#include "a_star.h"
#include <algorithm>

namespace algorithm {

AStar::AStar(int rows, int cols, float obstacle_ratio, bool need_generate_grid)
  : rows_(rows), cols_(cols), obstacle_ratio_(obstacle_ratio), need_generate_grid_(need_generate_grid)
    , search_finished_(false) {
  generateGrid();
}

// 曼哈顿距离
int AStar::calculateHeuristic(const Node& node) {
  return abs(node.x - end_->x) + abs(node.y - end_->y);
}

void AStar::setStart(int x, int y) {
  start_ = &grid_[y][x];
  start_->is_obstacle = false;
}

void AStar::setEnd(int x, int y) {
  end_ = &grid_[y][x];
  end_->is_obstacle = false;
}

void AStar::setGrid(const std::vector<std::vector<Node>>& grid) {
  this->grid_ = grid;
  map_generated_ = true;
}

void AStar::search() {
  if (!map_generated_) {
    std::cerr << "Map is not generated" << std::endl;
    return;
  }
  if (start_ == nullptr || end_ == nullptr) {
    std::cerr << "Start or end is not set" << std::endl;
    return;
  }
  search_finished_ = false;
  start_->g = 0;
  start_->h = calculateHeuristic(*start_);
  start_->f = start_->g + start_->h;
  open_list_.push(start_);

  while (!open_list_.empty()) {
    Node* current = open_list_.top();
    open_list_.pop();
    if (current == end_) {
      search_finished_ = true;
      break;
    }
    closed_list_.insert(current);
    current->is_in_closed_list = true;
    auto neighbors = getNeighbors(*current);
    for (auto neighbor : neighbors) {
      if (closed_list_.find(neighbor) != closed_list_.end()) {
        continue;
      }
      int tentative_g = current->g + 1;
      if (!neighbor->is_in_open_list || tentative_g < neighbor->g) {
        neighbor->g = tentative_g;
        neighbor->h = calculateHeuristic(*neighbor);
        neighbor->f = neighbor->g + neighbor->h;
        neighbor->parent = current;
        if (!neighbor->is_in_open_list) {
          open_list_.push(neighbor);
          neighbor->is_in_open_list = true;
        }
      }
    }
  }
  search_finished_ = true;
}

std::vector<Node*> AStar::getPath() {
  if (!search_finished_) {
    std::cerr << "Search is not finished" << std::endl;
    return {};
  }
  std::vector<Node*> path;
  Node* current = end_;
  while (current != nullptr) {
    path.push_back(current);
    current = current->parent;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

void AStar::saveMap(const std::string& file_path) {
  std::ofstream file(file_path);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << file_path << std::endl;
    return;
  }

  // 先写入起点与终点
  file << start_->x << " " << start_->y << std::endl;
  file << end_->x << " " << end_->y << std::endl;

  // 写入路径
  auto path = getPath();
  file << path.size() << std::endl;
  for (auto node : path) {
    file << node->x << " " << node->y << std::endl;
  }

  // 写入障碍物
  int obstacle_count = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (grid_[i][j].is_obstacle) {
        obstacle_count++;
      }
    }
  }
  file << obstacle_count << std::endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (grid_[i][j].is_obstacle) {
        file << j << " " << i << std::endl;
      }
    }
  }
  file.close();
  std::cout << "Map saved to " << file_path << std::endl;
}



void AStar::generateGrid() {
  grid_.resize(rows_, std::vector<Node>(cols_));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      grid_[i][j].x = j;
      grid_[i][j].y = i;
      grid_[i][j].g = 0;
      grid_[i][j].h = 0;
      grid_[i][j].f = 0;
      grid_[i][j].is_obstacle = false;
      grid_[i][j].is_in_closed_list = false;
      grid_[i][j].is_in_open_list = false;
      grid_[i][j].parent = nullptr;
    }
  }

  // 随机生成障碍物
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // 边缘设置为障碍物
      if (i == 0 || j == 0 || i == rows_ - 1 || j == cols_ - 1) {
        grid_[i][j].is_obstacle = true;
        continue;
      }
      // 随机生成障碍物
      if (rand() % 100 < obstacle_ratio_ * 100) {
        grid_[i][j].is_obstacle = true;
      }
    }
  }
  map_generated_ = true;
}

std::vector<Node*> AStar::getNeighbors(const Node& node) {
  if (grid_.empty()) {
    return {};
  }
  std::vector<Node*> neighbors;

  static int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                           {0, -1}, {0, 1},
                           {1, -1}, {1, 0}, {1, 1}};
  for (auto& dir : dirs) {
    int nx = node.x + dir[0];
    int ny = node.y + dir[1];
    if (nx >= 0 && nx < cols_ && ny >= 0 && ny < rows_ && !grid_[ny][nx].is_obstacle) {
      neighbors.push_back(&grid_[ny][nx]);
    }
  }
  return neighbors;
}

}  // namespace algorithm

int main() {
  algorithm::AStar astar(50, 50, 0.3, true);
  astar.setStart(10, 10);
  astar.setEnd(40, 40);
  astar.search();
  astar.saveMap("map_data.txt");
  return 0;
}