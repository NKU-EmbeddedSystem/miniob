drop table agg_test;
create table agg_test(id int, iv int, sv char, dv date, fv float);
select * from agg_test;
select max(iv) from agg_test;
select max(sv) from agg_test;
select max(dv) from agg_test;
select max(fv) from agg_test;
select min(iv) from agg_test;
select min(sv) from agg_test;
select min(dv) from agg_test;
select min(fv) from agg_test;
select count(*) from agg_test;
select count(10) from agg_test;
select avg(iv) from agg_test;
select avg(fv) from agg_test;
select avg(2) from agg_test;
select max(agg_test.iv) from agg_test;
select max(agg_test.sv) from agg_test;
select max(agg_test.dv) from agg_test;
select max(agg_test.fv) from agg_test;
select min(agg_test.iv) from agg_test;
select min(agg_test.sv) from agg_test;
select min(agg_test.dv) from agg_test;
select min(agg_test.fv) from agg_test;
select count(*) from agg_test;
select count(10) from agg_test;
select avg(agg_test.iv) from agg_test;
select avg(agg_test.fv) from agg_test;
select avg(2) from agg_test;
select max(iv) from agg_test;
select max(sv) from agg_test;
