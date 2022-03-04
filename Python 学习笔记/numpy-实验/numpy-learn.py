
# coding: utf-8

# ## 一、实验介绍
# 
# **1. 实验内容**  
# 
# 本章将介绍numpy，NumPy（Numerical Python的简称）是Python数值计算最重要的基础包。大多数提供科学计算的包都是用NumPy的数组作为构建基础。
# 
# **2. 实验要点**  
# 
# * NumPy的ndarray：一种多维数组对象
# * 通用函数：快速的元素级数组函数
# * 利用数组进行数据处理
# * 用于数组的文件输入输出
# * 线性代数
# * 伪随机数生成
# * 示例：随机漫步
# 
# **3. 实验环境**  
# * Python 3.6.6
# * numpy
# * random
# * matplotlib
# 
# 
# ## 二、实验步骤
# 
# **简介**
# 
# NumPy的部分功能如下：
# 
# - ndarray，一个具有矢量算术运算和复杂广播能力的快速且节省空间的多维数组。
# - 用于对整组数据进行快速运算的标准数学函数（无需编写循环）。
# - 用于读写磁盘数据的工具以及用于操作内存映射文件的工具。
# - 线性代数、随机数生成以及傅里叶变换功能。
# - 用于集成由C、C++、Fortran等语言编写的代码的A C API。
# 
# 由于NumPy提供了一个简单易用的C API，因此很容易将数据传递给由低级语言编写的外部库，外部库也能以NumPy数组的形式将数据返回给Python。这个功能使Python成为一种包装C/C++/Fortran历史代码库的选择，并使被包装库拥有一个动态的、易用的接口。
# 
# NumPy本身并没有提供多么高级的数据分析功能，理解NumPy数组以及面向数组的计算将有助于你更加高效地使用诸如pandas之类的工具。因为NumPy是一个很大的题目，我会在附录A中介绍更多NumPy高级功能，比如广播。
# 
# 对于大部分数据分析应用而言，我最关注的功能主要集中在：
# 
# - 用于数据整理和清理、子集构造和过滤、转换等快速的矢量化数组运算。
# - 常用的数组算法，如排序、唯一化、集合运算等。
# - 高效的描述统计和数据聚合/摘要运算。
# - 用于异构数据集的合并/连接运算的数据对齐和关系型数据运算。
# - 将条件逻辑表述为数组表达式（而不是带有if-elif-else分支的循环）。
# - 数据的分组运算（聚合、转换、函数应用等）。。
# 
# 虽然NumPy提供了通用的数值数据处理的计算基础，但大多数读者可能还是想将pandas作为统计和分析工作的基础，尤其是处理表格数据时。pandas还提供了一些NumPy所没有的领域特定的功能，如时间序列处理等。
# 
# >笔记：Python的面向数组计算可以追溯到1995年，Jim Hugunin创建了Numeric库。接下来的10年，许多科学编程社区纷纷开始使用Python的数组编程，但是进入21世纪，库的生态系统变得碎片化了。2005年，Travis Oliphant从Numeric和Numarray项目整了出了NumPy项目，进而所有社区都集合到了这个框架下。
# 
# NumPy之于数值计算特别重要的原因之一，是因为它可以高效处理大数组的数据。这是因为：
# 
# - NumPy是在一个连续的内存块中存储数据，独立于其他Python内置对象。NumPy的C语言编写的算法库可以操作内存，而不必进行类型检查或其它前期工作。比起Python的内置序列，NumPy数组使用的内存更少。
# - NumPy可以在整个数组上执行复杂的计算，而不需要Python的for循环。
# 
# 要搞明白具体的性能差距，考察一个包含一百万整数的数组，和一个等价的Python列表：

# In[1]:


import numpy as np
my_arr = np.arange(1000000)
my_list = list(range(1000000))


# 各个序列分别乘以2：

# In[2]:


get_ipython().run_line_magic('time', 'for _ in range(10): my_arr2 = my_arr * 2')


# In[3]:


get_ipython().run_line_magic('time', 'for _ in range(10): my_list2 = [x * 2 for x in my_list]')


# 基于NumPy的算法要比纯Python快10到100倍（甚至更快），并且使用的内存更少。
# 
# **1 NumPy的ndarray：一种多维数组对象**
# 
# NumPy最重要的一个特点就是其N维数组对象（即ndarray），该对象是一个快速而灵活的大数据集容器。你可以利用这种数组对整块数据执行一些数学运算，其语法跟标量元素之间的运算一样。
# 
# 要明白Python是如何利用与标量值类似的语法进行批次计算，我先引入NumPy，然后生成一个包含随机数据的小数组：

# In[4]:


import numpy as np
# Generate some random data
data = np.random.randn(2, 3)
data


# 然后进行数学运算：

# In[5]:


data * 10


# In[6]:


data + data


