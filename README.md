用法：
  1. 新建工作空间：
  ```
    mkdir -p ~/catkin_ws/src
    cd ~/catkin_ws/
    catkin_make
    source devel/setup.bash
  ```
  
  2. 把`catkin_ws` 中的 `src` 拷贝进 新的工作空间 覆盖 `src`

  3. 在`catkin_ws` 中，`catkin_make`

  4. 在`catkin_ws` 中，`source devel/setup.bash`

launch 文件夹：
  1. 检测机器人：gate.sh
  2. 餐厅： robot.sh
  3. 其他脚本是各功能模块的启动文件， 在gate.sh/robot.sh中有注释
