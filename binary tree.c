#include<stdio.h>
#include<stdlib.h>
struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};
int search(struct btreenode **str,struct btreenode**loc,struct btreenode**par,int item )
{
    struct btreenode *ptr ,*save;
    ptr=*str;
    if(*str==NULL)
    {
        (*loc)=NULL;
        (*par)=NULL;
      return 0;
    }
    if((*str)->data==item)
    {
        (*loc)=ptr;
        (*par)=NULL;
        return 0;
    }
    if((ptr->data)>item)
    {
        ptr=(ptr->leftchild);
    }
    else
        {ptr=ptr->rightchild;}
    save=*str;
    while(ptr!=NULL)
    {if(ptr->data==item)
       {
           (*loc)=ptr;
           (*par)=save;
           return 0;
       }
        save=ptr;
      if(ptr->data>item)
      {
          ptr=ptr->leftchild;
      }
      else
        {ptr=ptr->rightchild;
        }
    }
    (*loc)=NULL;
    (*par)=save;
}
int insert(struct btreenode **sr,int num)
{   struct btreenode *loc,*par;
    loc=*sr;
    if(*sr==NULL)
   {loc=(struct btreenode*)malloc(sizeof(struct btreenode));
    loc->leftchild=NULL;
    loc->data=num;
    loc->rightchild=NULL;
    *sr=loc;
   }
   else
   { while(loc!=NULL)
       {if(num<loc->data)
          {par=loc;
          loc=loc->leftchild;
          }
        else
        {
            par=loc;
            loc=loc->rightchild;
        }
        }
        loc=(struct btreenode*)malloc(sizeof(struct btreenode));
        loc->leftchild=loc->rightchild=NULL;

            if(num<(par->data))
            {
             loc->data=num;
             par->leftchild=loc;
            }
            else
            {loc->data=num;
            par->rightchild=loc;
            }
        }
return 0;
}

int inorder(struct btreenode *sr)
{ struct btreenode *q;
q=sr;
    //printf("hi i am using");
    if(q!=NULL)
    {//printf("hello i am also using");
        inorder(q->leftchild);
        printf("%d  ",q->data);
        inorder(q->rightchild);
    }
    else
    {
        return 0;
    }
}

int casea(struct btreenode **loc1,struct btreenode **par1)
{struct btreenode *ptr,*subptr;
ptr=(*loc1)->rightchild;
while(ptr->leftchild!=NULL)
{
    subptr=ptr;
    ptr=ptr->leftchild;
}
subptr->leftchild=NULL;
ptr->leftchild=(*loc1)->leftchild;
ptr->rightchild=(*loc1)->rightchild;
(*loc1)->leftchild=(*loc1)->rightchild=NULL;
if((*par1)!=NULL)
{
    if((*loc1)->data<(*par1)->data)
{
    (*par1)->leftchild=ptr;
}
else
{
    (*par1)->rightchild=ptr;
}
}
}
int caseb(struct btreenode **loc1,struct btreenode **par1)
{
    if((*loc1)->leftchild==NULL)
    {if((*loc1)->rightchild==NULL)
    {  if(((*par1)->data)>(*loc1)->data)
          {
              (*par1)->leftchild=NULL;
          }
        else
        {
            (*par1)->rightchild=NULL;
        }
    }
    else
      {
          if((*par1)->data>(*loc1)->data)
          {
              (*par1)->leftchild=(*loc1)->rightchild;
              (*loc1)->rightchild=NULL;
          }
        else
        {
            (*par1)->rightchild=(*loc1)->rightchild;
             (*loc1)->rightchild=NULL;
        }

      }

    }
    else
    {
        if((*loc1)->leftchild==NULL)
    {  if((*par1)->data>(*loc1)->data)
          {
              (*par1)->leftchild=NULL;
          }
        else
        {
            (*par1)->rightchild=NULL;
        }
    }
    else
      {
          if((*par1)->data>(*loc1)->data)
          {
              (*par1)->leftchild=(*loc1)->leftchild;
               (*loc1)->leftchild=NULL;
          }
        else
        {
            (*par1)->rightchild=(*loc1)->leftchild;
             (*loc1)->leftchild=NULL;
        }

      }

    }
free((*loc1));
}
int delete(struct btreenode **del, int item)
{struct btreenode *loc,*par;
loc=par=NULL;
search(del,&loc,&par,item);
    if(loc==NULL)
    {
        printf("\n item not found in the tree");
        return 0;
    }
    else
    {
        if(loc->leftchild!=NULL&&(loc->rightchild)!=NULL)
        {
            casea(&loc,&par);
        }
        else
        {
            caseb(&loc,&par);
        }
    }
}
int main()
{
    struct btreenode *bt,*loc,*par;
    int req, i=1, num,item;

    loc=par=bt=NULL;  //empty binary tree
    printf("specify the nmber of data to be inserted:");
    scanf("%d",&req);
    while(i++<=req)
    {
        printf("enter the data:");
        scanf("%d",&num);
        insert(&bt,num);
    }
    printf("inorder traversal:\n");
    inorder(bt);
    printf("enter the elelment that you wnt to search :");
    scanf("%d",&item);
    search(&bt,&loc,&par,item);
    if(loc==NULL)
       {printf("\n not found");

       }
    else
        {printf("\nfound");
        printf("\n the parent node is %d",(par->data));}
    printf("\nenter the element that you want to delete :");
    scanf("%d",&item);
    delete(&bt,item);
    printf("\ntree after deletion :\n");
    inorder(bt);
return 0;
}

