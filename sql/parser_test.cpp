#include<string.h>
#include<stdio.h>
#include"sql_node.h"
#include"y.tab.h"
#include<queue>
#include<cmath>


struct node{
    node(node*l,node*r,int){
        left=l;
        right=r;
        this->val=x++;
    };
    static char x;
    node*left;
    node*right;
    char val;
};
char node::x=32;
static int i=0;
node*build_node(node *p,int d){
    //printf("build %d\n",d);
    if(d==0)
        return p;
    
    p->left=new node(NULL,NULL,rand()%100);
    p->right=new node(NULL,NULL,rand()%100);

  

    build_node(p->left,d-1);
    build_node(p->right,d-1);
    return p;
};

int max_depth(node *r){
    if (!r)
        return 0;
    else
        return 1+std::max(max_depth(r->left),max_depth(r->right));
};



/*
       O 
   x       c     
 a   d   f   g
q w e r t y u i
*/

std::vector<node*> level;

 

void print_level(int d){
    
    
    printf("\n");
    for(int i=0;i<std::pow(2,d);i++){
        printf(" ");
    }
    std::vector<node*> l2;
    for(int i=0;i<level.size();i++){
        printf("%c",level[i]->val);
        int space=-1+std::pow(2,d+1);
        for(int j=0;j<space;j++)
        printf(" ");
        if(d>0){
            l2.push_back(level[i]->left);
            l2.push_back(level[i]->right);
        }
    }

    if(d>0){
        level=l2;
        print_level(d-1);
    }
    
};

void tree_test(){
    node *root=new node(NULL,NULL,100);
    build_node(root,5);
    level.push_back(root);
    print_level(max_depth(root));
    printf("\n");
};

int main(){
    setbuf(stdout,NULL);
    const char*sql_create="create table student (ID int,name varchar(10))";
    const char*sql_select="select ID,name from student where student.ID = 10 and student.name=11 and student.name=2.5";
    const char*sql_insert1="insert into student values(10001,\"gaojingyu\")";
    const char*sql_insert2="insert into student (ID,name) values(10001,\"gaojingyu\")";
    const char*sql_update="update student set name=\"xiaoming\" where ID=10002"; 
    const char*sql_delete="delete from student where name=\"xiaomin\"";
    //tree_test();
    sql_parser(sql_delete);
    return 0;
}
