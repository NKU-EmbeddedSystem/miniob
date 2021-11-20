drop table t;
create table t(id int, val text);
insert into t values(1, "a very long string1");
insert into t values(2, "a very long string2");
insert into t values(3, "a very long string2");
select * from t;
