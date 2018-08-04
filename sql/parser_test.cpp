#include<string.h>
#include<stdio.h>
#include"sql_node.h"
#include"y.tab.h"




int main(){
    sql_parser("select A B from C");
    return 0;
}

