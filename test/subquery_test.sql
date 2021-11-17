drop table t1;
drop table t2;
drop table t3;
drop table t4;
drop table t5;
drop table t6;
create table t1(id int, num1 int);
create table t2(id int, num2 int);
create table t3(id int, num3 int);
create table t4(id int, num4 int);
create table t5(id int, num5 int);
create table t6(id int, num6 int);
-- these should pass
select * from t1 where num1 in (select num2 from t2);
select * from t1 where num1 not in (select num2 from t2);
select * from t1 where id > (select count(*) from t2);
select * from t1 where id > (select max(num2) from t2);
--
select * from t1 where id > (select max(id) from t2);
select * from t1 where id > (select max(t2.id) from t2);
select * from t1 where id in (select id from t2);
select * from t1 where id in (select t2.id from t2);
select * from t1 where id not in (select id from t2);
select * from t1 where id not in (select t2.id from t2);
--
select * from t1 where id > (select max(id) from t2 where id = t1.id);
select * from t1 where id > (select max(t2.id) from t2, t3 where t1.id = t2.id and t1.id = t3.id);
select * from t1 where id in (select id from t2 where id = t1.id);
select * from t1 where id in (select t2.id from t2, t3 where t1.id = t2.id and t1.id = t3.id);
select * from t1 where id not in (select id from t2 where id = t1.id);
select * from t1 where id not in (select t2.id from t2, t3 where t1.id = t2.id and t1.id = t3.id);
--
select * from t1 where id > (select count(*) from t2 where id = t1.id and id > (select avg(id) from t3 where id = t1.id and id = t2.id));
select * from t1 where id > (select count(t2.id) from t2, t3 where t1.id = t2.id and t1.id = t3.id and t2.id > (select min(t4.id) from t4, t5 where t4.id = t1.id and t4.id = t2.id and t4.id = t3.id and t4.id = t5.id));
select * from t1 where id in (select id from t2 where id = t1.id and id in (select id from t3 where id = t1.id and id = t2.id));
select * from t1 where id in (select t2.id from t2, t3 where t1.id = t2.id and t1.id = t3.id and t2.id not in (select t4.id from t4, t5 where t4.id = t1.id and t4.id = t2.id and t4.id = t3.id and t4.id = t5.id));
select * from t1 where id not in (select id from t2 where id = t1.id and id in (select id from t3 where id = t1.id and id = t2.id));
select * from t1 where id not in (select t2.id from t2, t3 where t1.id = t2.id and t1.id = t3.id and t2.id not in (select t4.id from t4, t5 where t4.id = t1.id and t4.id = t2.id and t4.id = t3.id and t4.id = t5.id));
-- these should failed
select * from t1 where (select max(num2) from t2) < (select max(num2) from t2);
--
select * from t1 where (select num2 from t2) in (select max(num2) from t2);
select * from t1 where (select num2 from t2) not in (select max(num2) from t2);
select * from t1 where (select num2 from t2) in num1;
select * from t1 where (select num2 from t2) not in num1;
--
select * from t1 where id > (select * from t2);
select * from t1 where id > (select num2 from t2);
--
select * from t1 where id in (select count(*) from t7);
select * from t1 where id > (select num7 from t7);
--
select * from t1 where id > (select max(t1.id) from t2);
select * from t1 where t1.id > (select max(id) from t2) and t1.id = t2.id;
select * from t1 where id in (select t1.id from t2);
select * from t1 where t1.id in (select id from t2) and t1.id = t2.id;
select * from t1 where id not in (select t1.id from t2);
select * from t1 where t1.id not in (select id from t2) and t1.id = t2.id;
--
select * from t1 where id > (select max(id) from t2, t3 where t1.id = id and t1.id = t3.id);
select * from t1 where id in (select id from t2, t3 where t1.id = id and t1.id = t3.id);
select * from t1 where id not in (select id from t2, t3 where t1.id = id and t1.id = t3.id);
-- select * from t2 where id in (select * from t1 inner join t2 on t1.id = t2.id inner join t3 on t1.id = t3.id inner join t4 on t3.id=t4.id inner join t5 on 1=1 inner join t6 on t5.id=t6.id where t3.num3 < 10 and t5.num5 > 90 and t7 in (select max(what) from t1 inner join t2 on t1.id = t2.id inner join t3 on t1.id = t3.id inner join t4 on t3.id=t4.id inner join t5 on 1=1 inner join t6 on t5.id=t6.id where t3.num3 < 10 and t5.num5 > 90));
-- select * from t2 where id in (select * from t1 inner join t2 on t1.id = t2.id where t5.num5 > 90 and t7 in (select max(what) from t1 inner join t2 on t1.id = t2.id where t5.num5 > 90));
-- select * from t2 where id in (select * from t1 inner join t2 on t1.id = t2.id inner join t3 on t1.id = t3.id inner join t4 on t3.id=t4.id inner join t5 on 1=1 inner join t6 on t5.id=t6.id where t3.num3 < 10 and t5.num5 > 90);
