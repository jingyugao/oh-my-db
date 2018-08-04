#include<string.h>
#include<stdio.h>
#include"sql_node.h"
#include"y.tab.h"




int main(){
    const char*sql_create="create table student (ID int,name varchar(10))";
    const char*sql_select="select ID,name from student where student.ID = 10 and student.name=11";
    const char*sql_insert1="insert into student values(10001,\"gaojingyu\")";
    const char*sql_insert2="insert into student (ID,name) values(10001,\"gaojingyu\")";

    sql_parser(sql_select);
    return 0;
}