# 第一个例子中，所有的元素都乘以10。第二个例子中，每个元素都与自身相加。
# 
# >笔记：在本章及全书中，我会使用标准的NumPy惯用法``import numpy as np``。你当然也可以在代码中使用``from numpy import *``，但不建议这么做。``numpy``的命名空间很大，包含许多函数，其中一些的名字与Python的内置函数重名（比如min和max）。
# 
# ndarray是一个通用的同构数据多维容器，也就是说，其中的所有元素必须是相同类型的。每个数组都有一个shape（一个表示各维度大小的元组）和一个dtype（一个用于说明数组数据类型的对象）：

# In[7]:


data.shape


# In[8]:


data.dtype


# 本章将会介绍NumPy数组的基本用法，这对于本书后面各章的理解基本够用。虽然大多数数据分析工作不需要深入理解NumPy，但是精通面向数组的编程和思维方式是成为Python科学计算牛人的一大关键步骤。
# 
# >笔记：当你在本书中看到“数组”、“NumPy数组”、"ndarray"时，基本上都指的是同一样东西，即ndarray对象。
# 
# **1.1 创建ndarray**
# 
# 创建数组最简单的办法就是使用array函数。它接受一切序列型的对象（包括其他数组），然后产生一个新的含有传入数据的NumPy数组。以一个列表的转换为例：

# In[9]:


data1 = [6, 7.5, 8, 0, 1]
arr1 = np.array(data1)
arr1


# 嵌套序列（比如由一组等长列表组成的列表）将会被转换为一个多维数组：

# In[10]:


data2 = [[1, 2, 3, 4], [5, 6, 7, 8]]
arr2 = np.array(data2)
arr2


# 因为data2是列表的列表，NumPy数组arr2的两个维度的shape是从data2引入的。可以用属性ndim和shape验证：

# In[11]:


arr2.ndim


# In[12]:


arr2.shape


# 除非特别说明（稍后将会详细介绍），np.array会尝试为新建的这个数组推断出一个较为合适的数据类型。数据类型保存在一个特殊的dtype对象中。比如说，在上面的两个例子中，我们有：

# In[13]:


arr1.dtype


# In[14]:


arr2.dtype


# 除np.array之外，还有一些函数也可以新建数组。比如，zeros和ones分别可以创建指定长度或形状的全0或全1数组。empty可以创建一个没有任何具体值的数组。要用这些方法创建多维数组，只需传入一个表示形状的元组即可：

# In[15]:


np.zeros(10)


# In[16]:


np.zeros((3, 6))


# In[17]:


np.empty((2, 3, 2))


# >注意：认为np.empty会返回全0数组的想法是不安全的。很多情况下（如前所示），它返回的都是一些未初始化的垃圾值。
# 
# arange是Python内置函数range的数组版：

# In[18]:


np.arange(15)


# 表列出了一些数组创建函数。由于NumPy关注的是数值计算，因此，如果没有特别指定，数据类型基本都是float64（浮点数）。
# 
# ![表4-1 数组创建函数](img/7178691-78ab11f67e7077a6.png)
# 
# **1.2 ndarray的数据类型**
# 
# dtype（数据类型）是一个特殊的对象，它含有ndarray将一块内存解释为特定数据类型所需的信息：

# In[19]:


arr1 = np.array([1, 2, 3], dtype=np.float64)
arr2 = np.array([1, 2, 3], dtype=np.int32)
arr1.dtype


# In[20]:


arr2.dtype


# dtype是NumPy灵活交互其它系统的源泉之一。多数情况下，它们直接映射到相应的机器表示，这使得“读写磁盘上的二进制数据流”以及“集成低级语言代码（如C、Fortran）”等工作变得更加简单。数值型dtype的命名方式相同：一个类型名（如float或int），后面跟一个用于表示各元素位长的数字。标准的双精度浮点值（即Python中的float对象）需要占用8字节（即64位）。因此，该类型在NumPy中就记作float64。表4-2列出了NumPy所支持的全部数据类型。
# 
# >笔记：记不住这些NumPy的dtype也没关系，新手更是如此。通常只需要知道你所处理的数据的大致类型是浮点数、复数、整数、布尔值、字符串，还是普通的Python对象即可。当你需要控制数据在内存和磁盘中的存储方式时（尤其是对大数据集），那就得了解如何控制存储类型。
# 
# ![](img/7178691-2f2d7406a8bc076c.png)
# 
# ![](img/7178691-5cc31115615737b7.png)
# 
# 你可以通过ndarray的astype方法明确地将一个数组从一个dtype转换成另一个dtype：

# In[21]:


arr = np.array([1, 2, 3, 4, 5])
arr.dtype


# In[22]:


float_arr = arr.astype(np.float64)
float_arr.dtype


# 在本例中，整数被转换成了浮点数。如果将浮点数转换成整数，则小数部分将会被截取删除：

