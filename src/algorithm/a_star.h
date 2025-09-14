
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace algorithm {

struct Node {
  int x{0};
  int y{0};
  int g{0};
  int h{0};
  int f{0};
  bool is_obstacle{false};
  bool is_in_closed_list{false};
  bool is_in_open_list{false};
  Node* parent{nullptr};

  Node() = default;

  Node(int x, int y) : x(x), y(y), g(0), h(0), f(0),
                       is_obstacle(false), is_in_closed_list(false),
                       is_in_open_list(false), parent(nullptr) {}
};

// 比较函数用于优先队列
struct CompareNode {
  bool operator()(const Node* a, const Node* b) const {
    return a->f > b->f;
  }
};

struct NodeHash {
  size_t operator()(const Node* node) const {
    return std::hash<int>()(node->x) ^ std::hash<int>()(node->y);
  }
};

struct NodeEqual {
  bool operator()(const Node* a, const Node* b) const {
    return a->x == b->x && a->y == b->y;
  }
};

class AStar {
 public:
  AStar() = default;
  explicit AStar(int rows, int cols, float obstacle_ratio, bool need_generate_grid = true);
  ~AStar() = default;
  int calculateHeuristic(const Node& node);
  void setStart(int x, int y);
  void setEnd(int x, int y);
  void setGrid(const std::vector<std::vector<Node>>& grid);
  void search();
  std::vector<Node*> getPath();


  void saveMap(const std::string& file_path);

 private:
  void generateGrid();
  std::vector<Node*> getNeighbors(const Node& node);
 private:
  int rows_{};
  int cols_{};
  float obstacle_ratio_{};
  bool need_generate_grid_{};
  bool search_finished_{false};
  bool map_generated_{false};
  std::vector<std::vector<Node>> grid_;
  Node* start_;
  Node* end_;
  std::vector<Node*> open_list_heap_;
  std::priority_queue<Node*, std::vector<Node*>, CompareNode> open_list_;
  std::unordered_set<Node*, NodeHash, NodeEqual> closed_list_;
};



}  // namespace algorithm