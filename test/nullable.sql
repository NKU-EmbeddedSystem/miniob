drop table t;
create table t(id int, num int nullable, birthday date nullable);
create index i_num on t(num);
insert into t values(1, 2, '2020-01-01');
insert into t values(1, null, null);
insert into t values(1, null, '2020-02-02');
insert into t values(null, 1, '2020-01-02');
select * from t;

select * from t where id is null;
select * from t where id is not null;
select * from t where num is null; 
select * from t where num > null;
select * from t where num <> null;
select * from t where 1=null;
select * from t where 'a'=null;
select * from t where null = null;
select * from t where null is null;
select * from t where '2020-01-31' is null;

