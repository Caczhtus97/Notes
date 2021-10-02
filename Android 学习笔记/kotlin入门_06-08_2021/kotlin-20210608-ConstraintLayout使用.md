# Android

## ConstraintLayout

**约束布局ConstraintLayout** 是一个ViewGroup，可以在Api9以上的Android系统使用它，它的出现主要是为了解决布局嵌套过多的问题，以灵活的方式定位和调整小部件。从 **Android Studio 2.3** 起，官方的模板默认使用 **ConstraintLayout**。

### 1. 使用

#### 1.1 添加依赖

```
 implementation 'com.android.support.constraint:constraint-layout:1.1.3'
```

#### 1.2 相对定位

```
app:app:layout_constraintLeft_toRightOf="a"
```

表示把本控件的左边约束到 a 的右边

##### 1.2.1 常用属性

```
layout_constraintLeft_toLeftOf
layout_constraintLeft_toRightOf
layout_constraintRight_toLeftOf
layout_constraintRight_toRightOf
layout_constraintTop_toTopOf
layout_constraintTop_toBottomOf
layout_constraintBottom_toTopOf
layout_constraintBottom_toBottomOf
layout_constraintBaseline_toBaselineOf
layout_constraintStart_toEndOf
layout_constraintStart_toStartOf
layout_constraintEnd_toStartOf
layout_constraintEnd_toEndOf
```

- top：上
- bottom：下
- left：左
- right：右
- baseline：文本基线，也就是textview中文本的水平线，常用于让文本对齐
- start：左侧基线
- end：右侧基线

#### 1.3 角度定位

角度定位指的是可以用一个角度和一个距离来约束两个空间的中心。

例如：

```xml
    <TextView
        android:id="@+id/TextView1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content" />

    <TextView
        android:id="@+id/TextView2"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        app:layout_constraintCircle="@+id/TextView1"
        app:layout_constraintCircleAngle="120"
        app:layout_constraintCircleRadius="150dp" />
```

![image-20210608142955933](\photo\image-20210608142955933.png)

>app:layout_constraintCircle="@+id/TextView1"
> app:layout_constraintCircleAngle="120"（角度）
> app:layout_constraintCircleRadius="150dp"（距离）

#### 1.4 边距

##### 1.4.1 常用外边距

> ConstraintLayout的边距常用属性如下：
>
>  android:layout_marginStart
>  android:layout_marginEnd
>  android:layout_marginLeft
>  android:layout_marginTop
>  android:layout_marginRight
>  android:layout_marginBottom

##### 1.4.2 使用边距前提

在约束布局中，使用边距必须先进行约束，否则边距不生效；同时，margin的值只能大于0

##### 1.4.3 goneMargin

goneMargin主要用于约束的控件可见性被设置为gone的时候使用的margin值。

>goneMargin属性使用如下：
>
>layout_goneMarginStart
> layout_goneMarginEnd
> layout_goneMarginLeft
> layout_goneMarginTop
> layout_goneMarginRight
> layout_goneMarginBottom

设置可见性属性：visibility

#### 1.5 居中和偏移

##### 1.5.1 居中

在RelativeLayout中，把控件放在布局中间的方法是把layout_centerInParent设为true，而在ConstraintLayout中的写法是：

```xml
app:layout_constraintBottom_toBottomOf="parent"
app:layout_constraintLeft_toLeftOf="parent"
app:layout_constraintRight_toRightOf="parent"
app:layout_constraintTop_toTopOf="parent"
```

Tips：**这边用脱离控件的方式可能更快捷**

