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

##### 2.1.2.1 [Dubins曲线](https://www.helloxiaobai.cn/article/bmp/2-5)

1.  状态转移方程

    1. 左转L状态转移方程

    <p align="center">
      <img src="https://www.notion.so/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2Fad2ab0c3-eab8-46b6-8097-793d488a1c72%2F23383d79-7e69-4984-99a7-352f3a978530%2Fimage.png?table=block&id=82574eac-a885-4224-8500-4092c7458774&t=82574eac-a885-4224-8500-4092c7458774&width=200&cache=v2" alt="notion image">
    </p>

    $$
    \begin{aligned}
    x_g &= x_s+Rsin(\theta_s+\phi)-Rsin(\theta_s)\\
    y_g &= y_s-Rcos(\theta_s+\phi)+Rcos(\theta_s)\\
    \theta_g &= \theta_s+\phi
    \end{aligned}
    $$
    推理过程如下：

    **确定圆心坐标** 
      根据切线方向与半径垂直的性质，半径方向为切线方向逆时针旋转 \( 90^\circ \)。若切线与 \( x \)-轴的夹角为 \( \theta_s \)，则半径方向的角度为 \( \theta_s - 90^\circ \)。
      圆心 \( (h, k) \) 可表示为：
      $$
      \begin{cases}
      x = h + R\cos(\theta_s-90^\circ)=h+R\sin(\theta_s), \\  
      y = k + R\sin(\theta_s-90^\circ)=k-R\cos(\theta_s).
      \end{cases}
      =>
      \begin{cases}
      h = x_s - R\sin\theta_s, \\  
      k = y_s + R\cos\theta_s.
      \end{cases}
      $$
      

    **绕圆心旋转** 
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

    2. 右转R状态转移方程
    <p align="center">
      <img src="Appendix/image/Dubins_R_Turn.png" alt="Dubins_R_Turn.png" width="300">
    </p>

    $$
    \begin{aligned}
    x_g &= x_s-Rsin(\theta_s-\phi)+Rsin(\theta_s)\\
    y_g &= y_s+Rcos(\theta_s-\phi)-Rcos(\theta_s)\\
    \theta_g &= \theta_s-\phi
    \end{aligned}
    $$
    推理过程如下:
    **确定圆心坐标**  
    已知点 \((x_s, y_s)\) 在圆上，且顺时针方向的切线与 \(x\)-轴的夹角为 \(\theta_s\)。由于切线方向与半径垂直，半径方向为逆时针旋转 \(90^\circ\)（即角度 \(\theta_s + 90^\circ\)）。圆心坐标为：
      $$
      \begin{cases}
      x = h + R\cos(\theta_s+90^\circ)=h-R\sin(\theta_s), \\  
      y = k + R\sin(\theta_s+90^\circ)=k+R\cos(\theta_s).
      \end{cases}
      =>
    \begin{cases}
    h = x + R \sin \theta_s, \\
    k = y - R \cos \theta_s.
    \end{cases}
      $$

    **绕圆心顺时针旋转**  
    点 \((x_s, y_s)\) 绕圆心顺时针旋转 \(\phi\) 角度后的坐标公式为：
    $$
    \begin{cases}
    x' = h + (x - h) \cos(-\phi) - (y - k) \sin(-\phi), \\
    y' = k + (x - h) \sin(-\phi) + (y - k) \cos(-\phi).
    \end{cases}
    $$
    代入圆心坐标 \(h = x + R \sin \theta_s\) 和 \(k = y - R \cos \theta_s\)，并化简：
    $$
    \begin{aligned}
    x' &= x + R \sin\theta_s + \left( -R \sin \theta_s \cos \phi + R \cos \theta_s \sin \phi\right), \\
    y' &= y - R \cos \theta_s + \left( R \sin \theta_s \sin \phi + R \cos \theta_s \cos \phi \right).
    \end{aligned}
    $$

    **应用三角恒等式**  
    利用三角恒等式 \(\sin(\phi - \theta_s) = \sin \phi \cos \theta_s - \cos \phi \sin \theta_s\) 和 \(\cos(\phi - \theta_s) = \cos \phi \cos \theta_s + \sin \phi \sin \theta_s\)，得到：
    $$
    \begin{aligned}
    x' &= x + R \left[ \sin(\phi - \theta_s) + \sin \theta_s \right], \\
    y' &= y + R \left[ \cos(\phi - \theta_s) - \cos \theta_s \right].
    \end{aligned}
    $$

    **最终结果**
    点 \((x_s, y_s)\) 顺时针旋转 \(\phi\) 角度后的坐标为：
    $$
    \boxed{
    \left( 
    x + R \left[ \sin(\phi - \theta_s) + \sin \theta_s \right], \ 
    y + R \left[ \cos(\phi - \theta_s) - \cos \theta_s \right]
    \right)
    }
    $$

    3. 直行转移方程
    <p align="center">
      <img src="Appendix/image/Dubins_Straight.png" alt="Dubins_Straight" width="300">
    </p>

    $$
    \begin{aligned}
    x_g & =x_s + p\cos(\theta_s)\\
    y_g &= y_s+p\sin(\theta_s)\\
    \theta_g &= \theta_s
    \end{aligned}
    $$

