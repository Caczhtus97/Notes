# Android

shape 用于控制圆角等控件的样式，其中一共有六个属性，默认定义的类型是 `rectangle`

```xml
<?xml version="1.0" encoding="utf-8"?>
<shape
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape=["rectangle" | "oval" | "line" | "ring"] >   --- 默认为rectangle
    <corners  -- shape=“rectangle”时使用， 
        android:radius="integer"  -- 半径，会被下边的属性覆盖，默认为1dp，
        android:topLeftRadius="integer" 
        android:topRightRadius="integer"
        android:bottomLeftRadius="integer"
        android:bottomRightRadius="integer" />
    <gradient  -- 渐变
        android:angle="integer"
        android:centerX="integer"
        android:centerY="integer"
        android:centerColor="integer"
        android:endColor="color"
        android:gradientRadius="integer"
        android:startColor="color"
        android:type=["linear" | "radial" | "sweep"]
        android:useLevel=["true" | "false"] />
    <padding
        android:left="integer"
        android:top="integer"
        android:right="integer"
        android:bottom="integer" />
    <size    -- 指定大小，一般用在imageview配合scaleType属性使用。大小一般会适配滴
        android:width="integer"
        android:height="integer" />
    <solid    -- 填充颜色，可是是十六进制颜色。（比如想设置半透明效果，直接使用十六就只就OK）
        android:color="color" />
    <stroke    -- 指定边框，border，dashWidth和dashGap有一个为0dp则为实线
        android:width="integer"
        android:color="color"
        android:dashWidth="integer"    -- 虚线宽度
        android:dashGap="integer" />    -- 虚线间隔宽度
</shape>
```



## corners

用于控制四个边的圆角，属性 radius

## gradient

用于控制颜色的渐变效果，一旦设置这个属性，那么填充属性 `soild` 便不再生效。

gradient中的属性有：angle、startColor、endColor、centerColor、type、gradientRadius、centerX、centerY、useLevel。当type的值不同时，有些属性不生效。

type指定了渐变的类型，一共有三种类型：**linear（线性、默认）**、**radial（中间扩散）**、**sweep（旋转扫一周）**

先解释一下几个在任何类型下表现都相同的属性：

startColor：渐变开始的颜色

endColor：渐变结束的颜色

centerColor：渐变中间的颜色

useLevel：这个属性有两个值，true和false：一般要设置为false，默认也为false

## soild

用于控制背景填充颜色，属性 color

## size

用于控制控件的大小，属性height、width

## padding

用于控制控件的内边距，属性 top、bottom、left、right

## stroke

用于控制背景的边框

width：边框的宽度

color：控制边框的颜色

dashGap、dashWidth：控制边框是否为虚线，如果两个值同时设置为正数，那么边框就会是虚线。dashGap控制的是虚线之间的距离，dashWidth控制的是虚线段的长度，这两个值只要有一个没有设置或者被设置为0dp，那边框就是实线。



# 参考

[Android中shape的使用](https://blog.csdn.net/sysukehan/article/details/52022307)