> [郭霖大佬博客](https://blog.csdn.net/guolin_blog/article/details/53122387)

##### 1.5.2 偏移

控件在添加约束后再使用margin可以达到偏移的效果。

除此之外，ConstraintLayout 还提供另一种偏移的属性：

> layout_constraintHorizontal_bias       水平偏移
>
> layout_constarintVertical_bias             垂直偏移

假如现在要实现水平偏移，给TextView1的layout_constraintHorizontal_bias赋一个范围为 0-1 的值，假如赋值为0，则TextView1在布局的最左侧，假如赋值为1，则TextView1在布局的最右侧，假如假如赋值为0.5，则水平居中，假如假如赋值为0.3，则更倾向于左侧。
 垂直偏移同理。

**具体bias取值**见： https://blog.csdn.net/lerous/article/details/105494012

#### 1.6 尺寸约束

官方有四种方式：

##### 1.6.1 使用指定尺寸

##### 1.6.2 使用 warp_content

当控件的高度或宽度为wrap_content时，可以使用下列属性来控制最大、最小的高度或宽度：

- android:minWidth 最小的宽度
- android:minHeight 最小的高度
-  android:maxWidth 最大的 宽度
-  android:maxHeight 最大的高度

###### 注意事项

当ConstraintLayout为1.1版本以下时，使用这些属性**需要加上强制约束**，如下所示：

- app:constrainedWidth=”true”
- app:constrainedHeight=”true”

##### 1.6.3 使用 0dp（MATCH_CONSTRAINT）

官方不推荐在ConstraintLayout中使用match_parent，可以设置 0dp (MATCH_CONSTRAINT)

配合约束代替match_parent

```xml
<TextView
        android:id="@+id/TextView1"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_marginLeft="50dp"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toRightOf="parent"
        android:visibility="visible" />
```

宽度设为0dp，左右两边约束parent的左右两边，并设置左边边距为50dp，效果如下：

![image-20210608145711689](\photo\image-20210608145711689.png)

##### 1.6.4 宽高比

当宽或高至少有一个尺寸被设置为0dp时，可以通过属性layout_constraintDimensionRatio设置宽高比。

除此之外，在设置宽高比的值的时候，还可以在前面加W或H，分别指定宽度或高度限制。

>app:layout_constraintDimensionRatio="H,2:3"指的是  高:宽=2:3
 app:layout_constraintDimensionRatio="W,2:3"指的是  宽:高=2:3

#### 1.7 链

如果两个或以上控件通过下图的方式约束在一起，就可以认为是他们是一条链（图为横向的链，纵向同理）。

![image-20210608150541956](C:\Users\Administrator\Desktop\caczhtus\notes\photo\image-20210608150541956.png)

XML：

```xml
    <TextView
        android:id="@+id/TextView1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toLeftOf="@+id/TextView2" />

    <TextView
        android:id="@+id/TextView2"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toRightOf="@+id/TextView1"
        app:layout_constraintRight_toLeftOf="@+id/TextView3"
        app:layout_constraintRight_toRightOf="parent" />

    <TextView
        android:id="@+id/TextView3"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toRightOf="@+id/TextView2"
        app:layout_constraintRight_toRightOf="parent" />
```

##### 1.7.1 样式链

一条链的第一个控件是这条链的链头，我们可以在链头中设置 `layout_constraintHorizontal_chainStyle` 来改变整条链的样式。chains 提供了 3 种样式，分别是：

- CHAIN_SPREAD —— 展开元素 (默认)
- CHAIN_SPREAD_INSIDE —— 展开元素，但链的两端贴近parent
- CHAIN_PACKED —— 链的元素将被打包在一起

效果如图：

![image-20210608150853684](C:\Users\Administrator\Desktop\caczhtus\notes\photo\image-20210608150853684.png)

##### 1.7.2 权重链

上面的例子创建了一个样式链，除了样式链外，还可以创建一个权重链。
 可以留意到上面所用到的3个TextView宽度都为wrap_content，如果我们把宽度都设为0dp，这个时候可以在每个TextView中设置横向权重`layout_constraintHorizontal_weight(constraintVertical为纵向)` 来创建一个权重链，如下所示：

```xml
 <TextView
        android:id="@+id/TextView1"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toLeftOf="@+id/TextView2"
        app:layout_constraintHorizontal_weight="2" />

    <TextView
        android:id="@+id/TextView2"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toRightOf="@+id/TextView1"
        app:layout_constraintRight_toLeftOf="@+id/TextView3"
        app:layout_constraintRight_toRightOf="parent"
        app:layout_constraintHorizontal_weight="3" />

    <TextView
        android:id="@+id/TextView3"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        app:layout_constraintLeft_toRightOf="@+id/TextView2"
        app:layout_constraintRight_toRightOf="parent"
        app:layout_constraintHorizontal_weight="4" />
```

![image-20210608151637103](C:\Users\Administrator\Desktop\caczhtus\notes\photo\image-20210608151637103.png)

### 2. 工具

#### 2.1 Optimizer

当我们使用 MATCH_CONSTRAINT 时，ConstraintLayout 将对控件进行 2 次测量，ConstraintLayout在1.1中可以通过设置 **layout_optimizationLevel** 进行优化，可设置的值有：

- none：无优化
- standard：仅优化直接约束和屏障约束（默认）
- direct：优化直接约束
- barrier：优化屏障约束
- chain：优化链约束
- dimensions：优化尺寸测量

#### 2.2 Barrier

划出一条线把部分不规则的控件拦截到一边

#### 2.3 Group

可以把多个控件归为一组，方便成组隐藏

#### 2.4 Placeholder

Placeholder指的是占位符。在Placeholder中可使用setContent()设置另一个控件的id，使这个控件移动到占位符的位置。

#### 2.5 Guideline

Guildline像辅助线一样，在预览的时候帮助你完成布局（不会显示在界面上）

主要属性：

- android:orientation 垂直vertical，水平horizontal
- layout_constraintGuide_begin 开始位置
- layout_constraintGuide_end 结束位置
- layout_constraintGuide_percent 距离顶部的百分比(orientation = horizontal时则为距离左边)