2. 路径求解

    这里我们以LSL为例：

    **step1: L** 设第一步L的结束状态为\((x_1, y_1, \theta_1)\),L转过对的角度是\(\phi_1\) .代入初始状态得:

    $$
    x_1=x_s+R\sin(\theta_s+\phi_1)-R\sin(\theta_s)\\
    y_1=y_s-R\cos(\theta_s+\phi_1)+R\cos(\theta_s)\\
    \theta_1=\theta_s+\phi_1
    $$

    **step2: S** 设第2步S的结束状态是\((x_2, y_2, \theta_2)\)，代入\((x_1, y_1, \theta_1)\)得：

    $$
    \begin{aligned}
    x_2 &= x_1 + p\cos(\theta_1) \\
      &= x_s + R\sin(\theta_s+\phi_1) - R\sin(\theta_s) + p\cos(\theta_s + \phi_1) \\
    y_2 &= y_1 + p\sin(\theta_1) \\
      &= y_s - R\cos(\theta_s+\phi_1) + R\cos(\theta_s) + p\sin(\theta_s + \phi_1) \\
    \theta_2 &= \theta_1 = \theta_s + \phi_1
    \end{aligned}
    $$

    **step3: L** 第三步L的结束状态就是终点状态\((x_g, y_g, \theta_g)\),代入\((x_2, y_2, \theta_2)\)得：
    
    $$
    \begin{aligned}
    x_g &= x_2 + R\sin(\theta_2 + \phi_2) - R\sin(\theta_2) \\
    &= x_s - R\sin(\theta_s) + p\cos(\theta_s + \phi_1) + R\sin(\theta_s + \phi_1 + \phi_2) \\
    y_g &= y_2 - R\cos(\theta_2 + \phi_2) + R\cos(\theta_2) \\
    &= y_s + R\cos(\theta_s) + p\sin(\theta_s + \phi_1) - R\cos(\theta_s + \phi_1 + \phi_2) \\
    \theta_g &= \theta_2 + \phi_2 = \theta_s + \phi_1 + \phi_2
    \end{aligned}
    $$

    **step4:** 联立求解，可以计算出转过的角度\(\phi_1, \phi_2\),直线长度\(p\),总长度\(L\)

    $$
    \begin{aligned}
    \phi_1 &= -\theta_s + \arctan(\frac{y_g - y_s + R\cos(\theta_g) - R\cos(\theta_s)}{x_g - x_s + R\sin(\theta_s) - R\sin(\theta_g)}) \{mod2\pi\} \\
    \phi_2 &= \theta_g - \arctan(\frac{y_g - y_s + R\cos(\theta_g) - R\cos(\theta_s)}{x_g - x_s + R\sin(\theta_s) - R\sin(\theta_g)}) \{mod2\pi\}\\
    p & = \sqrt{((x_g - x_s + R\sin(\theta_s) - R\sin(\theta_g))^2 + (y_g - y_s - R\cos(\theta_s) + R\cos(\theta_g))^2)} \\
    L &= (\theta_g - \theta_s)R + p
    \end{aligned}
    $$

    其中{mod2\(\pi\)}是指将角度归一化到[0,\(2\pi\)]的区间内，其他组合方式可以参考上述内容自行推导。