# In[23]:


arr = np.array([3.7, -1.2, -2.6, 0.5, 12.9, 10.1])
arr


# In[24]:


arr.astype(np.int32)


# 如果某字符串数组表示的全是数字，也可以用astype将其转换为数值形式：

# In[25]:


numeric_strings = np.array(['1.25', '-9.6', '42'], dtype=np.string_)
numeric_strings.astype(float)


# >注意：使用numpy.string_类型时，一定要小心，因为NumPy的字符串数据是大小固定的，发生截取时，不会发出警告。pandas提供了更多非数值数据的便利的处理方法。
# 
# 如果转换过程因为某种原因而失败了（比如某个不能被转换为float64的字符串），就会引发一个ValueError。这里，我比较懒，写的是float而不是np.float64；NumPy很聪明，它会将Python类型映射到等价的dtype上。
# 
# 数组的dtype还有另一个属性：

# In[26]:


int_array = np.arange(10)
calibers = np.array([.22, .270, .357, .380, .44, .50], dtype=np.float64)
int_array.astype(calibers.dtype)


# 你还可以用简洁的类型代码来表示dtype：

# In[27]:


empty_uint32 = np.empty(8, dtype='u4')
empty_uint32


# >笔记：调用astype总会创建一个新的数组（一个数据的备份），即使新的dtype与旧的dtype相同。
# 
# **1.3 NumPy数组的运算**
# 
# 数组很重要，因为它使你不用编写循环即可对数据执行批量运算。NumPy用户称其为矢量化（vectorization）。大小相等的数组之间的任何算术运算都会将运算应用到元素级：

# In[28]:


arr = np.array([[1., 2., 3.], [4., 5., 6.]])
arr


# In[29]:


arr*arr


# In[30]:


arr-arr


# 数组与标量的算术运算会将标量值传播到各个元素：

# In[31]:


1 / arr


# In[32]:


arr ** 0.5


# 大小相同的数组之间的比较会生成布尔值数组：

# In[33]:


arr2 = np.array([[0., 4., 1.], [7., 2., 12.]])
arr2


# In[34]:


arr2 > arr


# 不同大小的数组之间的运算叫做广播（broadcasting），将在附录A中对其进行详细讨论。本书的内容不需要对广播机制有多深的理解。
# 
# **1.4 基本的索引和切片**
# 
# NumPy数组的索引是一个内容丰富的主题，因为选取数据子集或单个元素的方式有很多。一维数组很简单。从表面上看，它们跟Python列表的功能差不多：

# In[35]:


arr = np.arange(10)
arr


# In[36]:


arr[5]


# In[37]:


arr[5:8]


# In[38]:


arr[5:8] = 12
arr


# 如上所示，当你将一个标量值赋值给一个切片时（如arr[5:8]=12），该值会自动传播（也就说后面将会讲到的“广播”）到整个选区。跟列表最重要的区别在于，数组切片是原始数组的视图。这意味着数据不会被复制，视图上的任何修改都会直接反映到源数组上。
# 
# 作为例子，先创建一个arr的切片：

# In[39]:


arr_slice = arr[5:8]
arr_slice


# 现在，当修改arr_slice中的值，变动也会体现在原始数组arr中：

# In[40]:


arr_slice[1] = 12345
arr


# 切片[ : ]会给数组中的所有值赋值：

# In[41]:


arr_slice[:] = 64
arr


# 
# 如果你刚开始接触NumPy，可能会对此感到惊讶（尤其是当你曾经用过其他热衷于复制数组数据的编程语言）。由于NumPy的设计目的是处理大数据，所以你可以想象一下，假如NumPy坚持要将数据复制来复制去的话会产生何等的性能和内存问题。
# 
# >注意：如果你想要得到的是ndarray切片的一份副本而非视图，就需要明确地进行复制操作，例如``arr[5:8].copy()``。
# 
# 对于高维度数组，能做的事情更多。在一个二维数组中，各索引位置上的元素不再是标量而是一维数组：

# In[42]:


arr2d = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
arr2d[2]


# 因此，可以对各个元素进行递归访问，但这样需要做的事情有点多。你可以传入一个以逗号隔开的索引列表来选取单个元素。也就是说，下面两种方式是等价的：

# In[43]:


arr2d[0][2]


# In[44]:


arr2d[0, 2]


# 图说明了二维数组的索引方式。轴0作为行，轴1作为列。
# 
# ![图4-1 NumPy数组中的元素索引](img/7178691-0a641536f73f560e.png)
# 
# 在多维数组中，如果省略了后面的索引，则返回对象会是一个维度低一点的ndarray（它含有高一级维度上的所有数据）。因此，在2×2×3数组arr3d中：

# In[45]:


arr3d = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]])
arr3d


# arr3d[0]是一个2×3数组：

# In[46]:


