#### Java注解(Annotation)

```java
public @interface ABC {
    ...
}
```

---

##### 常见注解

- @Override

覆盖父类的方法

- @Deprecated

过时的方法，不推荐，但可以使用，因为该方法可能存在更好的替代品

- @SuppressWarnings

过滤警告的，有参数，常见参数，**参数必写**

---

##### 元注解

**可以写在注解上的注解**

元标签有 @Retention、@Documented、@Target、@Inherited、@Repeatable 5 种

- @Retention

生命什么时期有效，**Source < Class < Runtime**

**例如**：

```java
@Retention(RetentionPolicy.RUNTIME)
public @interface Test {
    ...
}
```



- @Target

声明作用域

