# Android

## Navigation 使用

1. 建navigation资源页
2. 在活动xml中利用fragmentcontainerview绑定默认导航（defaultnavhost和navGraph）
3. 在fragment用navigation跳转

## SparseArray

在深入分析SparseAray前,我们先说一下SparseArray的特点 ,同时介绍一下其使用场景;

Sparserray是Android中特有的数据结构,他的几个重要的特点；

以键值对形式进行存储，基于分查找,因此查找的时间复杂度为0(LogN);
.由于SparseArray中Key存储的是数组形式,因此可以直接以int作为Key。避免了HashMap的装箱拆箱操作,性能更高且int的存储开销远远小于Integer;
采用了延迟删除的机制(针对数组的删除扩容开销大的问题的优化， 具体稍后分析) ;
SparseArray小巧但是精悍，主类代码加上注释也只有不到500行，但是其中蕴含的思想却很值得学习。下面我们一起深入源码去学习一下其中的设计思想；

## ConstraintLayout使用

> [郭霖大佬博客](https://blog.csdn.net/guolin_blog/article/details/53122387)

## ViewPager2使用

## 公司自定义控件使用

1. TitleBarLayout
2. RecyleView
3. TabBarLayout
