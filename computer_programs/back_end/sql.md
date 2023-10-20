# SQL

#### 2023/10/19

## 初级要点

- SQL的书写顺序和执行顺序。先梳理取数逻辑，在转为SQL语句。能跑出数据，不一定SQL就是对的。
- 基础语法：select，where，join，group by，order by，having，limit；聚合函数：sum，avg，count
- 进阶写法：嵌套查询，子查询，left，right关联查询
- 高级写法：复杂日期，类型转换，行转列，列转行，正则匹配，json的处理；
- 有基础以后，理解“关系运算”，理解笛卡尔积
- 了解事务，锁，索引，约束，视图，元数据

## 书写顺序和执行顺序

```
【8】select 【9】distinct <select_list>
【1】from <left_table> 【3】<join_type> join <right_table>
【2】on<join_condition>
【4】where<where_condition>
【5】group by<group_by_list>
【6】with {CUBE|ROLLUP}
【7】having<having_condition>
【10】order by<order_by_list>
【11】limit<limit_number>

```

简单来说，书写顺序：`select -> from -> where -> group by ->having -> order by`
执行顺序：`from -> where -> group by -> having -> select -> order by`

最显著的区别是select的执行位置，书写在前面，而实际执行在后面。可以这么理解，先检索数据，然后设置查看规则。从角度来看，先找到空间中的各组向量，然后对向量进行投影。

为了提高效率，需要注意：
- from 后面的关联表，解析如果是自右向左，则最后的表是驱动表，尽量将数据量小的表放到后面进行关联，用小表去匹配大表；
- where子语句同from；
- 尽量少使用having语句，很耗资源；

### 内部执行流程

所有查询语句，都是从from开始执行，在执行过程中，上一步为下一步生成一个虚拟表，作为下一个步骤输入。

from的表小于2

1. from子句的表执行笛卡尔积，生成虚拟表virtual table 1【以小的表作为基础表】
2. 应用on条件筛选器，将on条件用到virtual table 1各行，生成虚拟表 virtual table 2
3. 跟进连接方式，进一步操作，如果是 outer join，则添加外部行

注意：left outer join，会把左表中筛选的行添加进来；right outer join将右表中筛选的行添加进来；

如果from的表大于2， 则重复执行上面步骤，得到一个virtual table 3

1. 用where筛选器，对virtual table 3 筛选，生成 virtual table 4。注意，需要用condition去筛选数据，放在on还是where呢？二者区别为：on移除的行，可以在join中添加回来，而where移除不可以
2. group by 子句将相同属性的row合并，得到virtual table 5。后面所有步骤，只能得到virtual table 5中列或者聚合函数
3. 使用 CUBE 或者 ROLLUP选项，生成 virtual table 6
4. having筛选器，生成 virtual table 7
5. 处理select子句，生成 virtual table 8
6. 使用distinct，移除 virtual table 8 重复行，生成 virtual table 9。如果使用group by，则已经列中唯一值分组，无需使用distinct
7. 使用order by子句，返回一个游标，不是虚拟表，所以order by不能应用于表达式。【SQL是基于集合，而集合不需要预先排序。对表排序，可以返回一个对象，对象包含了特定的顺序，即游标】

## group by

工作原理【ClickHouse】：

- group by 子句包含表达式列表，这份列表充当 grouping key，而每个单独的表达式被称为键表达式“key expressions”
- 在所有表达式在select， having和order by子句中，必须基于键表达式进行计算，或者在聚合函数在非键表达式（包含单纯列）。也就是，从表中选择的每个列，必须用于键表达式或者聚合函数内，但不能同时使用；
- 聚合结果select查询将包含尽可能多的行，因为有唯一值“grouping key”在源表中。



【MySQL】分组统计的用途。用于结合合计的函数，根据一个或多个列对结果集进行分组。合计函数（如sum）常常需要添加group by语句。

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

### order by

用于根据指定的列对结果进行排序。默认按照升序排序，降序加desc关键字。

例子【查询前10个】：`select name,age,city from staff where city='xxx' order by age limit 10;`

### count

`count(*)`返回表中记录数。`count(column_name)`返回指定列值的数目。

例子【计算比例】：`select (select count(*) from table_name where timestamp<=11111111 )/(select count(*) from table_name);`

### having

where关键字无法和聚合函数一起使用，新增having子句。

例子：`select customer, sum(price) from table_name group by customer having sum(price)<2000;`

## 子查询

在一个select语句中，嵌入另一个select语句，被嵌入语句称之为子查询语句，相应的外部select语句为主查询。由于order by生成的不是临时表，而是游标，故order by不能用在子查询中。

子查询有4种情况：

1. 标量子查询：子查询返回一个数据。可以看着特殊的一行一列，只有一个元素的矩阵；
2. 列子查询：返回一列多行；
3. 行子查询：返回一行多列；
4. 表子查询：返回多行多列，即一个临时表；

举例：
1. 标量子查询【年龄大于班级平均年龄】：`select * from student where age > (select avg(age) from student);`
2. 列子查询【查看学生班级信息，注：班级是另一个表】：`select * from student where class_id in (select id from classes);`
3. 行子查询【查看学生年龄最大，身高最高的学生】：`select * from student where (age, height)=(select max(age),max(height) from students);`
4. 表子查询【查找学号小于6的男同学】：`select * from student where (select * from student where id<6) as a where a.gender=1;`

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

- [神奇的 SQL 之 联表细节 → MySQL JOIN 的执行过程（一）](https://www.cnblogs.com/youzhibing/p/12004986.html)
- 《SQL 必知必会》
- [w3school SQL 教程](https://www.w3school.com.cn/sql/index.asp)
- [SQL 练习【可在线执行】](https://sqlzoo.net/wiki/SELECT_basics)
- [看一遍就理解：group by 详解 ](https://juejin.cn/post/7053966777088213005)
- [ClickHouse 在有赞的实践之路](https://tech.youzan.com/clickhouse-zai-you-zan-de-shi-jian-zhi-lu/)
               
