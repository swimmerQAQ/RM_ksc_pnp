所有文件包含cmakelists
注意顶层cmakelists就放在原有的层

步骤：
所有文件层级不变，放到一个文件夹
在顶层，也就是 contours——tree find什么什么 hsv kalmanFliter那些同一级
新建build文件夹 进取build,在当前位置打开终端
键入：cmake ..
键入： make
键入：./bin/pnp
上一步建议直接tab键，因为只有一个执行文件
###包含的主要内容### 自己粗略封装的库 solve解算 kalman滤波 标准工程样例
