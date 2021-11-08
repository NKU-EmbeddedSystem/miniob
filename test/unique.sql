drop table t1;
create table t1(id int, age int, value int);
create index tid on t1(id);
create unique index tage on t1(age);
insert into t1 values(1, 2, 3);
drop table t1;
