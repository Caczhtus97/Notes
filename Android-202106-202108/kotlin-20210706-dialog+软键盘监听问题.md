# Kotlin

## Dialog 和 软键盘监听问题

### 描述

需求是 dialog 点击空白区域关闭的同时，如果有软键盘存在，需要把软键盘一同关闭。

### 坑点

使用 `hideSoftInputFromWindow` 方法执行的是强制隐藏软键盘，然而，这个方法需要传一个windowToken进去，而当 dialog 关闭时，windowToken 也变为了 null 。于是无法使用该方法隐藏，会发现关闭dialog后，软键盘隐藏后又弹出的动作。

### 过程

以上的方法无果后，找到了几种比较接近效果的解决方案，不过这些方案均未验证，这里提出思路：

	1. 第一种方法，在 MainActivity 中重写 `dispatchTouchEvent` 方法，手动监听软键盘的显示隐藏，这个方法在 [Blankj](https://github.com/Blankj/AndroidUtilCode/blob/master/lib/utilcode/README-CN.md) Android 工具类中也有，不知出于何种原因被他注释掉了；
 	2. 第二种方法，监听软键盘以外的区域，当点击除了获取焦点的 EditText 以外的区域，先将软键盘关闭，之后如果还有点击，再把 dialog 关闭。也就是间断了一下执行逻辑，不过出于用户体验，这种方法也可以接受。

### 解决

在 `cancel` 监听中，获取当前 dialog 的焦点 view，之后利用 `toggleSoftInput` 方法可以达到将软键盘和 dialog 一起关闭的效果。不过 `toggleSoftInput` 这个方法是当软键盘如果打开，则调用后将其关闭；否在就将其打开。这样当 dialog 使用软键盘并手动将其关闭后，如果此时将 dialog 关闭，这个软键盘就又会打开。这时，我们可以在执行这个方法之前，先查看一下软键盘的存在状态，如果存在再执行这个方法，否则不执行。

```kotlin
dialog?.setOnCancelListener {
            val view = dialog?.currentFocus
            if (view is TextView) {
                if (KeyboardUtils.isSoftInputVisible(ActivityUtils.getTopActivity())) {
                    inputMethodManager?.toggleSoftInput(InputMethodManager.HIDE_NOT_ALWAYS, 0)
                }
            }
        }
```

其中，监听软键盘状态的工具均出自 [blankj](https://github.com/Blankj/AndroidUtilCode/blob/master/lib/utilcode/README-CN.md) 的 Android库。

### 补充

- dialog 以外的区域可以利用 cancel 相关的方法监听到，cancel 就相当于 dialog 盒子模型的背景。
- `setCanceledOnTouchOutside` 设置点击 cancel 区域是否关闭 dialog
- `setOnCancelListener` 设置点击 cancel 的监听