arr3d[0]


# 标量值和数组都可以被赋值给arr3d[0]：

# In[47]:


old_values = arr3d[0].copy()
arr3d[0] = 42
arr3d


# In[48]:


arr3d[0] = old_values
arr3d


# 相似的，arr3d[1,0]可以访问索引以(1,0)开头的那些值（以一维数组的形式返回）：

# In[49]:


arr3d[1, 0]


# 虽然是用两步进行索引的，表达式是相同的：

# In[50]:


x = arr3d[1]
x


# In[51]:


x[0]


# 注意，在上面所有这些选取数组子集的例子中，返回的数组都是视图。
# 
# **1.5 切片索引**
# 
# ndarray的切片语法跟Python列表这样的一维对象差不多：

# In[52]:


arr


# In[53]:


arr[1:6]


# 对于之前的二维数组arr2d，其切片方式稍显不同：

# In[54]:


arr2d


# In[55]:


arr2d[:2]


# 可以看出，它是沿着第0轴（即第一个轴）切片的。也就是说，切片是沿着一个轴向选取元素的。表达式arr2d[:2]可以被认为是“选取arr2d的前两行”。
# 
# 你可以一次传入多个切片，就像传入多个索引那样：

# In[56]:


arr2d[:2, 1:]


# 像这样进行切片时，只能得到相同维数的数组视图。通过将整数索引和切片混合，可以得到低维度的切片。
# 
# 例如，我可以选取第二行的前两列：

# In[57]:


arr2d[1, :2]


# 相似的，还可以选择第三列的前两行：

# In[58]:


arr2d[:2, 2]


# 图对此进行了说明。注意，“只有冒号”表示选取整个轴，因此你可以像下面这样只对高维轴进行切片：
# 
# ![图4-2 二维数组切片](img/7178691-9da32d2f4629c304.png)

# In[59]:


arr2d[:2, 1:] = 0
arr2d


# **1.6 布尔型索引**
# 
# 来看这样一个例子，假设我们有一个用于存储数据的数组以及一个存储姓名的数组（含有重复项）。在这里，我将使用numpy.random中的randn函数生成一些正态分布的随机数据：

# In[60]:


names = np.array(['Bob', 'Joe', 'Will', 'Bob', 'Will', 'Joe', 'Joe'])
data = np.random.randn(7, 4)


# In[61]:


names


# In[62]:


data


# 假设每个名字都对应data数组中的一行，而我们想要选出对应于名字"Bob"的所有行。跟算术运算一样，数组的比较运算（如==）也是矢量化的。因此，对names和字符串"Bob"的比较运算将会产生一个布尔型数组：

# In[63]:


names == 'Bob'


# 这个布尔型数组可用于数组索引：

# In[64]:


data[names == 'Bob']


# 布尔型数组的长度必须跟被索引的轴长度一致。此外，还可以将布尔型数组跟切片、整数（或整数序列，稍后将对此进行详细讲解）混合使用：
# 
# >注意：如果布尔型数组的长度不对，布尔型选择就会出错，因此一定要小心。
# 
# 下面的例子，我选取了``names == 'Bob'``的行，并索引了列：

# In[65]:


data[names == 'Bob', 2:]


# In[66]:


data[names == 'Bob', 3]


# 要选择除"Bob"以外的其他值，既可以使用不等于符号（!=），也可以通过~对条件进行否定：

# In[67]:


names != 'Bob'


# In[68]:


data[~(names == 'Bob')]


# ~操作符用来反转条件很好用：

# In[69]:


cond = names == 'Bob'
data[~cond]


# 选取这三个名字中的两个需要组合应用多个布尔条件，使用&（和）、|（或）之类的布尔算术运算符即可：

# In[70]:


mask = (names == 'Bob') | (names == 'Will')
mask


# In[71]:


data[mask]


# 通过布尔型索引选取数组中的数据，将总是创建数据的副本，即使返回一模一样的数组也是如此。
# 
# >注意：Python关键字and和or在布尔型数组中无效。要使用&与|。
# 
# 通过布尔型数组设置值是一种经常用到的手段。为了将data中的所有负值都设置为0，我们只需：

# In[72]:


data[data < 0] = 0
data


# 
# 后面会看到，这类二维数据的操作也可以用pandas方便的来做。
# 
# **1.7 花式索引**
# 
# 花式索引（Fancy indexing）是一个NumPy术语，它指的是利用整数数组进行索引。假设我们有一个8×4数组：

# In[73]:


arr = np.empty((8, 4))
for i in range(8):
    arr[i] = i
arr


# 为了以特定顺序选取行子集，只需传入一个用于指定顺序的整数列表或ndarray即可：

# In[74]:


arr[[4, 3, 0, 6]]


# 这段代码确实达到我们的要求了！使用负数索引将会从末尾开始选取行：

