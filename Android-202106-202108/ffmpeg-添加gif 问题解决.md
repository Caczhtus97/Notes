# FFmpeg

## 视频+Gif 移动问题记录

```shell
ffmpeg -y -i d.mp4 -i c.gif -lavfi "overlay=enable='mod(t,10)':x='90*mod(t, 10)-w':y='90*mod(t, 10)-w'" -shortest out.mp4
```

- ~~`-ignore_loop 这边如果为0，则视频不会渲染完成，会一直重复渲染；如果不舍，则gif只会播放一次`~~

### 问题描述

利用 -vf 以及 movie 命令在视频添加一张 gif 后，再向其添加一张可运动的 gif 会使得渲染不结束。若该新添加的gif设其只播放一次则不会有该问题，而当将其设置 `-ignore_loop 0` 后，则渲染一直进行。

### 尝试更换滤镜无果

```
ffmpeg -hide_banner -i big_buck_bunny.mp4 -vf "movie=doggie3.gif:loop=0,setpts=N/FRAME_RATE/TB[out];[0:v][out]overlay=x=W-w:y=0" -shortest out.mp4 -y
```

[参考文档](https://www.cnblogs.com/daner1257/p/14442777.html)

### 原因分析

由于测试的视频上面已经添加了一张无限循环的静态贴图（本身不动），在使用该命令时检索的视频时长可能为该 gif 的时间，从而导致渲染一直不能结束。

### 解决

在-lavfi 的脚本最后加上`:shortest=1` 表示视频结束就截断渲染

```
ffmpeg -y -i out1.mp4 -ignore_loop 0 -i 0.gif -lavfi "overlay=enable='mod(t,10)':x='90*mod(t, 10)-w':y='90*mod(t, 10)-h':shortest=1"  out2.mp4
```

### 注意

在贴图为静图时则不能使用该方法，而是要使用原来的命令，因为静态播放时间为0，如果这样做就会使得视频一开始就渲染结束。

