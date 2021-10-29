DROP TABLE person;
CREATE TABLE person (number INT, name CHAR,region CHAR,birthday DATE);
create index dtx on person(birthday);
INSERT INTO person VALUES(1,"tom","nor","2019-10-27");
INSERT INTO person VALUES(2,"bob","wes","2018-10-27");
INSERT INTO person VALUES(3,"jay","nor","2018-10-25");
INSERT INTO person VALUES(4,"jer","nor","2018-10-23");
SELECT * FROM person;
UPDATE person SET birthday='2019-11-06' WHERE name='tom';
select * from person;
DELETE from person where birthday = '2018-10-27';
select * from person;
-- this should fail(not lunar year)
INSERT INTO person values(5, "jal", "nor", "2021-02-29");
select * from person;
select * from person where birthday > '2018-10-24';
select * from person where birthday > '2019-01-01';
select * from person where birthday < '2019-01-01';
