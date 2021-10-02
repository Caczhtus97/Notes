```kotlin
package com.beemans.photofix.ui.fragments

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.*
import android.media.MediaMetadataRetriever
import android.os.Bundle
import android.util.Log
import android.view.Gravity
import android.view.View
import androidx.appcompat.widget.AppCompatTextView
import androidx.core.graphics.drawable.toBitmap
import androidx.core.graphics.drawable.toDrawable
import androidx.core.view.isNotEmpty
import androidx.core.view.isVisible
import androidx.core.view.updateLayoutParams
import androidx.core.widget.NestedScrollView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.beemans.common.data.constant.CommonStore
import com.beemans.common.ext.*
import com.beemans.common.ui.views.CustomDivider
import com.beemans.common.utils.*
import com.beemans.common.utils.umeng.UMPlatform
import com.beemans.photofix.R
import com.beemans.photofix.data.bean.*
import com.beemans.photofix.data.config.Config
import com.beemans.photofix.data.constant.Constant
import com.beemans.photofix.data.constant.Store
import com.beemans.photofix.databinding.FragmentCutoutResultBinding
import com.beemans.photofix.databinding.LayoutCutoutResultAdBinding
import com.beemans.photofix.domain.request.CoinViewModel
import com.beemans.photofix.domain.request.CutoutFileLoadViewModel
import com.beemans.photofix.domain.request.RechargeCenterViewModel
import com.beemans.photofix.domain.request.UserViewModel
import com.beemans.photofix.ext.jumpWeb
import com.beemans.photofix.ext.photoHandleTitle
import com.beemans.photofix.ext.selectPhotoByResultAction
import com.beemans.photofix.utils.FFmpegHelper
import com.beemans.photofix.integration.ffmpeg.GifToMp4
import com.beemans.photofix.integration.ffmpeg.Mp4AddSingleFixedPhoto
import com.beemans.photofix.integration.ffmpeg.Mp4ToGif
import com.beemans.photofix.integration.pay.PayHelper
import com.beemans.photofix.ui.adapter.CutoutResultAdapter
import com.beemans.photofix.ui.base.BaseFragment
import com.beemans.photofix.ui.views.diyvideo.MyRenderTextureView
import com.beemans.photofix.ui.views.diyvideo.MyTextureViewFactory
import com.beemans.photofix.ui.views.sticker.DrawableSticker
import com.beemans.photofix.ui.views.sticker.Sticker
import com.beemans.photofix.utils.*
import com.beemans.photofix.utils.AdHelper.isShowInsertAd
import com.blankj.utilcode.util.*
import com.bumptech.glide.Glide
import com.bumptech.glide.request.target.SimpleTarget
import com.bumptech.glide.request.transition.Transition
import com.hjq.permissions.Permission
import com.tiamosu.databinding.delegate.lazyDataBinding
import com.tiamosu.databinding.delegate.toDataBinding
import com.tiamosu.databinding.page.DataBindingConfig
import com.tiamosu.fly.base.dialog.loading.Loader
import com.tiamosu.fly.ext.addObserve
import com.tiamosu.fly.ext.clickNoRepeat
import com.tiamosu.navigation.ext.navigateUp
import com.yc.video.config.ConstantKeys
import com.yc.video.player.OnVideoStateListener
import com.yc.video.player.VideoViewManager
import com.yc.video.ui.view.BasisVideoController
import net.lucode.hackware.magicindicator.FragmentContainerHelper
import net.lucode.hackware.magicindicator.buildins.commonnavigator.CommonNavigator
import net.lucode.hackware.magicindicator.buildins.commonnavigator.abs.CommonNavigatorAdapter
import net.lucode.hackware.magicindicator.buildins.commonnavigator.abs.IPagerTitleView
import net.lucode.hackware.magicindicator.buildins.commonnavigator.titles.CommonPagerTitleView
import java.io.*
import java.util.*
import kotlin.math.pow
import kotlin.math.sqrt


/**
 * @author tiamosu
 * @date 2021/6/30.
 */
class CutoutResultFragment : BaseFragment() {
    private val dataBinding: FragmentCutoutResultBinding by lazyDataBinding()
    private val rechargeViewModel: RechargeCenterViewModel by lazyViewModel()
    private val coinViewModel: CoinViewModel by lazyViewModel()
    private val userViewModel: UserViewModel by lazyViewModel()
    private val cutoutFileViewModel: CutoutFileLoadViewModel by lazyViewModel()

    private val fragmentContainerHelper by lazy { FragmentContainerHelper() }
    private val adapter by lazy { CutoutResultAdapter() }

    private val categoryList by lazy { mutableListOf<String>() }
    private var forePath: String? = null    //人像前景图片地址
    private var backPath: String? = null    //背景图片地址
    private var backIsType: Int = 0  //背景图片的类型  0：静图  1：Gif  2：视频
    private var cutoutList: List<CutoutResponse>? = null
    private var curCutoutEntity: CutoutEntity? = null

    private var backDynamicLocalSourcePath: String? = null  //gif图片本地源地址
    private var backDynamicLocalTargetPath: String? = null  //gif图片本地目标地址
    private var forePicPath: String? = null //人像前景处理过后的地址
    private var backRealH = 1
    private var backRealW = 1

    private var rechargeResponse: RechargeListResponse? = null
    private var coinEntity: RechargeCenterCoinEntity? = null
    private var rechargePosition = -1 //保存图片提示弹框充值档位，大于-1则为保存图片提示弹框；反之为挽留弹框
    private var savePicCoin = 0 //保存图片所需金币
    private var curItemPos = 0 //当前图片item下标
    private var isPicSaved = false

    private val layoutManger by lazy {
        LinearLayoutManager(context, RecyclerView.HORIZONTAL, false)
    }
    private val actionTitle by lazy { Constant.TYPE_ACTION_CUTOUT.photoHandleTitle }

    private val basisVideoController by lazy { BasisVideoController(context) } //视频控制

    companion object {
        const val PARAM_FORE_PATH = "PARAM_FORE_PATH"
        const val PARAM_ENTITY = "PARAM_ENTITY"
        const val PARAM_CUTOUT_LIST = "PARAM_CUTOUT_LIST"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //禁止截屏
        ScreenHelper.setSecureFlags(context)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.fragment_cutout_result)
    }

    override fun initParameters(bundle: Bundle?) {
        cutoutList = bundle?.getParcelableArrayList(PARAM_CUTOUT_LIST)
        getParcelable<CutoutEntity>(PARAM_ENTITY)?.apply {
//            backPath = bgUrl
//            backIsType = bgType
            backPath = "http://192.168.1.37:8087/static/upload/image/bg/9068d9894545c45856b8e0cf2a6695b5.mp4"
            backIsType = 2
        }

        forePath = getString(PARAM_FORE_PATH)

        if (!Store.user.isVip) {
            savePicCoin = Store.coinCostMap[Constant.TYPE_ACTION_CUTOUT] ?: 0
        }
    }

    override fun initView(rootView: View?) {
        dataBinding.cutoutResultTitleBar.setTvTitle { text = actionTitle }

        when(backIsType) {
            0 -> {
                dataBinding.cutoutResultIvBg.isVisible = true
                dataBinding.cutoutResultPlayer.isVisible  =false
                dataBinding.cutoutResultIvBg.loadImage(backPath) {
                    onSuccess { _, _, _, _, _ ->
                        //图片过长情况下，按钮会跑到屏幕外
                        postDelayed({
                            dataBinding.cutoutResultNsv.fullScroll(NestedScrollView.FOCUS_DOWN)
                        }, 200)
                    }
                }
            }
            1 -> {
                dataBinding.cutoutResultIvBg.isVisible = true
                dataBinding.cutoutResultPlayer.isVisible  =false
                DialogHelper.showDynamicLoadingDialog(this)
                cutoutFileViewModel.resourceDownload(backPath!! , "gif")
            }
            2 -> {
                dataBinding.cutoutResultIvBg.isVisible = false
                dataBinding.cutoutResultPlayer.isVisible  =true
                DialogHelper.showDynamicLoadingDialog(this)
                //优化点：考虑内存空间不足的情况
                cutoutFileViewModel.resourceDownload(backPath!! , "mp4")
            }
        }

        forePath?.getBitmap {
            onSuccess { resource, _, _, _, _ ->
                dataBinding.cutoutResultViewSticker.apply {
                    addSticker(
                        DrawableSticker(resource?.toDrawable(resources)),
                        Sticker.Position.CENTER
                    )
                }
            }
        }

        dataBinding.cutoutResultRv.init(
            layoutManger, adapter,
            CustomDivider(8.pt2dp.toFloat()).apply { isVerticalOrientation = false }
        )
        dataBinding.cutoutResultRv.addOnScrollListener(RecyclerScrollListener())

        //加载其他图像功能入口视图
        dataBinding.cutoutResultViewAction.update(Constant.TYPE_ACTION_CUTOUT) { actionType ->
            selectPhotoByResultAction(actionType)
        }
    }

    override fun onFlyLazyInitView() {
        super.onFlyLazyInitView()
        loadPicGallery()
    }

    override fun createObserver() {
        //充值中心充值成功通知
        addObserve(sharedViewModel.isRechargeSuc) {
            picUnlock()
        }

        //套餐数据
        addObserve(rechargeViewModel.rechargeListLiveData) {
            rechargeResponse = it
        }

        //支付宝支付订单
        addObserve(rechargeViewModel.aliPayLiveData) { order ->
            order ?: return@addObserve
            PayHelper.payForAli(context, order, onSuccess = {
                paySuc()
            }, onCancel = {
                payCancel()
            }, onFailed = { errorMsg ->
                payFailed(errorMsg)
            })
        }
        //微信支付订单
        addObserve(rechargeViewModel.wxPayLiveData) { response ->
            response ?: return@addObserve
            PayHelper.payForWx(context, response, onSuccess = {
                paySuc()
            }, onCancel = {
                payCancel()
            }, onFailed = { errorMsg ->
                payFailed(errorMsg)
            })
        }

        //获取客服地址
        addObserve(userViewModel.csAddressLiveData) { csAddress ->
            if (csAddress.isNullOrBlank()) {
                DialogHelper.showContactQQDialog(this)
                return@addObserve
            }
            jumpWeb(csAddress, WebFragment.TITLE_CS)
        }

        //动态背景文件下载
        addObserve(cutoutFileViewModel.remoteFileLiveData) { response ->
            Loader.hideLoading()
            if (response?.isSuccess == true) {
                backDynamicLocalSourcePath = response.localPath
                CacheUtils.insertCutoutBgPath(response.remotePath!!, backDynamicLocalSourcePath!!)
                loadDynamicToView(response.type)
            } else {
                showToast("动态背景加载失败！请返回重试...")
            }
        }
    }

    override fun initEvent() {
        dataBinding.cutoutResultTitleBar.setPageBack(false) {
            onPageBack()
        }

        adapter.setNbOnItemClickListener { _, _, position ->
            if (curItemPos != position) {
                AgentEvent.event50211()
                curItemPos = position
                curCutoutEntity = adapter.data[position]
                backPath = curCutoutEntity?.bgUrl
                backIsType = curCutoutEntity?.bgType!!
                adapter.changeSelected(position)
                updateBg(position)
                updateIndicator(position)
            }
        }

        //保存图片
        dataBinding.cutoutResultTvSave.clickNoRepeat {
            AgentEvent.event50210()
            when (backIsType) {
                0 -> savePic()
                1 -> saveGif()
                2 -> saveVideo()
            }
        }

        //防止点击穿透
        dataBinding.cutoutResultFlPage.clickNoRepeat { }
    }

    /**
     * 更新分类标题显示
     */
    private fun updateIndicator(position: Int) {
        val category = adapter.data[position].category
        val index = categoryList.indexOf(category)
        fragmentContainerHelper.handlePageSelected(index)
    }

    /**
     * 更新 RecyclerView 展示位置
     */
    private fun updateRvPosition(index: Int) {
        val category = categoryList.getOrNull(index)
        val list = adapter.data
        val position = list.indexOfFirst { it.category == category }
        if (position >= 0 && position < list.size) {
            dataBinding.cutoutResultRv.smoothScrollToPosition(position)
        }
    }

    /**
     * 更新背景图片
     */
    private fun updateBg(position: Int) {
        val entity = adapter.data[position]

        when(entity.bgType) {
            0 -> {
                dataBinding.cutoutResultIvBg.isVisible = true
                dataBinding.cutoutResultPlayer.isVisible = false
                dataBinding.cutoutResultIvBg.loadImage(entity.bgUrl) {
                    options { placeholder(dataBinding.cutoutResultIvBg.drawable) }
                }
            }
            1 -> {
                dataBinding.cutoutResultIvBg.isVisible = true
                dataBinding.cutoutResultPlayer.isVisible = false
                DialogHelper.showDynamicLoadingDialog(this)
                cutoutFileViewModel.resourceDownload(entity.bgUrl , "gif")
            }
            2 -> {
                dataBinding.cutoutResultIvBg.isVisible = false
                dataBinding.cutoutResultPlayer.isVisible = true
                DialogHelper.showDynamicLoadingDialog(this)
                cutoutFileViewModel.resourceDownload(entity.bgUrl , "mp4")
            }
        }

        if (!Store.user.isVip && !entity.isFree) {
            dataBinding.cutoutResultTvSave.isEnabled = false
            dataBinding.cutoutResultTvSave
                .setBackgroundResource(R.drawable.shape_gradient_8pt_50999999_999999_270)
            loadAdView()
        } else {
            dataBinding.cutoutResultTvSave.isEnabled = true
            dataBinding.cutoutResultTvSave
                .setBackgroundResource(R.drawable.shape_gradient_8pt_9bc8ff_5747e9_270)
            removeAdPage()
        }
    }

    /**
     * 加载图片画廊
     */
    private fun loadPicGallery() {
        if (cutoutList.isNullOrEmpty()) {
            return
        }
        val picList = mutableListOf<CutoutEntity>()
        cutoutList?.forEach {
            categoryList.add(it.category)
            picList.addAll(it.bgList)
        }
        adapter.setList(picList)

        //更新页面进入所选择的背景图片对应的item位置
        postDelayed({
            val position = picList.indexOfFirst { it.isSelect }
            if (position >= 0 && position < picList.size) {
                dataBinding.cutoutResultRv.smoothScrollToPosition(position)
            }
        }, 200)

        CommonNavigator(context).apply {
            adapter = object : CommonNavigatorAdapter() {
                override fun getCount() = categoryList.size
                override fun getIndicator(context: Context) = null
                override fun getTitleView(context: Context, index: Int): IPagerTitleView {
                    return CommonPagerTitleView(context).apply {
                        val textView = AppCompatTextView(context).apply {
                            text = categoryList.getOrNull(index)
                            setContentView(this)
                            updateLayoutParams {
                                width = 48.pt2px
                                height = 30.pt2px
                                gravity = Gravity.CENTER
                            }
                            setOnClickListener {
                                fragmentContainerHelper.handlePageSelected(index)
                                updateRvPosition(index)
                            }
                        }

                        onPagerTitleChangeListener =
                            object : CommonPagerTitleView.OnPagerTitleChangeListener {
                                override fun onSelected(index: Int, totalCount: Int) {
                                    textView.apply {
                                        updateTextBold()
                                        updateTextSize(16.pt2px.toFloat())
                                        setTextColor(R.color.color_4b41a6.toColor())
                                    }
                                }

                                override fun onDeselected(index: Int, totalCount: Int) {
                                    textView.apply {
                                        updateTextBold(false)
                                        updateTextSize(13.pt2px.toFloat())
                                        setTextColor(R.color.color_666666.toColor())
                                    }
                                }

                                override fun onLeave(
                                    index: Int,
                                    totalCount: Int,
                                    leavePercent: Float,
                                    leftToRight: Boolean
                                ) {
                                }

                                override fun onEnter(
                                    index: Int,
                                    totalCount: Int,
                                    enterPercent: Float,
                                    leftToRight: Boolean
                                ) {
                                }
                            }
                    }
                }
            }
        }.let(dataBinding.cutoutResultIndicator::setNavigator)
        fragmentContainerHelper.attachMagicIndicator(dataBinding.cutoutResultIndicator)
    }

    /**
     * 展示看视频解锁视图
     */
    private fun loadAdView() {
        removeAdPage()
        R.layout.layout_cutout_result_ad.toDataBinding<LayoutCutoutResultAdBinding>()?.apply {
            dataBinding.cutoutResultFlPage.addView(this.root)
            dataBinding.cutoutResultFlPage.isVisible = true

            //订阅，前往充值中心
            fun subscribe() {
                AgentEvent.event50213()
                jumpFragment(R.id.rechargeCenterFragment)
            }

            if (!CommonStore.isShowAd) {
                cutoutResultAdGroupSkip.isVisible = false
                cutoutResultAdTvUnlock.text = "前往充值"
            }

            //看视频解锁
            cutoutResultAdTvUnlock.clickNoRepeat {
                if (!CommonStore.isShowAd) {
                    subscribe()
                    return@clickNoRepeat
                }
                AgentEvent.event50212()
                AdHelper.showRewardAd(
                    this@CutoutResultFragment,
                    actionName = actionTitle,
                    onRewardAction = { _, isReward ->
                        if (!isReward) return@showRewardAd
                        picUnlock()
                    })
            }

            //马上订阅
            cutoutResultAdViewSkip.clickNoRepeat {
                subscribe()
            }
        }
    }

    /**
     * 移除看视频解锁视图
     */
    private fun removeAdPage() {
        if (dataBinding.cutoutResultFlPage.isVisible) {
            dataBinding.cutoutResultFlPage.isVisible = false
        }
        if (dataBinding.cutoutResultFlPage.isNotEmpty()) {
            dataBinding.cutoutResultFlPage.removeAllViews()
        }
    }

    /**
     * Vip图片解锁
     */
    private fun picUnlock() {
        curCutoutEntity?.is_free = 1
        adapter.updateVipState(curItemPos)
        removeAdPage()
        dataBinding.cutoutResultTvSave.isEnabled = true
        dataBinding.cutoutResultTvSave
            .setBackgroundResource(R.drawable.shape_gradient_8pt_9bc8ff_5747e9_270)
    }

    /**
     * 支付成功
     */
    private fun paySuc() {
        showLoading()
        postDelayed({
            userInfo()
        }, 1000)
        rechargeList()

        when (rechargePosition) {
            0 -> {
                AgentEvent.event50155(actionTitle)
                AgentEvent.event50034("一键抠图_保存图片弹框", coinEntity?.price ?: 0.0)
            }
            1 -> {
                AgentEvent.event50158(actionTitle)
                AgentEvent.event50034("一键抠图_保存图片弹框", coinEntity?.price ?: 0.0)
            }
        }
        ReportHelper.reportAction(ReportHelper.ACTION_PAY_SUCCESS)
    }

    /**
     * 支付取消
     */
    private fun payCancel() {
        when (rechargePosition) {
            0 -> AgentEvent.event50157(actionTitle)
            1 -> AgentEvent.event50160(actionTitle)
        }
    }

    /**
     * 支付失败
     */
    private fun payFailed(errorMsg: String?) {
        when (rechargePosition) {
            0 -> AgentEvent.event50156(coinEntity?.price ?: 0.0, errorMsg, actionTitle)
            1 -> AgentEvent.event50159(coinEntity?.price ?: 0.0, errorMsg, actionTitle)
        }
    }

    /**
     * 保存图片
     */
    private fun savePic() {
        if (savePicCoin > 0
            && rechargeResponse?.recharge?.size ?: 0 > 0
            && Store.user.coin < savePicCoin
        ) {
            showSavePicPromptDialog()
            return
        }

        fun start() {
            //扣除金币
            reduceCoin()

            if (!Store.user.isVip && isShowInsertAd) {
                AdHelper.showInsertAd(this)
            }
            val bitmap = dataBinding.cutoutResultViewSticker.createBitmap()
            val file = ImageUtils.save2Album(bitmap, Bitmap.CompressFormat.JPEG)
            val msg = if (file != null) "图片已保存到相册" else "图片保存失败！"
            isPicSaved = true
            showToast(msg)
            AgentEvent.event50192(actionTitle)
        }

        PermissionHelper.with(this)
            .permission(*Permission.Group.STORAGE)
            .onExplainRequestReason { true }
            .onForwardToSettings { true }
            .request { _, _, isGrantedAll, _ ->
                if (isGrantedAll) {
                    start()
                }
                if (PermissionHelper.isGranted(*Permission.Group.STORAGE)) {
                    AgentEvent.event10020()
                } else {
                    AgentEvent.event10021()
                }
            }
    }

    /**
     * 保存Gif图片
     * */
    private fun saveGif() {
        if (savePicCoin > 0
            && rechargeResponse?.recharge?.size ?: 0 > 0
            && Store.user.coin < savePicCoin
        ) {
            showSavePicPromptDialog()
            return
        }

        fun start() {
            //扣除金币
            reduceCoin()

            if (!Store.user.isVip && isShowInsertAd) {
                AdHelper.showInsertAd(this)
            }
            backDynamicLocalTargetPath = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.gif"
            forePicPath = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.jpg"

            //预处理人像
            dataBinding.cutoutResultViewSticker.stickers[0].apply {
                val pic = drawable?.toBitmap()
                val mat = Matrix()
                mat.reset()
                val newPic =
                    pic?.let {
                        if (isFlippedHorizontally) {
                            //问题点：虽然可以达到预期的效果，但这边的变换有问题！！影响到角度也需一块变换
                            mat.preScale(
                                1f,
                                -1f,
                                (it.width / 2).toFloat(),
                                (it.height / 2).toFloat()
                            )
                        }
                        Bitmap.createBitmap(it, 0, 0, it.width, it.height, mat, true)
                    }
                ImageUtils.save(newPic, forePicPath, Bitmap.CompressFormat.WEBP)
            }

            //获取图片的实际尺寸
            Glide.with(context).asBitmap().load(backDynamicLocalSourcePath)
                .into(object : SimpleTarget<Bitmap?>() {
                    override fun onResourceReady(
                        resource: Bitmap,
                        transition: Transition<in Bitmap?>?
                    ) {
                        backRealH = resource.height
                        backRealW = resource.width
                    }
                })

            handler.postDelayed({//利用ffmpeg处理动图合成
                gifHandle(backDynamicLocalSourcePath!!, backDynamicLocalTargetPath!!)
            }, 1000)

//            AgentEvent.event50192(actionTitle)
        }

        PermissionHelper.with(this)
            .permission(*Permission.Group.STORAGE)
            .onExplainRequestReason { true }
            .onForwardToSettings { true }
            .request { _, _, isGrantedAll, _ ->
                if (isGrantedAll) {
                    start()
                }
                if (PermissionHelper.isGranted(*Permission.Group.STORAGE)) {
                    AgentEvent.event10020()
                } else {
                    AgentEvent.event10021()
                }
            }
    }

    /**
     * ffmpeg 合成图片
     * */
    fun gifHandle(sPath: String, tPath: String) {
        DialogHelper.showImageLoadingDialog(this)
        val mp4Path1 = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.mp4"
        val cmdGif2Mp4 = GifToMp4(sPath, mp4Path1, true)
        FFmpegHelper.start(cmdGif2Mp4) {
            onSuccess {
                Log.e("caczhtus", "gif转mp4 成功")
                val mp4Path2 = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.mp4"

                //向MP4添加贴纸
                dataBinding.cutoutResultViewSticker.stickers[0].apply {
                    val pxScale = backRealW / dataBinding.cutoutResultIvBg.width.toFloat()
                    val pyScale =
                        backRealH / dataBinding.cutoutResultIvBg.height.toFloat() //底图的缩放比
                    val w = currentWidth * pxScale
                    val h = currentHeight * pyScale
                    val handleLine = sqrt(w.pow(2.0f) + h.pow(2.0f))
                    var angle = currentAngle
                    if (isFlippedHorizontally) {
                        angle = -angle
                    }

                    val cmdMp4AddSingleFixedPhoto = Mp4AddSingleFixedPhoto(
                        mp4Path1,
                        mp4Path2,
                        forePicPath!!,
                        true,
                        w,
                        h,
                        mappedCenterPoint.x * pxScale - handleLine / 2,
                        mappedCenterPoint.y * pyScale - handleLine / 2,
                        angle
                    )
                    FFmpegHelper.start(cmdMp4AddSingleFixedPhoto) {
                        onSuccess {
                            Log.e("caczhtus", "mp4添加贴纸成功")
                            val cmdMp42Gif = Mp4ToGif(mp4Path2, tPath)
                            FFmpegHelper.start(cmdMp42Gif) {
                                onSuccess {
                                    Log.e("caczhtus", "mp4转gif成功  $tPath")
                                    //保存图片到相册
                                    val file = FFmpegHelper.gifSave2Album(tPath)
                                    isPicSaved = file != null
                                }
                                onFail {
                                    it?.let { it1 -> Log.e("caczhtus", it1) }
                                }
                                onFinally {
                                    Loader.hideLoading()
                                    if (isPicSaved) {
                                        showToast("图片已保存到相册")
                                    } else {
                                        showToast("图片保存失败！")
                                    }
                                }
                            }
                        }
                        onFail {
                            Loader.hideLoading()
                            showToast("图片保存失败！")
                            it?.let { it1 -> Log.e("caczhtus", it1) }
                        }
                    }
                } ?: Log.e("caczhtus", "currentSticker is null point")
            }
            onFail {
                Loader.hideLoading()
                showToast("图片保存失败！")
                it?.let { it1 -> Log.e("caczhtus", it1) }
            }
        }
    }

    /**
     * 保存为视频背景
     * */
    private fun saveVideo() {
        if (savePicCoin > 0
            && rechargeResponse?.recharge?.size ?: 0 > 0
            && Store.user.coin < savePicCoin
        ) {
            showSavePicPromptDialog()
            return
        }

        fun start() {
            //扣除金币
            reduceCoin()

            if (!Store.user.isVip && isShowInsertAd) {
                AdHelper.showInsertAd(this)
            }
            backDynamicLocalTargetPath = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.mp4"
            forePicPath = "${Config.cutoutDynamicDir}${System.currentTimeMillis()}.jpg"

            //预处理人像
            dataBinding.cutoutResultViewSticker.stickers[0].apply {
                val pic = drawable?.toBitmap()
                val mat = Matrix()
                mat.reset()
                val newPic =
                    pic?.let {
                        if (isFlippedHorizontally) {
                            //问题点：虽然可以达到预期的效果，但这边的变换有问题！！影响到角度也需一块变换
                            mat.preScale(
                                1f,
                                -1f,
                                (it.width / 2).toFloat(),
                                (it.height / 2).toFloat()
                            )
                        }
                        Bitmap.createBitmap(it, 0, 0, it.width, it.height, mat, true)
                    }
                ImageUtils.save(newPic, forePicPath, Bitmap.CompressFormat.WEBP)
            }

            val videoUtil = MediaMetadataRetriever() //用于获取视频实际尺寸
            videoUtil.setDataSource(backDynamicLocalSourcePath)
            backRealW = videoUtil.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_WIDTH)?.toInt() ?: -1
            backRealH = videoUtil.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_HEIGHT)?.toInt() ?: -1
            videoHandle(backDynamicLocalSourcePath!!, backDynamicLocalTargetPath!!)

//            AgentEvent.event50192(actionTitle)
        }

        PermissionHelper.with(this)
            .permission(*Permission.Group.STORAGE)
            .onExplainRequestReason { true }
            .onForwardToSettings { true }
            .request { _, _, isGrantedAll, _ ->
                if (isGrantedAll) {
                    start()
                }
                if (PermissionHelper.isGranted(*Permission.Group.STORAGE)) {
                    AgentEvent.event10020()
                } else {
                    AgentEvent.event10021()
                }
            }
    }

    /**
     * ffmpeg 合成视频
     * */
    private fun videoHandle(sPath: String, tPath: String) {
        DialogHelper.showImageLoadingDialog(this)
        //向视频添加贴纸
        dataBinding.cutoutResultViewSticker.stickers[0].apply {
            val pxScale = backRealW / dataBinding.cutoutResultPlayer.width.toFloat()
            val pyScale =
                backRealH / dataBinding.cutoutResultPlayer.height.toFloat() //底图的缩放比
            val w = currentWidth * pxScale
            val h = currentHeight * pyScale
            val handleLine = sqrt(w.pow(2.0f) + h.pow(2.0f))
            var angle = currentAngle
            if (isFlippedHorizontally) {
                angle = -angle
            }

            val cmdMp4AddSingleFixedPhoto = Mp4AddSingleFixedPhoto(
                sPath,
                tPath,
                forePicPath!!,
                true,
                w,
                h,
                mappedCenterPoint.x * pxScale - handleLine / 2,
                mappedCenterPoint.y * pyScale - handleLine / 2,
                angle
            )
            Log.e("caczhtus", "准备开始处理视频")
            FFmpegHelper.start(cmdMp4AddSingleFixedPhoto) {
                onSuccess {
                    Log.e("caczhtus", "视频添加贴纸成功")
                    val file = FFmpegHelper.videoSave2Album(tPath)
//                    isPicSaved = file != null
//                    isPicSaved = true
                }
                onFail {
                    Log.e("caczhtus", "onFail")
//                    isPicSaved = false
                    it?.let { it1 -> Log.e("caczhtus", it1) }
                }
                onFinally {
                    Log.e("caczhtus", "onFinally")
                    Loader.hideLoading()
//                    if (isPicSaved) {
//                        showToast("视频已保存到相册")
//                    } else {
//                        showToast("视频保存失败！")
//                    }
                }
            }
        } ?: Log.e("caczhtus", "currentSticker is null point")
    }

    /**
     * 初始化播放器的控制器（控制器只能有一个VideoPlayer使用）
     */
    @SuppressLint("WrongConstant")
    private fun initVideoController() {
        VideoViewManager.instance().setPlayOnMobileNetwork(true)//设置手机网络继续播放(使用config设置是无效的)
        basisVideoController.apply {
            setEnableOrientation(false)//关闭自动旋转
            removeAllViews()//移除所有组件
            setEnableInNormal(false) //竖屏模式下关闭手势控制
            setGestureEnabled(false)//关闭手势控制
            setCanChangePosition(false)//关闭滑动调节进度
            removeAllControlComponent()//移除所有控制组件
        }
        dataBinding.cutoutResultPlayer.setRenderViewFactory(MyTextureViewFactory.create())
        dataBinding.cutoutResultPlayer.setController(basisVideoController)
        dataBinding.cutoutResultPlayer.setScreenScaleType(MyRenderTextureView.SCREEN_SCALE_ONLY_WIDTH)
        dataBinding.cutoutResultPlayer.setLooping(true)
    }

    /**
     * 加载动态背景
     * */
    private fun loadDynamicToView(tag: Int) {
        when(tag) {
            1 -> {  //gif
                dataBinding.cutoutResultIvBg.loadImage(backDynamicLocalSourcePath) {
                    onSuccess { _, _, _, _, _ ->
                        //图片过长情况下，按钮会跑到屏幕外
                        postDelayed({
                            dataBinding.cutoutResultNsv.fullScroll(NestedScrollView.FOCUS_DOWN)
                        }, 200)
                    }
                }
            }
            2 -> {  //mp4
                dataBinding.cutoutResultPlayer.release()
                initVideoController()
                dataBinding.cutoutResultPlayer.url = backDynamicLocalSourcePath
                dataBinding.cutoutResultPlayer.start()
            }
        }
    }

    /**
     * 展示保存图片提示弹框
     */
    private fun showSavePicPromptDialog() {
        AgentEvent.event50153(actionTitle)
        DialogHelper.showSavePicPromptDialog(
            this, savePicCoin, rechargeResponse!!,
            onRechargeAction = { position, entity ->
                rechargePosition = position
                coinEntity = entity
                getPayOrder(entity)

                when (position) {
                    0 -> AgentEvent.event50154(actionTitle)
                    1 -> AgentEvent.event50169(actionTitle)
                }
            },
            onJumpRechargeAction = {
                jumpFragment(R.id.rechargeCenterFragment)
                AgentEvent.event50197(actionTitle)
            },
            onConsiderAction = { isWatchAd ->
                if (!isWatchAd) {
                    AgentEvent.event50161(actionTitle)
                    @Suppress("LABEL_NAME_CLASH")
                    return@showSavePicPromptDialog
                }

                AgentEvent.event50196(actionTitle)
                AdHelper.showRewardAd(
                    this,
                    actionName = actionTitle,
                    onRewardAction = { _, isReward ->
                        if (!isReward) return@showRewardAd
                        savePicCoin = 0
                    })
            },
            onCloseAction = {
                AgentEvent.event50161(actionTitle)
            })
    }

    /**
     * 获取微信、支付宝支付订单
     */
    private fun getPayOrder(coinEntity: RechargeCenterCoinEntity) {
        val rid = coinEntity.rid
        if (rid == 0) {
            showToast("请先选择套餐")
            return
        }
        when {
            UMConfig.isAppInstalled(UMPlatform.WECHAT) -> rechargeViewModel.wxPayInfo(rid)
            else -> rechargeViewModel.aliPayInfo(rid)
        }
    }

    private inner class RecyclerScrollListener : RecyclerView.OnScrollListener() {
        private var laseCategory = ""

        override fun onScrolled(recyclerView: RecyclerView, dx: Int, dy: Int) {}
        override fun onScrollStateChanged(recyclerView: RecyclerView, newState: Int) {
            //停止滚动
            if (newState != RecyclerView.SCROLL_STATE_IDLE) return
            val position = layoutManger.findLastCompletelyVisibleItemPosition()
            val category = adapter.data[position].category
            if (laseCategory != category) {
                laseCategory = category
                updateIndicator(position)
            }
        }
    }

    /**
     * 请求套餐数据
     */
    private fun rechargeList() {
        rechargeViewModel.rechargeList()
    }

    /**
     * 扣除金币，免费图片处理
     */
    private fun reduceCoin() {
        if (savePicCoin > 0) {
            coinViewModel.coinReduce(savePicCoin)
            savePicCoin = 0 //只扣除一次金币
        }
    }

    /**
     * 获取用户信息
     */
    private fun userInfo() {
        userViewModel.userData()
    }

    /**
     * 展示评价弹框
     */
    private fun showEvaluateDialog() {
        fun start() {
            DialogHelper.showEvaluateDialog(this,
                onAppraiseAction = {
                    jumpToAppStore(marketPkgName = getMarketPkgNameByChannel(Config.channel))
                },
                onFeedbackAction = {
                    requestCs()
                })
        }

        postDelayed({
            start()
        }, 2000)
    }

    /**
     * 意见反馈
     */
    private fun requestCs() {
        userViewModel.requestCs()
    }

    override fun doBusiness() {
        rechargeList()
        showEvaluateDialog()
    }

    /**
     * 页面返回
     */
    private fun onPageBack() {
        AgentEvent.event50214()
        when {
            !isPicSaved -> showExitPromptDialog()
            else -> navigateUp()
        }
    }

    /**
     * 退出页面时，用户未保存图片进行弹框提示
     */
    private fun showExitPromptDialog() {
        DialogHelper.showExitPromptDialog(this,
            onCancelAction = {
                AgentEvent.event50216()
            },
            onEnsureAction = {
                AgentEvent.event50215()
                navigateUp()
            })
    }

    override fun onDestroyView() {
        super.onDestroyView()
        dataBinding.cutoutResultPlayer.release()
    }

    override fun onDestroy() {
        super.onDestroy()
        //解除截止截屏
        ScreenHelper.clearSecureFlags(context)
    }

    override fun onBackPressedSupport(): Boolean {
        onPageBack()
        return true
    }
}
```