# In[75]:


arr[[-3, -5, -7]]


# 一次传入多个索引数组会有一点特别。它返回的是一个一维数组，其中的元素对应各个索引元组：

# In[76]:


arr = np.arange(32).reshape((8, 4))
arr


# In[77]:


arr[[1, 5, 7, 2], [0, 3, 1, 2]]


# 最终选出的是元素(1,0)、(5,3)、(7,1)和(2,2)。无论数组是多少维的，花式索引总是一维的。
# 
# 这个花式索引的行为可能会跟某些用户的预期不一样（包括我在内），选取矩阵的行列子集应该是矩形区域的形式才对。下面是得到该结果的一个办法：

# In[78]:


arr[[1, 5, 7, 2]][:, [0, 3, 1, 2]]


# 记住，花式索引跟切片不一样，它总是将数据复制到新数组中。
# 
# **1.8 数组转置和轴对换**
# 
# 转置是重塑的一种特殊形式，它返回的是源数据的视图（不会进行任何复制操作）。数组不仅有transpose方法，还有一个特殊的T属性：

# In[79]:


arr = np.arange(15).reshape((3, 5))
arr


# In[80]:


arr.T


# 在进行矩阵计算时，经常需要用到该操作，比如利用np.dot计算矩阵内积：

# In[81]:


arr = np.random.randn(6, 3)
arr


# In[82]:


np.dot(arr.T, arr)


# 对于高维数组，transpose需要得到一个由轴编号组成的元组才能对这些轴进行转置（比较费脑子）：

# In[83]:


arr = np.arange(16).reshape((2, 2, 4))
arr


# In[84]:


arr.transpose((1, 0, 2))


# 这里，第一个轴被换成了第二个，第二个轴被换成了第一个，最后一个轴不变。
# 
# 简单的转置可以使用.T，它其实就是进行轴对换而已。ndarray还有一个swapaxes方法，它需要接受一对轴编号：

# In[85]:


arr


# In[86]:


arr.swapaxes(1, 2)


# **2 通用函数：快速的元素级数组函数**
# 
# 通用函数（即ufunc）是一种对ndarray中的数据执行元素级运算的函数。你可以将其看做简单函数（接受一个或多个标量值，并产生一个或多个标量值）的矢量化包装器。
# 
# 许多ufunc都是简单的元素级变体，如sqrt和exp：

# In[87]:


arr = np.arange(10)
arr


# In[88]:


np.sqrt(arr)


# In[89]:


np.exp(arr)


# 这些都是一元（unary）ufunc。另外一些（如add或maximum）接受2个数组（因此也叫二元（binary）ufunc），并返回一个结果数组：

# In[90]:


x = np.random.randn(8)
x


# In[91]:


y = np.random.randn(8)
y


# In[92]:


np.maximum(x, y)


# 这里，numpy.maximum计算了x和y中元素级别最大的元素。
# 
# 虽然并不常见，但有些ufunc的确可以返回多个数组。modf就是一个例子，它是Python内置函数divmod的矢量化版本，它会返回浮点数数组的小数和整数部分：

# In[93]:


arr = np.random.randn(7) * 5
arr


# In[94]:


remainder, whole_part = np.modf(arr)
remainder


# In[95]:


whole_part


# Ufuncs可以接受一个out可选参数，这样就能在数组原地进行操作：

# In[96]:


arr


# In[97]:


np.sqrt(arr)


# In[98]:


np.sqrt(arr, arr)


# In[99]:


arr


# 表1和表2分别列出了一些一元和二元ufunc。
# 
# ![](img/7178691-1d494e73b61c7ced.png)
# 
# ![](img/7178691-2be79faf68ab6ff8.png)
# 
# ![](img/7178691-4e38d02a66481530.png)
# 
# ![](img/7178691-eff1e61e5464159f.png)
# 
# ![](img/7178691-236dba83b6a420cc.png)
# 
# **3 利用数组进行数据处理**
# 
# NumPy数组使你可以将许多种数据处理任务表述为简洁的数组表达式（否则需要编写循环）。用数组表达式代替循环的做法，通常被称为矢量化。一般来说，矢量化数组运算要比等价的纯Python方式快上一两个数量级（甚至更多），尤其是各种数值计算。在后面内容中（见附录A）我将介绍广播，这是一种针对矢量化计算的强大手段。
# 
# 作为简单的例子，假设我们想要在一组值（网格型）上计算函数``sqrt(x^2+y^2)``。np.meshgrid函数接受两个一维数组，并产生两个二维矩阵（对应于两个数组中所有的(x,y)对）：

# In[100]:


points = np.arange(-5, 5, 0.01) # 1000 equally spaced points
xs, ys = np.meshgrid(points, points)
ys


# 现在，对该函数的求值运算就好办了，把这两个数组当做两个浮点数那样编写表达式即可：

