PNC学习

## 1. 基础数学知识

线性代数：

[行列式](https://zhuanlan.zhihu.com/p/358591975)

矩阵：

[旋转矩阵](https://www.cnblogs.com/zhoug2020/p/7842808.html)

## 2. 专业知识

### 2.1 [决策规划](https://www.helloxiaobai.cn/article/bmp)

#### 2.1.1 碰撞检测

- [碰撞检测算法:AABB, SAT](https://www.helloxiaobai.cn/article/bmp/1-3)
  - [百度Apollo规划算法——OBB障碍物检测代码解析](https://blog.csdn.net/qq_38422317/article/details/131996644)
- [碰撞检测算法:GJK](https://www.helloxiaobai.cn/article/bmp/1-4)

#### 2.1.2 曲线表达形式

- [Dubins曲线](https://www.helloxiaobai.cn/article/bmp/2-5)

  左转L状态转移方程

  ![notion image](https://www.notion.so/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2Fad2ab0c3-eab8-46b6-8097-793d488a1c72%2F23383d79-7e69-4984-99a7-352f3a978530%2Fimage.png?table=block&id=82574eac-a885-4224-8500-4092c7458774&t=82574eac-a885-4224-8500-4092c7458774&width=1200&cache=v2)
  $$
  x_g=x_s+Rsin(\theta_s+\phi)-Rsin(\theta_s)\\
  y_g=y_s-Rcos(\theta_s+\phi)+Rcos(\theta_s)\\
  \theta_g=\theta_s+\phi
  $$
  推理过程如下：

  1. **确定圆心坐标** 
     根据切线方向与半径垂直的性质，半径方向为切线方向逆时针旋转 \( 90^\circ \)。若切线与 \( x \)-轴的夹角为 \( a \)，则半径方向的角度为 \( a - 90^\circ \)。 
     圆心 \( (h, k) \) 可表示为：
     $$
     \begin{cases}
     h = x - R\sin\theta_s, \\
     k = y + R\cos\theta_s.
     \end{cases}
     $$
     

  2. **绕圆心旋转** 
     点 \( (x_s, y_s) \) 绕圆心逆时针旋转 \( \phi \) 后的坐标通过旋转矩阵计算：
     $$
     \begin{cases}
     x' = h + (x - h) \cos \phi - (y - k) \sin \phi, \\
     y' = k + (x - h) \sin \phi + (y - k) \cos \phi.
     \end{cases}
     $$
     代入圆心坐标 \( h \) 和 \( k \)，并化简：
     $$
     \begin{aligned}
     x' &= x + R \left[ \sin(\theta_s + \phi) - \sin \theta_s \right], \\
     y' &= y + R \left[ \cos \theta_s - \cos(\theta_s + \phi) \right].
     \end{aligned}
     $$
  
  **最终结果**
  旋转后的坐标为：
  $$
  \boxed{
  \left( 
  x + R \left[ \sin(\theta_s + \phi) - \sin \theta_s \right], \ 
  y + R \left[ \cos \theta_s - \cos(\theta_s + \phi) \right] 
  \right)
  }
  $$

  - [Dubins曲线详细笔记](https://zhuanlan.zhihu.com/p/414753861)
  - https://github.com/AtsushiSakai/PythonRobotics/tree/master/PathPlanning/DubinsPath

## 3. 开源项目

https://github.com/ApolloAuto/apollo/blob/master/modules/common/math/box2d.cc

[Python sample codes and textbook for robotics algorithms.](https://github.com/AtsushiSakai/PythonRobotics/)



