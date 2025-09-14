import matplotlib.pyplot as plt
import numpy as np
import sys

def visualize_astar_results(filename):
    # 读取数据
    with open(filename, 'r') as f:
        # 读取起点
        start_x, start_y = map(int, f.readline().split())
        
        # 读取终点
        end_x, end_y = map(int, f.readline().split())
        
        # 读取路径
        path_length = int(f.readline())
        path = []
        for _ in range(path_length):
            x, y = map(int, f.readline().split())
            path.append((x, y))
        
        # 读取障碍物
        obstacle_count = int(f.readline())
        obstacles = []
        for _ in range(obstacle_count):
            x, y = map(int, f.readline().split())
            obstacles.append((x, y))
    
    # 创建图形
    plt.figure(figsize=(12, 12))
    
    # 绘制障碍物
    if obstacles:
        obs_x, obs_y = zip(*obstacles)
        plt.scatter(obs_x, obs_y, c='black', s=1, label='障碍物')
    
    # 绘制路径
    if path:
        path_x, path_y = zip(*path)
        plt.plot(path_x, path_y, 'r-', linewidth=2, label='路径')
    
    # 绘制起点和终点
    plt.scatter(start_x, start_y, c='green', s=50, marker='o', label='起点')
    plt.scatter(end_x, end_y, c='red', s=50, marker='o', label='终点')
    
    plt.title('A* 搜索算法结果可视化')
    plt.xlabel('X坐标')
    plt.ylabel('Y坐标')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.axis('equal')
    
    # 保存图像
    plt.savefig('astar_visualization.png', dpi=300, bbox_inches='tight')
    print("可视化结果已保存为 astar_visualization.png")
    
    # 显示图像
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) == 2:
        visualize_astar_results(sys.argv[1])
    else:
        visualize_astar_results('map_data.txt')
    