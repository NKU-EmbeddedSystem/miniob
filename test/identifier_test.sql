drop table person;
create table person(id int, name char, birth date, weight float );
insert into person values(1, "A", "2019-10-1", 55.2);
insert into person values(2, "B", "2020-10-1", 53.1);
insert into person values(3, "C", "2021-10-1", 50.0);
insert into person values(4, "D", "2022-10-1", 57.2);
-- test select *
select * from person;
-- test select field without table name
select id, name from person;
-- test select field without table name
select person.id, person.name from person;
-- test select field with/without table name
select id, person.name from person;
-- test select field with/without table name
