# SQL

#### 2023/10/19

## 初级要点

- SQL的书写顺序和执行顺序。先梳理取数逻辑，在转为SQL语句。能跑出数据，不一定SQL就是对的。
- 基础语法：select，where，join，group by，order by，having，limit；聚合函数：sum，avg，count
- 进阶写法：嵌套查询，子查询，left，right关联查询
- 高级写法：复杂日期，类型转换，行转列，列转行，正则匹配，json的处理；
- 有基础以后，理解“关系运算”，理解笛卡尔积
- 了解事务，锁，索引，约束，视图，元数据

## 基础语句

### group by

分组统计的用途。用于结合合计的函数，根据一个或多个列对结果集进行分组。合计函数（如sum）常常需要添加group by语句。

- 如果没有使用聚合函数，使用group by呢？在mysql中，返回的是第一行数据。
- group by中的字段，不一定要出现在select中；

例子：

`select city,  count(*) as num from staff where age>19 group by city having num >= 3;`

注意：group by既用到了临时表，又默认用到了排序，甚至有时候用到磁盘临时表，使用不当，容易导致慢sql。

执行顺序：
1. 执行where子句，查找符合年龄大于19的数据；
2. group by子句，对员工数据，根据城市分组；
3. 对group by形成的城市组，运行聚合函数，计算每一组的员工数量；
4. 最后用having子句选出员工数量大于等于3的城市组；

### where和having

- having用于分组以后的筛选，where子句用于行条件筛选；
- having一般配合group by，和聚合函数一起出现如：count，sum，avg，max，min等
- where条件子句，不能使用聚合函数，而having子句可以

### 优化 group by语句

#### group by依赖的字段加索引

如果字段一开始就有序，就需要建立临时表记录并统计结果。加索引就可以达到这个目的。

`alter table stall add index idx_age_city(age, city);`

加联合索引`idx_age_city(age, city)`

#### order by null 不用排序

有些场景不适合加索引，如果需求并不需要对结果集排序，就可以去掉排序。

`select city, count(*) as num from staff group by city order by null;`

## 基础概念

### 笛卡尔积

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

## Relational Data Model

### Relational

- 每行为N个元素的Tuple
- 行序无关紧要
- 所有的行应该去重（注意这是关系表）
- Column顺序很重要，对Column命名以便凸显相关的业务意义

要点：
- 实体表都有主键，每个主键的数据，代表不同实体
- 实体之间的关系，用一张新的表来描述

### Relational algebra

by E.F.Codd

#### 传统的Set操作

##### Projection算子

类似SQL中的`SELECT name, price`中选择字段的部分，取原始Relation中的元素，重组为新的Relation

数学基础：
- 每N-ary Record 类比N维Vector
- 选择部分字段，相当于N维Vector建立在更低维度空间的投影（Projection）
- Projection操作，实际相当于降维过程，舍弃部分与当前逻辑相关性不大的Degree

#### 其他操作

- Union
- intersection
- different

#### Join算子

Codd定义的Join，类似与SQL中的`CROSS JOIN`，源于集合论中的笛卡尔积（ Cartesian product）

| 左集合不变(补充缺失属性) | 右集合不变(补充缺少属性) | 关注交集(满足多种条件) | 关注合集(查漏补缺) | Join类型 |
| ------------------------ | ------------------------ | ---------------------- | ------------------ | ---------- |
| Y                        | N                        | N                      | N                  | left join  |
| N                        | Y                        | N                      | N                  | right join |
| N                        | N                        | Y                      | N                  | inner join |
| N                        | N                        | N                      | Y                  | outer join |

#### Restriction算子

一个Relation的子集还是一个Relation。Restriction描述操作：对R中的数据进行筛选，筛选的依据是管理另一个Relation S。类似SQL中的`Inner Join`。这种筛选数据集的思想，是后面`Where`子句的理论来源。

## 阅读资料

- 《SQL 必知必会》
- [w3school SQL 教程](https://www.w3school.com.cn/sql/index.asp)
- [SQL 练习【可在线执行】](https://sqlzoo.net/wiki/SELECT_basics)
- [ClickHouse 在有赞的实践之路](https://tech.youzan.com/clickhouse-zai-you-zan-de-shi-jian-zhi-lu/)
               