3. 简化求解过程
    为方便计算，在计算前先进行了坐标变换。还是以LSL为例，设起点s\((x_i，y_i，\alpha_i\))， 终点为g\((x_g,y_g,\beta_g\)) ，先将起点平移支原点，并放置\(\theta\)角，则终点也落在 x 轴上，变换后起点和终点的坐标为 s\((0,0,\alpha\))和g\((d,0,\beta\)),变换后的坐标系如图所示：

    <p align="center">
      <img src="Appendix/image/normalization_coordinate.png" alt="coordinate" width="500">
    </p>

    $$
    \begin{aligned}
    \theta &= atan2(\frac{y_g - y_i}{x_g - x_i})  \\
    D &= \sqrt{(x_i - x_g)^2 + (y_i - y_g)^2} \\
    d &= \frac{D}{R}  \\
    \alpha &= mod(\alpha_i - \theta, 2\pi)  \\
    \beta &= mod(\beta_g - \theta, 2\pi)
    \end{aligned}
    $$

    这里将最小转弯半径正则化为1，这样每个最小转弯半径都为1，由角度计算弧长时更方便，弧长即等于角度（弧度制）
    
    将上述变量代入路径求解**step3**中，得到如下方程组

    $$
    p\cos(\alpha + t) - \sin\alpha + \sin\beta = d  \\
    p\sin(\alpha + t) + \cos\alpha - \cos\beta = 0  \\
    \alpha + t + q = \beta \{mod2\pi\}
    $$
    联立求解可得：

    $$
    \begin{aligned}
    t_{lsl} &= -\alpha + arctan(\frac{\cos\beta - \cos\alpha}{ d + \sin\alpha - \sin\beta}) \{mod 2\pi\} \\
    p_{lsl} &= \sqrt{2 + d^2 - 2\cos(\alpha - \beta) + 2d\sin(\alpha - \beta)} \\
    q_{lsl} &= \beta - arctan(\frac{\cos\beta - \cos\alpha}{ d + \sin\alpha - \sin\beta}) \{mod 2\pi\} \\
    L_{lsl} &= t_{lsl} + p_{lsl} + q_{lsl}
    \end{aligned}
    $$
    其他求解过程类似，可自行推导，六种情况的求解方程如下：
    <p align="center">
      <img src="Appendix/image/Dubins_solves.png" alt="Dubins_solves" width="500">
    </p>
  - [Dubins曲线学习笔记及相关思考](https://blog.csdn.net/qq_44339029/article/details/126095951)
  - [Dubins曲线详细笔记](https://zhuanlan.zhihu.com/p/414753861)
  - [【自动驾驶】路径规划—— Dubins 曲线推导(基于向量的方法)](https://blog.csdn.net/weixin_42301220/article/details/125328823?spm=1001.2014.3001.5501)
  - [【自动驾驶轨迹规划之dubins曲线与reeds-shepp曲线】_csdn](https://blog.csdn.net/weixin_65089713/article/details/124039241?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7EPaidSort-1-124039241-blog-125328823.235%5Ev43%5Epc_blog_bottom_relevance_base6&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7EPaidSort-1-124039241-blog-125328823.235%5Ev43%5Epc_blog_bottom_relevance_base6&utm_relevant_index=1)
  - [【自动驾驶轨迹规划之dubins曲线与reeds-shepp曲线】_local](./Appendix/html/【自动驾驶轨迹规划之dubins曲线与reeds-shepp曲线.html)
  - [【全局路径规划模块曲线算法】Dubins与Reeds-Shepp曲线拟合（附C++代码）_csdn](https://blog.csdn.net/qq_35635374/article/details/131612386?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7EPaidSort-1-131612386-blog-124039241.235%5Ev43%5Epc_blog_bottom_relevance_base6&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7EPaidSort-1-131612386-blog-124039241.235%5Ev43%5Epc_blog_bottom_relevance_base6&utm_relevant_index=2)
  - [【全局路径规划模块曲线算法】Dubins与Reeds-Shepp曲线拟合（附C++代码）_local](./Appendix/html/【全局路径规划模块曲线算法】Dubins与Reeds-Shepp曲线拟合（附C++代码）.html)
  - [【运动规划算法项目实战】如何实现Dubins曲线和Reeds-Shepp曲线（附ROS C++代码）_csdn](https://blog.csdn.net/Travis_X/article/details/130579771?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7EPaidSort-1-130579771-blog-124039241.235%5Ev43%5Epc_blog_bottom_relevance_base6&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7EPaidSort-1-130579771-blog-124039241.235%5Ev43%5Epc_blog_bottom_relevance_base6&utm_relevant_index=1)
  - [【运动规划算法项目实战】如何实现Dubins曲线和Reeds-Shepp曲线（附ROS C++代码）_local](./Appendix/html/【运动规划算法项目实战】如何实现Dubins曲线和Reeds-Shepp曲线（附ROS%20C++代码）.html)
  - https://github.com/AtsushiSakai/PythonRobotics/tree/master/PathPlanning/DubinsPath

## 3. 开源项目

https://github.com/ApolloAuto/apollo/blob/master/modules/common/math/box2d.cc

[Python sample codes and textbook for robotics algorithms.](https://github.com/AtsushiSakai/PythonRobotics/)



