# Android

## ListView 使用

### 1. 列表主布局 ListView控件

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="vertical"
    android:layout_height="match_parent"
    android:layout_width="match_parent"
    >
    <LinearLayout
        android:orientation="horizontal"
        android:layout_width="match_parent"
        android:layout_height="wrap_content">

        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content"
            android:id="@+id/tv_name"
            android:text="姓名"
            android:gravity="center"
            android:textSize="25sp"/>
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content"
            android:id="@+id/tv_tel"
            android:text="电话"
            android:gravity="center"
            android:textSize="25sp"/>

    </LinearLayout>

    <ListView
        android:id="@+id/lv_list"
        android:layout_width="match_parent"
        android:layout_height="wrap_content">

    </ListView>

</LinearLayout>
```

### 2. 列表的项布局

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="horizontal"
    android:layout_height="match_parent"
    android:layout_width="match_parent"
    >

    <TextView
        android:layout_width="0dp"
        android:layout_weight="1"
        android:layout_height="wrap_content"
        android:id="@+id/tv_item_name"
        android:text="姓名"
        android:gravity="center"
        android:textSize="25sp"/>
    <TextView
        android:layout_width="0dp"
        android:layout_weight="1"
        android:layout_height="wrap_content"
        android:id="@+id/tv_item_tel"
        android:text="电话"
        android:gravity="center"
        android:textSize="25sp"/>

</LinearLayout>

```

### 3. 项的实体类

```kotlin
package com.example.demo_20210603_2.data.bean

/**
 *
 * @Author: zh
 * @Date: 2021/6/3
 */
data class Person(val name: String, val tel: String)
```



### 4. 设置监听器，并绑定列表项布局和主布局

```kotlin
package com.example.demo_20210603_2.ui.adapter

import com.example.demo_20210603_2.data.bean.Person
import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView
import com.example.demo_20210603_2.R

/**
 *
 * @Author: zh
 * @Date: 2021/6/3
 */
class myAdapter(private val context: Context, private val list: List<Person>): BaseAdapter() {

    private val ct = context
    private var ls = list

    override fun getCount(): Int {
        return ls.size
    }

    override fun getItem(position: Int): Any {
        return ls[position]
    }

    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val inflate = View.inflate(ct, R.layout.activity_listview, null)
        val name = inflate.findViewById<TextView>(R.id.tv_item_name)
        val tel = inflate.findViewById<TextView>(R.id.tv_item_tel)

        name.text = ls[position].name
        tel.text = ls[position].tel

        return inflate

    }

}
```

### 5. 主布局设置 ListView 的项监听器以及点击事件监听

```kotlin
package com.example.demo_20210603_2.ui.activity

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ListView
import android.widget.Toast
import android.widget.Toast.Callback
import com.example.demo_20210603_2.R
import com.example.demo_20210603_2.data.bean.Person
import com.example.demo_20210603_2.ui.adapter.myAdapter

class MainActivity : AppCompatActivity() {

    //listview使用
    /**
     * 1. xml：主布局，item布局
     * 2. kotlin：(1) 监听器绑定主布局和item的布局
     *           (2) 设置监听器
     *           (3) 设置每一项的点击事件
     * */

    private val data = mutableListOf(
        Person("张三","18555555555"),
        Person("李四","18555555556"),
        Person("王五","18555555557"),
        Person("赵六","18555555558"),
        Person("邓七","18555555559")
    )

    private lateinit var adapter: myAdapter

    @SuppressLint("WrongConstant")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        data.run {
            repeat(100) {
                this += this.get(0)
            }
        }

        adapter = myAdapter(this, data) //创造监听器

        val findViewById = findViewById<ListView>(R.id.lv_list)
        findViewById.adapter = adapter  //设置监听器

        findViewById.setOnItemClickListener { adapterView: AdapterView<*>, view1: View, i: Int, l: Long ->
            Toast.makeText(this, data[i].toString(), 0).show()
        }
    }
}
```