# In[101]:


z = np.sqrt(xs ** 2 + ys ** 2)
z


# 作为第9章的先导，我用matplotlib创建了这个二维数组的可视化：

# In[104]:


import matplotlib.pyplot as plt
get_ipython().run_line_magic('matplotlib', 'inline')


# In[105]:


plt.imshow(z, cmap=plt.cm.gray); plt.colorbar()


# In[108]:


plt.title("Image plot of $\sqrt{x^2 + y^2}$ for a grid of values")
plt.imshow(z, cmap=plt.cm.gray); 
plt.colorbar()


# **3.1 将条件逻辑表述为数组运算**
# 
# numpy.where函数是三元表达式x if condition else y的矢量化版本。假设我们有一个布尔数组和两个值数组：

# In[109]:


xarr = np.array([1.1, 1.2, 1.3, 1.4, 1.5])
yarr = np.array([2.1, 2.2, 2.3, 2.4, 2.5])
cond = np.array([True, False, True, True, False])


# 假设我们想要根据cond中的值选取xarr和yarr的值：当cond中的值为True时，选取xarr的值，否则从yarr中选取。列表推导式的写法应该如下所示：

# In[110]:


result = [(x if c else y)
          for x, y, c in zip(xarr, yarr, cond)]
result


# 这有几个问题。第一，它对大数组的处理速度不是很快（因为所有工作都是由纯Python完成的）。第二，无法用于多维数组。若使用np.where，则可以将该功能写得非常简洁：

# In[111]:


result = np.where(cond, xarr, yarr)
result


# np.where的第二个和第三个参数不必是数组，它们都可以是标量值。在数据分析工作中，where通常用于根据另一个数组而产生一个新的数组。假设有一个由随机数据组成的矩阵，你希望将所有正值替换为2，将所有负值替换为－2。若利用np.where，则会非常简单：

# In[112]:


arr = np.random.randn(4, 4)
arr


# In[113]:


arr > 0


# In[114]:


np.where(arr > 0, 2, -2)


# 使用np.where，可以将标量和数组结合起来。例如，我可用常数2替换arr中所有正的值：

# In[115]:


np.where(arr > 0, 2, arr) # set only positive values to 2


# 传递给where的数组大小可以不相等，甚至可以是标量值。
# 
# **3.2 数学和统计方法**
# 
# 可以通过数组上的一组数学函数对整个数组或某个轴向的数据进行统计计算。sum、mean以及标准差std等聚合计算（aggregation，通常叫做约简（reduction））既可以当做数组的实例方法调用，也可以当做顶级NumPy函数使用。
# 
# 这里，我生成了一些正态分布随机数据，然后做了聚类统计：

# In[116]:


arr = np.random.randn(5, 4)
arr


# In[117]:


arr.mean()


# In[118]:


np.mean(arr)


# In[119]:


arr.sum()


# mean和sum这类的函数可以接受一个axis选项参数，用于计算该轴向上的统计值，最终结果是一个少一维的数组：

# In[120]:


arr.mean(axis=1)


# In[121]:


arr.sum(axis=0)


# 这里，arr.mean(1)是“计算行的平均值”，arr.sum(0)是“计算每列的和”。
# 
# 其他如cumsum和cumprod之类的方法则不聚合，而是产生一个由中间结果组成的数组：

# In[122]:


arr = np.array([0, 1, 2, 3, 4, 5, 6, 7])
arr.cumsum()


# 在多维数组中，累加函数（如cumsum）返回的是同样大小的数组，但是会根据每个低维的切片沿着标记轴计算部分聚类：

# In[123]:


