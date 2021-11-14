drop table T_ORDER_BY;
create table T_ORDER_BY(id int, score int, name char);
insert into T_ORDER_BY values(3, 1, "A"), (1, 2, "B"), (3, 2, "C"), (4, 3, "C"), (3, 4, "C"), (3, 3, "D");
select * from T_ORDER_BY order by id desc, score asc, name desc;