```kotlin
package com.beemans.photofix.utils

import android.Manifest
import android.content.ContentValues
import android.os.Build
import android.os.Environment
import android.provider.MediaStore
import android.util.Log
import com.arthenica.ffmpegkit.FFmpegKit
import com.beemans.photofix.integration.ffmpeg.base.FFmpegBase
import com.blankj.utilcode.util.*
import com.bumptech.glide.Glide
import com.bumptech.glide.load.DataSource
import com.bumptech.glide.load.engine.GlideException
import com.bumptech.glide.request.RequestListener
import com.bumptech.glide.request.target.Target
import com.tiamosu.fly.utils.launchIO
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileOutputStream
import java.io.OutputStream

/**
 *
 * @Author: zh
 * @Date: 2021/7/27
 */
object FFmpegHelper {

    /**
     * FFmpeg 命令执行入口
     * */
    fun start(cmdBean: FFmpegBase, listener: FFmpegCallback.() -> Unit = {}) {
        val callback = FFmpegCallback().apply(listener)

        FFmpegKit.executeAsync(cmdBean.generate()
        ) {
            var tag = it.returnCode
            when {
                tag.isSuccess -> {
                    callback.onSuccess?.invoke(it.duration)
                }
                tag.isError -> {
                    callback.onFail?.invoke(it.output)
                }
                tag.isCancel -> {
                    callback.onCancel?.invoke(it.duration)
//                    callback.onFail?.invoke(it.output)
                }
            }
            callback.onFinally?.invoke()
        }
    }

    class FFmpegCallback {
        internal var onSuccess: ((executionId: Long) -> Unit)? = null
        internal var onCancel: ((executionId: Long) -> Unit)? = null
        internal var onFail: ((errorMsg: String?) -> Unit)? = null
        internal var onFinally: (() -> Unit)? = null
        fun onSuccess(onSuccess: (executionId: Long) -> Unit) {
            this.onSuccess = onSuccess
        }

        fun onCancel(onCancel: (executionId: Long) -> Unit) {
            this.onCancel = onCancel
        }

        fun onFail(onFail: (errorMsg: String?) -> Unit) {
            this.onFail = onFail
        }

        fun onFinally(onFinally: () -> Unit) {
            this.onFinally = onFinally
        }
    }

    /**
     * Glide 获取URL图片文件
     * */
    fun getFile(
        picURL: String?,
        loadFailed: () -> Unit = {},
        resourceReady: (File?) -> Unit = {}
    ) {
        launchIO {
            Glide.with(Utils.getApp())
                .downloadOnly()
                .load(picURL)
                .listener(object : RequestListener<File> {
                    override fun onLoadFailed(
                        e: GlideException?,
                        model: Any?,
                        target: Target<File>?,
                        isFirstResource: Boolean
                    ): Boolean {
                        loadFailed.invoke()
                        return false
                    }

                    override fun onResourceReady(
                        resource: File?,
                        model: Any?,
                        target: Target<File>?,
                        dataSource: DataSource?,
                        isFirstResource: Boolean
                    ): Boolean {
                        resourceReady.invoke(resource)
                        return false
                    }
                }).preload()
        }
    }

    /**
     * 保存gif到图库
     * */
    fun gifSave2Album(sourcePath: String): File? {
        val file = File(sourcePath)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            val values = ContentValues()
            values.put(MediaStore.MediaColumns.TITLE, file.name)
            values.put(MediaStore.MediaColumns.DISPLAY_NAME, file.name)
            values.put(MediaStore.MediaColumns.MIME_TYPE, "image/gif")
            values.put(MediaStore.MediaColumns.DATE_TAKEN, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.DATE_MODIFIED, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.DATE_ADDED, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.SIZE, file.length())
            values.put(MediaStore.MediaColumns.RELATIVE_PATH, "${Environment.DIRECTORY_DCIM}/${Utils.getApp().packageName}")
            values.put(MediaStore.MediaColumns.IS_PENDING, 1)
            val contentUri = if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
                MediaStore.Images.Media.EXTERNAL_CONTENT_URI
            } else {
                MediaStore.Images.Media.INTERNAL_CONTENT_URI
            }
            val mUri = Utils.getApp().contentResolver.insert(contentUri, values) ?: return null
            var bos: OutputStream? = null
            try {
                bos = BufferedOutputStream(Utils.getApp().contentResolver.openOutputStream(mUri))
                bos.write(file.readBytes())
                bos.flush()

                values.clear()
                values.put(MediaStore.MediaColumns.IS_PENDING, 0)
                Utils.getApp().contentResolver.update(mUri, values, null, null)

                return UriUtils.uri2File(mUri)
            } catch (e : Exception) {
                Utils.getApp().contentResolver.delete(mUri, null, null)
                e.printStackTrace()
                return null
            } finally {
                try {
                    bos?.close()
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        } else {
            if (!PermissionUtils.isGranted(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                Log.e("caczhtus", "save to album need storage permission")
                return null
            } else {
                val picDir =
                    Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM)
                val destFile = File(picDir, Utils.getApp().packageName + "/" + file.name)
                if (!FileUtils.createFileByDeleteOldFile(destFile)) {
                    Log.e("caczhtus", "create or delete file <$file> failed.")
                    return null
                }
                var bos: OutputStream? = null
                try {
                    bos  = BufferedOutputStream(FileOutputStream(destFile))
                    bos.write(file.readBytes())
                    bos.flush()
                    FileUtils.notifySystemToScan(destFile)
                    return destFile
                } catch (e: Exception) {
                    e.printStackTrace()
                    return null
                } finally {
                    try {
                        bos?.close()
                    } catch (e : Exception) {
                        e.printStackTrace()
                    }
                }
            }
        }
    }

    /**
     * 保存video到图库
     * */
    fun videoSave2Album(sourcePath: String): File? {
        val file = File(sourcePath)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            val values = ContentValues()
            values.put(MediaStore.MediaColumns.TITLE, file.name)
            values.put(MediaStore.MediaColumns.DISPLAY_NAME, file.name)
            values.put(MediaStore.MediaColumns.MIME_TYPE, "video/mp4")
            values.put(MediaStore.MediaColumns.DATE_TAKEN, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.DATE_MODIFIED, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.DATE_ADDED, System.currentTimeMillis())
            values.put(MediaStore.MediaColumns.SIZE, file.length())
            values.put(MediaStore.MediaColumns.RELATIVE_PATH, "${Environment.DIRECTORY_DCIM}/${Utils.getApp().packageName}")
            values.put(MediaStore.MediaColumns.IS_PENDING, 1)
            val contentUri = if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
                MediaStore.Video.Media.EXTERNAL_CONTENT_URI
            } else {
                MediaStore.Video.Media.INTERNAL_CONTENT_URI
            }
            val mUri = Utils.getApp().contentResolver.insert(contentUri, values) ?: return null
            var bos: OutputStream? = null
            try {
                bos = BufferedOutputStream(Utils.getApp().contentResolver.openOutputStream(mUri))
                bos.write(file.readBytes())
                bos.flush()

                values.clear()
                values.put(MediaStore.MediaColumns.IS_PENDING, 0)
                Utils.getApp().contentResolver.update(mUri, values, null, null)

                return UriUtils.uri2File(mUri)
            }catch (e : Exception) {
                Utils.getApp().contentResolver.delete(mUri, null, null)
                e.printStackTrace()
                return null
            } finally {
                try {
                    bos?.close()
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        } else {
            if (!PermissionUtils.isGranted(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                Log.e("caczhtus", "save to album need storage permission")
                return null
            } else {
                val picDir =
                    Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM)
                val destFile = File(picDir, Utils.getApp().packageName + "/" + file.name)
                if (!FileUtils.createFileByDeleteOldFile(destFile)) {
                    Log.e("caczhtus", "create or delete file <$file> failed.")
                    return null
                }
                var bos: OutputStream? = null
                try {
                    bos  = BufferedOutputStream(FileOutputStream(destFile))
                    bos.write(file.readBytes())
                    bos.flush()
                    FileUtils.notifySystemToScan(destFile)
                    return destFile
                } catch (e: Exception) {
                    e.printStackTrace()
                    return null
                } finally {
                    try {
                        bos?.close()
                    } catch (e : Exception) {
                        e.printStackTrace()
                    }
                }
            }
        }
    }
}

```





