drop table multi_index3;
create table multi_index3(id int, col1 int, col2 float, col3 CHAR, col4 date, col5 int, col6 int);
insert into multi_index3 values(4, 2, 12.2, "E", "2022-01-04", 13, 10);
insert into multi_index3 values(5, 3, 14.2, "D", "2020-04-02", 12, 2);
insert into multi_index3 values(3, 1, 11.1, "A", "2021-04-21", 1, 1);
insert into multi_index3 values(3, 1, 12.2, "B", "2021-04-23", 1, 1);
insert into multi_index3 values(90, 13, 90.1, "C", "2022-05-03", 1, 1);
create index itx on multi_index3(id, col1);
