create table t2(id int, num int nullable, birthday date nullable);
insert into t2 values(1, 2, '2020-01-01');
insert into t2 values(1, null, null);
insert into t2 values(1, null, '2020-02-02');
insert into t2 values(null, 1, '2020-01-02');
select * from t;

select * from t2 where id is null;
select * from t2 where id is not null;
select * from t2 where num is null; 
select * from t2 where num > null;
select * from t2 where num <> null;
select * from t2 where 1=null;
select * from t2 where 'a'=null;
select * from t2 where null = null;
select * from t2 where null is null;
select * from t2 where '2020-01-31' is null;

