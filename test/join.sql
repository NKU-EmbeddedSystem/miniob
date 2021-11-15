# select t1.age, t2.name, t1.id from t1 inner join t2 on t1.id = t2.id;
select * from t1 inner join t2 on t1.id = t2.id inner join t3 on t1.id = t3.id inner join t4 on t3.id=t4.id inner join t5 on 1=1 inner join t6 on t5.id=t6.id where t3.num3 < 10 and t5.num5 > 90;
