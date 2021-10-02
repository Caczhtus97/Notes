# Android

## 架构

### `MVC`

### 分层架构

#### `DataManager` 层

数据管理，向上层（fragment、activity）提供接口。

![v2-0dc412d0f9be5a966d9cc0f60e68cdd8_720w](\photo\v2-0dc412d0f9be5a966d9cc0f60e68cdd8_720w.jpg)

#### 优点

大幅减轻Activity/Fragment的压力，实现数据统一管理，`DataManager`层成为了一个`UI`无关的`AppSDK`层

#### 缺点

需要添加嵌套回调，这个问题在引入`RxJava`之后被完美处理

#### 小结

即便如此，项目规模进一步往上之后，`DataManager`，Activity/Fragment的压力仍然会增大，更高的测试需求，要求进一步分离Activity/Fragment的代码。这时候就可以看看`MVP`和`MVVM`了

### `MVP`

> `MVC` 的C是即持有具体Model，又持有具体View，所以C很臃肿，分层架构就算抽出了`DataManager`，实质上仍然是一个`MVC`架构，而MVP和`MVVM`则是C持有具体View这个问题做了点文章，其中**MVP就是将大量的View <-> Model 交互剥离出来交由Presenter，Presenter持有抽象的View。**



### `MVVP`

数据绑定









## 注意

- 

