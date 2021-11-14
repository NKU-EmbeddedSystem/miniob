drop table agg_test;
create table agg_test(id int, iv int, sv char, dv date, fv float);
insert into agg_test values(1, 1, "FNC", "2011-11-1", 3.0);
insert into agg_test values(2, 2, "TPA", "2012-11-1", 3.0);
insert into agg_test values(3, 3, "SKT", "2013-11-1", 3.0);
insert into agg_test values(4, 4, "SSW", "2014-11-1", 3.1);
drop table agg_test2;
create table agg_test2(id int, iv int, sv char, dv date, fv float);
insert into agg_test2 values(5, 5, "SKT", "2015-11-1", 3.1);
insert into agg_test2 values(6, 6, "SKT", "2016-11-1", 3.2);
insert into agg_test2 values(7, 7, "SSG", "2017-11-1", 3.0);
insert into agg_test2 values(8, 8, "IG", "2018-11-1", 3.0);
select * from agg_test, agg_test2;
select * from agg_test, agg_test2 where agg_test2.fv > agg_test.fv;
select max(agg_test.iv), max(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), max(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), min(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), min(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), count(*) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), count(10) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), avg(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), avg(agg_test2.fv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select max(agg_test.iv), avg(2) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), max(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), max(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), min(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), min(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), count(*) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), count(10) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), avg(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), avg(agg_test2.fv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(*), avg(2) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), max(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), max(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), min(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), min(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), count(*) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), count(10) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), avg(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), avg(agg_test2.fv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select count(10), avg(2) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), max(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), max(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), min(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), min(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), count(*) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), count(10) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), avg(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), avg(agg_test2.fv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(agg_test.iv), avg(2) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), max(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), max(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), min(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), min(agg_test2.sv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), count(*) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), count(10) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), avg(agg_test2.iv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), avg(agg_test2.fv) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;
select avg(2), avg(2) from agg_test, agg_test2 where agg_test2.fv > agg_test.fv group by agg_test.sv, agg_test2.sv;