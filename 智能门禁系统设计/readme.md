## 中山大学2017级软件工程单片机原理及实验期末project  
  
以下为此project设计需求文档  
### 1、对通道进出权限的管理  
  进出通道的方式就是对可以进出该通道的人进行进出方式的授权，进出方式通常有密码、读卡、其它身份识别几种种方式。  
  基本功能需要实现密码开门，持卡人必须输入密码正确才能开门  
  扩展功能：增加其它进出门的识别方式：刷卡、指纹识别、掌脉识别、人脸识别、车牌识别  
### 2、防止非法进入功能（扩展）
  若使用非授权卡，系统将拒绝开启门锁，并自动报警。  
### 3、实时监控功能（扩展）
  系统管理人员可以实时查看每个门区人员的进出情况、每个门区的状态（包括门的开关，各种非正常状态报警等）  
  实时监测房间的温度、湿度  
### 4、异常报警功能
  在异常情况下可以实现报警，如：非法侵入、门超时未关、温湿度超过报警界限（扩展）等  
  记录各种报警记录（扩展）  
### 5.记录查询（扩展）  
   出入记录查询功能，可查询任何人、任何时间在任何门出入的记录。  
   报警记录查询  
### 6.有实时时钟功能  
### 7.有键盘、显示屏  
### 8.可以读取门的定位（扩展）  
### 9.有网络功能：蓝牙、WIFI  
   根据老师给出的通信协议，上传门的状态和接收开关门的命令  
   扩展功能：把门的状态和开门记录等数据上传到云服务器，手机通过蓝牙控制开关门和读取门的状态，可在地图查询门的位置    
   
   
### 已上传了整个工程文件，详细请见 keil&proteus.zip 
