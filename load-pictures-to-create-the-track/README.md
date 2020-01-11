# TONGYOU

### 基于MFC的旅程轨迹生成系统

### 通过上传本地图片，获取本地图片的GPS信息，利用百度地图API确定图片摆设的具体位置，进行标注，继而将所有标注点连成一条轨迹。

### 构建环境

开发系统：macOS Catalina 10.15.2

开发语言：C++, HTML, JavaScript

开发工具：QT Creator, SQLPro for Postgres, VS Code

数据库：PostgresSQL

### 解决问题记录

1.构建组件时无法找到QWebView，于是用Widget自己提升为QWebEngineView

2.开源QT没有QMYSQL的驱动文件，所以改用PSQL数据库

### 目录说明

### Headers

bridge.h 利用WebChannel进行C++和QWebEngineView的联系

editor.h ”生成轨迹”

exif.h 提取照片的EXIF信息

login.h “登录”，只是作为连接数据库的试水，并没有实际功能

mainpage.h “主页”

newtrack.h ”新建规划”

select.h “选择轨迹”

### Sources

bridge.cpp

editor.cpp

exif.cpp

login.cpp

main.cpp

mainpage.cpp

newtrack.cpp

select.cpp

### Forms

editor.ui

login.ui

mainpage.ui

newtrack.ui

select.ui

### Resources

res.qrc/

/

tong7you.png

### Others

README.md