arr = np.array([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
arr


# In[124]:


arr.cumsum(axis=0)


# In[125]:


arr.cumprod(axis=1)


# 表列出了全部的基本数组统计方法。后续章节中有很多例子都会用到这些方法。
# 
# ![](img/7178691-a6c6df3ca8e0b98e.png)
# 
# ![](img/7178691-866fcde885b1d357.png)
# 
# **3.3 用于布尔型数组的方法**
# 
# 在上面这些方法中，布尔值会被强制转换为1（True）和0（False）。因此，sum经常被用来对布尔型数组中的True值计数：

# In[126]:


arr = np.random.randn(100)
(arr > 0).sum() # Number of positive values


# 另外还有两个方法any和all，它们对布尔型数组非常有用。any用于测试数组中是否存在一个或多个True，而all则检查数组中所有值是否都是True：

# In[127]:


bools = np.array([False, False, True, False])
bools.any()


# In[128]:


bools.all()


# 这两个方法也能用于非布尔型数组，所有非0元素将会被当做True。
# 
# **3.4 排序**
# 
# 跟Python内置的列表类型一样，NumPy数组也可以通过sort方法就地排序：

# In[130]:


arr = np.random.randn(6)
arr


# In[131]:


arr.sort()
arr


# 多维数组可以在任何一个轴向上进行排序，只需将轴编号传给sort即可：

# In[132]:


arr = np.random.randn(5, 3)
arr


# In[133]:


arr.sort(1)
arr


# 顶级方法np.sort返回的是数组的已排序副本，而就地排序则会修改数组本身。计算数组分位数最简单的办法是对其进行排序，然后选取特定位置的值：

# In[134]:


large_arr = np.random.randn(1000)
large_arr.sort()
large_arr[int(0.05 * len(large_arr))] # 5% quantile


# **3.5 唯一化以及其它的集合逻辑**
# 
# NumPy提供了一些针对一维ndarray的基本集合运算。最常用的可能要数np.unique了，它用于找出数组中的唯一值并返回已排序的结果：

# In[135]:


names = np.array(['Bob', 'Joe', 'Will', 'Bob', 'Will', 'Joe', 'Joe'])
np.unique(names)


# In[136]:


ints = np.array([3, 3, 3, 2, 2, 1, 1, 4, 4])
np.unique(ints)


# 拿跟np.unique等价的纯Python代码来对比一下：

# In[137]:


sorted(set(names))


# 另一个函数np.in1d用于测试一个数组中的值在另一个数组中的成员资格，返回一个布尔型数组：

# In[138]:


values = np.array([6, 0, 0, 3, 2, 5, 6])
np.in1d(values, [2, 3, 6])


# NumPy中的集合函数请参见表。
# ![](img/7178691-80e85ae6b9c89ada.png)
# 
# **4 用于数组的文件输入输出**
# 
# NumPy能够读写磁盘上的文本数据或二进制数据。这一小节只讨论NumPy的内置二进制格式，因为更多的用户会使用pandas或其它工具加载文本或表格数据（见第6章）。
# 
# np.save和np.load是读写磁盘数组数据的两个主要函数。默认情况下，数组是以未压缩的原始二进制格式保存在扩展名为.npy的文件中的：

# In[139]:


arr = np.arange(10)
np.save('some_array', arr)


# 如果文件路径末尾没有扩展名.npy，则该扩展名会被自动加上。然后就可以通过np.load读取磁盘上的数组：

# In[140]:


np.load('some_array.npy')


# 通过np.savez可以将多个数组保存到一个未压缩文件中，将数组以关键字参数的形式传入即可：

# In[141]:


np.savez('array_archive.npz', a=arr, b=arr)


# 加载.npz文件时，你会得到一个类似字典的对象，该对象会对各个数组进行延迟加载：

# In[142]:


arch = np.load('array_archive.npz')
arch['b']


# 如果要将数据压缩，可以使用`numpy.savez_compressed`：

# In[143]:


np.savez_compressed('arrays_compressed.npz', a=arr, b=arr)


# **5 线性代数**
# 
# 线性代数（如矩阵乘法、矩阵分解、行列式以及其他方阵数学等）是任何数组库的重要组成部分。不像某些语言（如MATLAB），通过对两个二维数组相乘得到的是一个元素级的积，而不是一个矩阵点积。因此，NumPy提供了一个用于矩阵乘法的dot函数（既是一个数组方法也是numpy命名空间中的一个函数）：

# In[144]:


x = np.array([[1., 2., 3.], [4., 5., 6.]])
y = np.array([[6., 23.], [-1, 7], [8, 9]])


# In[145]:


x


# In[146]:


y


# In[147]:


x.dot(y)


# x.dot(y)等价于np.dot(x, y)：

# In[148]:


np.dot(x, y)


# 一个二维数组跟一个大小合适的一维数组的矩阵点积运算之后将会得到一个一维数组：

# In[149]:


np.dot(x, np.ones(3))


# @符（类似Python 3.5）也可以用作中缀运算符，进行矩阵乘法：

# In[150]:


x @ np.ones(3)


# numpy.linalg中有一组标准的矩阵分解运算以及诸如求逆和行列式之类的东西。它们跟MATLAB和R等语言所使用的是相同的行业标准线性代数库，如BLAS、LAPACK、Intel MKL（Math Kernel Library，可能有，取决于你的NumPy版本）等：

# In[152]:


from numpy.linalg import inv, qr
X = np.random.randn(5, 5)
mat = X.T.dot(X)
inv(mat)


# In[153]:


mat.dot(inv(mat))


# In[154]:


q, r = qr(mat)
r


# 表达式X.T.dot(X)计算X和它的转置X.T的点积。
# 
# 表中列出了一些最常用的线性代数函数。
# 
# ![](img/7178691-dcdb66e49e5f70ea.png)
# 
# **6 伪随机数生成**
# 
# numpy.random模块对Python内置的random进行了补充，增加了一些用于高效生成多种概率分布的样本值的函数。例如，你可以用normal来得到一个标准正态分布的4×4样本数组：

# In[155]:


samples = np.random.normal(size=(4, 4))
samples


# 而Python内置的random模块则只能一次生成一个样本值。从下面的测试结果中可以看出，如果需要产生大量样本值，numpy.random快了不止一个数量级：

# In[156]:


from random import normalvariate
N = 1000000
get_ipython().run_line_magic('timeit', 'samples = [normalvariate(0, 1) for _ in range(N)]')


# In[157]:


get_ipython().run_line_magic('timeit', 'np.random.normal(size=N)')


# 
# 我们说这些都是伪随机数，是因为它们都是通过算法基于随机数生成器种子，在确定性的条件下生成的。你可以用NumPy的np.random.seed更改随机数生成种子：

# In[158]:


np.random.seed(1234)


# numpy.random的数据生成函数使用了全局的随机种子。要避免全局状态，你可以使用numpy.random.RandomState，创建一个与其它隔离的随机数生成器：

# In[160]:


rng = np.random.RandomState(1234)
rng.randn(10)


# 表列出了numpy.random中的部分函数。在下一节中，我将给出一些利用这些函数一次性生成大量样本值的范例。
# 
# ![](img/7178691-97ba09c96dab93a2.png)
# 
# ![](img/7178691-6ed04fae3d1178e2.png)
# 
# **7 示例：随机漫步**
# 
# 我们通过模拟随机漫步来说明如何运用数组运算。先来看一个简单的随机漫步的例子：从0开始，步长1和－1出现的概率相等。
# 
# 下面是一个通过内置的random模块以纯Python的方式实现1000步的随机漫步：

# In[161]:


import random
position = 0
walk = [position]
steps = 1000
for i in range(steps):
    step = 1 if random.randint(0, 1) else -1
    position += step
    walk.append(position)


# 下图是根据前100个随机漫步值生成的折线图：

# In[162]:


plt.plot(walk[:100])


# 不难看出，这其实就是随机漫步中各步的累计和，可以用一个数组运算来实现。因此，我用np.random模块一次性随机产生1000个“掷硬币”结果（即两个数中任选一个），将其分别设置为1或－1，然后计算累计和：

# In[163]:


nsteps = 1000
draws = np.random.randint(0, 2, size=nsteps)
steps = np.where(draws > 0, 1, -1)
walk = steps.cumsum()


# 有了这些数据之后，我们就可以沿着漫步路径做一些统计工作了，比如求取最大值和最小值：

# In[164]:


walk.min()


# In[165]:


walk.max()


# 现在来看一个复杂点的统计任务——首次穿越时间，即随机漫步过程中第一次到达某个特定值的时间。假设我们想要知道本次随机漫步需要多久才能距离初始0点至少10步远（任一方向均可）。np.abs(walk)>=10可以得到一个布尔型数组，它表示的是距离是否达到或超过10，而我们想要知道的是第一个10或－10的索引。可以用argmax来解决这个问题，它返回的是该布尔型数组第一个最大值的索引（True就是最大值）：

# In[166]:


(np.abs(walk) >= 10).argmax()


# 注意，这里使用argmax并不是很高效，因为它无论如何都会对数组进行完全扫描。在本例中，只要发现了一个True，那我们就知道它是个最大值了。
# 
# **7.1 一次模拟多个随机漫步**
# 
# 如果你希望模拟多个随机漫步过程（比如5000个），只需对上面的代码做一点点修改即可生成所有的随机漫步过程。只要给numpy.random的函数传入一个二元元组就可以产生一个二维数组，然后我们就可以一次性计算5000个随机漫步过程（一行一个）的累计和了：

# In[167]:


nwalks = 5000
nsteps = 1000
draws = np.random.randint(0, 2, size=(nwalks, nsteps))
steps = np.where(draws > 0, 1, -1)
walks = steps.cumsum(1)
walks


# 现在，我们来计算所有随机漫步过程的最大值和最小值：

# In[168]:


walks.max()


# In[169]:


walks.min()


# 得到这些数据之后，我们来计算30或－30的最小穿越时间。这里稍微复杂些，因为不是5000个过程都到达了30。我们可以用any方法来对此进行检查：

# In[171]:


hits30 = (np.abs(walks) >= 30).any(1)
hits30


# In[172]:


hits30.sum() # Number that hit 30 or -30


# 然后我们利用这个布尔型数组选出那些穿越了30（绝对值）的随机漫步（行），并调用argmax在轴1上获取穿越时间：

# In[173]:


crossing_times = (np.abs(walks[hits30]) >= 30).argmax(1)
crossing_times.mean()


# 请尝试用其他分布方式得到漫步数据。只需使用不同的随机数生成函数即可，如normal用于生成指定均值和标准差的正态分布数据：

# In[174]:


steps = np.random.normal(loc=0, scale=0.25,size=(nwalks, nsteps))

