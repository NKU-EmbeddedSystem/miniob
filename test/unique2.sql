drop table unique_table;
create table unique_table (what int, id int, age int);
create unique index index_id on unique_table(id);
insert into unique_table values (2, 1, 1);
create unique index index_id on unique_table(id);
insert into unique_table values (3, 2, 1);
insert into unique_table values (1, 2, 1);
