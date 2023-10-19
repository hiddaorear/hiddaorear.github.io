# SQL

#### 2023/10/19

## 初级要点

- SQL的书写顺序和执行顺序。先梳理取数逻辑，在转为SQL语句。能跑出数据，不一定SQL就是对的。
- 基础语法：select，where，join，group by，order by，having，limit；聚合函数：sum，avg，count
- 进阶写法：嵌套查询，子查询，left，right关联查询
- 高级写法：复杂日期，类型转换，行转列，列转行，正则匹配，json的处理；
- 有基础以后，理解“关系运算”，理解笛卡尔积
- 了解事务，锁，索引，约束，视图，元数据

## 笛卡尔积

笛卡尔积指参与连接的两个表使用逗号，或者join关键词连接，连接条件放在where中。
慎用笛卡尔积的原因：其计算只产生一个reduce任务，等价于，两个表的连接key是一个常数，只有一个join key也就只会有一个reduce任务。这是一个极端数据倾斜的例子：`select * from a join b` = `select * from a join b on 1=1 `

例句：
- `select * from gbk, utf8 where gbk.key = utf8.key and gbk.key > 10;`
- `select * from gbk join utf8 where gbk.key = utf8.key and gbk.key > 10;`
规范形式：
- `select * from gbk join utf8 on gbk.key = utf8.key where gbk.key > 10;`

## 进阶

### SQL 守则

- 谨慎使用笛卡尔积
- 坚持先聚合后连接
- 小表连接大表


## 阅读资料

- 《SQL 必知必会》
- [w3school SQL 教程](https://www.w3school.com.cn/sql/index.asp)
- [SQL 练习【可在线执行】](https://sqlzoo.net/wiki/SELECT_basics)
- [ClickHouse 在有赞的实践之路](https://tech.youzan.com/clickhouse-zai-you-zan-de-shi-jian-zhi-lu/)
               
