# Android

## SeekBar

### 1. 介绍

可以滑动的进度条，效果：

![image-20210629150101393](\photo\image-20210629150101393.png)

### 2. 使用

1. 在 xml 中定义 SeekBar 控件

   ```xml
   <androidx.appcompat.widget.AppCompatSeekBar
                   android:id="@+id/setting_seekBar"
                   android:layout_width="273pt"
                   android:layout_height="wrap_content"
                   android:layout_marginStart="40pt"
                   android:layout_marginTop="53pt"
                   android:layout_marginEnd="62pt"
                   android:layout_marginBottom="26pt"
                   android:max="100"
                   android:maxHeight="30pt"
                   android:minHeight="30pt"
                   android:thumbOffset="0dp"
                   android:progress="50"
                   app:layout_constraintBottom_toBottomOf="@id/setting_speechSpeedView"
                   app:layout_constraintEnd_toEndOf="@id/setting_speechSpeedView"
                   app:layout_constraintStart_toStartOf="@id/setting_speechSpeedView"
                   app:layout_constraintTop_toTopOf="@id/setting_speechSpeedView" />
   ```

2. 之后可以在声明周期中加载滑动块图片 setting_seekbar_block 

```kotlin
dataBinding.settingSeekBar.apply {
            thumb = ImageUtils.bitmap2Drawable(bitmap).apply { bounds = thumb.bounds }
            progress = TTSUtils.mSpeed
            setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
                override fun onProgressChanged(
                    seekBar: SeekBar?,
                    progress: Int,
                    fromUser: Boolean
                ) {
                    TTSUtils.mSpeed = progress
                    Log.i(TAG, "当前progress为 ${TTSUtils.mSpeed}")
                }

                override fun onStartTrackingTouch(seekBar: SeekBar?) {
                }

                override fun onStopTrackingTouch(seekBar: SeekBar?) {
                }

            })
        }
```

