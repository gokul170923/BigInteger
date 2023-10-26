#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"BigInteger.h"




//display
void revdisplay(struct node*head,int sign){
    if(head==NULL)return;
    revdisplay(head->next,sign);
    if(sign==-1&&head->next==NULL){
        printf("%d",-1*head->data);
    } 
    else{
        printf("%d",head->data);
    }
}

void display(struct BigInteger temp){
    revdisplay(temp.head,temp.sign);
    
    
}

//length
int length_of_ll(struct node *head){
    int len =0;
    while(head!=NULL){
        len++;
        head=head->next;
    }
    return len;
}

// second larger
int second_greater(struct node *head1,struct node *head2)
{
    while(head1!=NULL){
        if(head2->data>head1->data){
            return 1;
        }
        head1=head1->next;
        head2=head2->next;
    }
    return 0;
}

//newtemp
struct BigInteger newtemp(){
    struct BigInteger temp;
    temp.length = 0;
    temp.head=NULL;
    temp.sign=1;
    return temp;

}

//compare
int compare(struct BigInteger a, struct BigInteger b){
    if(a.length>b.length) return 0;
    if(b.length>a.length) return 1;
    int flag=-1;
    struct node*h1=a.head,*h2=b.head;
    while(h1!=NULL&&h2!=NULL){
        if(h1->data>h2->data) flag =0;
        if(h2->data>h1->data) flag =1;
        h1=h1->next;
        h2=h2->next;
    }
    return flag;
}


struct node*copy(struct node *head){
    struct node *newhead=NULL,*temp;
    while(head!=NULL){
        struct node*n=(struct node*)malloc(sizeof(struct node));
        n->data=head->data;
        n->next=NULL;
        if(newhead==NULL){
            newhead=n;
            temp=n;
        }else{
            temp->next=n;
            temp=n;
        }
       head=head->next; 
        
    }
    return newhead;
}


//insert at begin
void insert_at_begin(struct BigInteger *temp,int data){
    struct node*newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=temp->head;
    temp->head=newnode;

}

//0insert
struct node* insert0(struct node*head){
    struct node*n=(struct node*)malloc(sizeof(struct node));
    n->data=0;
    n->next=head;
    head=n;
    return head;
    
}

//truncate


struct node* reverse(struct node* head) {
    struct node * curr= head,*prev = NULL,*ahead;
    while(curr!=NULL){
        ahead = curr->next;
        curr->next = prev;
        prev= curr;
        curr =ahead;
    }
    return prev;
    

}

struct node*truncate(struct node*head){
    if(head->next==NULL)return head;
    head=reverse(head);
    struct node*temp;
    while(head->next!=NULL&&head->data==0){
        temp=head;
        head=head->next;
        free(temp);
    }
    head = reverse(head);
    return head;
    
}


//initailize
struct BigInteger initialize(char *s){
    struct BigInteger temp = newtemp();
    int i=0;
    int flag=0;
    while(s[i]!='\0'){
        if(s[i]=='-'){
            temp.sign=-1;
            i++;
            continue;
        }
        if(flag==0&&s[i]=='0'){
            i++;
            continue;
        }
        else if(s[i]!='0'){
            flag =1;
        }
        insert_at_begin(&temp,s[i]-'0');
        i++;
        temp.length++;
    }
    if(temp.head==NULL&&s[0]=='0'){
        insert_at_begin(&temp,0);
        temp.length++;
    }
    return temp;
}

//add of ll
struct node *addition_of_ll(struct node *head1,struct node *head2){
    struct node *head = NULL,*temp;
    int carry=0,sum;
    while(head1!=NULL||head2!=NULL||carry){
        sum = carry;
        if(head1!=NULL){
            sum+=head1->data;
            head1=head1->next;
        }
        if(head2!=NULL){
            sum +=head2->data;
            head2=head2->next;
        }
        carry = sum/10;
        sum = sum%10;
        
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data= sum;
        newnode->next = NULL;
        if(head==NULL){
            head = newnode;
            temp = newnode;
        }
        else{
            temp->next = newnode;
            temp = temp->next;
        }
    }
    return head;
    
}


//sub of ll
struct node *subtraction_of_ll(struct node *head1,struct node *head2){
 
    int borrow=0,diff;
    struct node *head=NULL,*temp;
    while(head1!=NULL){
        diff= head1->data-borrow;
        if(head2!=NULL){
            diff-=head2->data;
            head2=head2->next;
        }
        if(diff<0){
            borrow=1;
            diff+=10;
        }
        else{
            borrow=0;
        }
        struct node *newnode =(struct node *)malloc(sizeof(struct node));
        newnode->data= diff;
        newnode->next=NULL;
        if(head==NULL){
            head=newnode;
            temp=newnode;
        }
        else{
            temp->next=newnode;
            temp=newnode;
        }
        head1=head1->next;
    }
       
        return head;
    }



//*****************************************************************************************************

//add
struct BigInteger add(struct BigInteger a,struct BigInteger b){
    if(a.sign !=b.sign){
        if(compare(a,b)==-1){
        struct BigInteger t;
        struct node*h = (struct node*)malloc(sizeof(struct node));
        t.head=h;
        h->next=NULL;
        h->data=0;
        t.length=1;
        return t;
        }
        if(compare(a,b)==0){
            struct BigInteger res = subofadd(a,b);
            res.head= truncate(res.head);
            res.length=length_of_ll(res.head);
            if(a.sign==-1) res.sign=-1;
            else res.sign =1;
            return res;

        }
        if(compare(a,b)==1){
            struct BigInteger res = subofadd(b,a);
            res.head= truncate(res.head);
            res.length=length_of_ll(res.head);
            if(b.sign==-1) res.sign=-1;
            else res.sign =1;
            return res;
        }
        

    }
    
    struct BigInteger temp;
    struct node *h1=a.head,*h2=b.head;
    temp.head = NULL;
    struct node *t;
    int carry=0,sum;
    while(h1!=NULL||h2!=NULL||carry){
        sum = carry;
        if(h1!=NULL){
            sum+=h1->data;
            h1=h1->next;
        }
        if(h2!=NULL){
            sum +=h2->data;
            h2=h2->next;
        }
        carry = sum/10;
        sum = sum%10;
        
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data= sum;
        newnode->next = NULL;
        if(temp.head==NULL){
            temp.head = newnode;
            t = newnode;
        }
        else{
            t->next = newnode;
            t = t->next;
        }
    }
    if(a.sign==-1&&b.sign==-1){
        temp.sign=-1;
    }
    temp.length = length_of_ll(temp.head);
    return temp;

}


struct BigInteger subofadd(struct BigInteger a,struct BigInteger b){
    struct BigInteger temp=newtemp();
    int borrow=0,diff;
    struct node *t;
    struct node *h1=a.head,*h2=b.head;
    while(h1!=NULL){
        diff= h1->data-borrow;
        if(h2!=NULL){
            diff-=h2->data;
            h2=h2->next;
        }
        if(diff<0){
            borrow=1;
            diff+=10;
        }
        else{
            borrow=0;
        }
        struct node *newnode =(struct node *)malloc(sizeof(struct node));
        newnode->data= diff;
        newnode->next=NULL;
        if(temp.head==NULL){
            temp.head=newnode;
            t=newnode;
        }
        else{
            t->next=newnode;
            t=newnode;
        }
        h1=h1->next;
    }

    temp.length =length_of_ll(temp.head);
    return temp;
}



//*******************************************************************************************************

//sub
struct BigInteger subhelp(struct BigInteger a,struct BigInteger b){
    struct BigInteger temp=newtemp();
    int borrow=0,diff;
    struct node *t;
    struct node *h1=a.head,*h2=b.head;
    while(h1!=NULL){
        diff= h1->data-borrow;
        if(h2!=NULL){
            diff-=h2->data;
            h2=h2->next;
        }
        if(diff<0){
            borrow=1;
            diff+=10;
        }
        else{
            borrow=0;
        }
        struct node *newnode =(struct node *)malloc(sizeof(struct node));
        newnode->data= diff;
        newnode->next=NULL;
        if(temp.head==NULL){
            temp.head=newnode;
            t=newnode;
        }
        else{
            t->next=newnode;
            t=newnode;
        }
        h1=h1->next;
    }
    temp.head=truncate(temp.head);
    temp.length =length_of_ll(temp.head);
    return temp;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b){
if(a.sign!=b.sign){
    struct BigInteger temp=newtemp();
    temp.head= addition_of_ll(a.head,b.head);
    temp.length=length_of_ll(temp.head);
    temp.sign=a.sign;
    return temp;
}
if(compare(a,b)==-1){
    struct BigInteger temp=newtemp();
    temp.head= (struct node*)malloc(sizeof(struct node));
    (temp.head)->data=0;
    (temp.head)->next=NULL;
    temp.length=1;
    return temp;
}
if(compare(a,b)==0){
    struct BigInteger t = subhelp(a,b);
    
    t.sign=a.sign;
    return t;
}
if(compare(a,b)==1){
    struct BigInteger t = subhelp(b,a);
    t.sign = -1*a.sign;
    return t;
}

}



//**************************************************************************************************


//multiplication
struct node *single_multiply(struct node *head,int n){
	struct node *ans = NULL,*temp;
	int carry=0, p;
	while(head!=NULL||carry!=0){
		p = carry;
		if(head!=NULL){
			p+=head->data*n ;
			head=head->next;
		}
		carry = p/10;
		p=p%10;
		struct node *newnode =(struct node *)malloc(sizeof(struct node));
		newnode->data =p;
		newnode->next=NULL;
		if(ans==NULL){
			ans = newnode;
			temp=newnode;
		}
		else{
			temp->next=newnode;
			temp=newnode;
		}
	}
	return ans;
}

struct node *addition_of_multiplication(struct node *head1,struct node *head2){
	if(head1==NULL) return head2;
    struct node *head = NULL,*temp;
    int carry=0,sum;
    while(head1!=NULL||head2!=NULL||carry){
        sum = carry;
        if(head1!=NULL){
            sum+=head1->data;
            head1=head1->next;
        }
        if(head2!=NULL){
            sum +=head2->data;
            head2=head2->next;
        }
        carry = sum/10;
        sum = sum%10;
        
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data= sum;
        newnode->next = NULL;
        if(head==NULL){
            head = newnode;
            temp = newnode;
        }
        else{
            temp->next = newnode;
            temp = temp->next;
        }
    }
    return head;
    
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b){

	struct BigInteger temp=newtemp();
    if(a.length==1&&(a.head)->data==0){
        insert_at_begin(&temp,0);
        temp.length++;
        return temp;
    }
    if(b.length==1&&(b.head)->data==0){
        insert_at_begin(&temp,0);
        temp.length++;
        return temp;
    }
	int i=0;
	struct node *h1=a.head,*h2=b.head;
	while(h2!=NULL){
		struct node* pro=single_multiply(h1,h2->data);
		int j=i;
		while(j!=0){
			struct node *zero= (struct node *)malloc(sizeof(struct node));
			zero->data=0;
			zero->next=pro;
			pro=zero;
			j--;
		}
		temp.head = addition_of_multiplication(temp.head,pro);
		h2 = h2->next;
		i++;
	}
 
	temp.length=length_of_ll(temp.head);
    if(a.sign!=b.sign){
        temp.sign =-1;
    }
   
	return temp;

}


//****************************************************************************************************

//division

struct BigInteger divRepeatedAddition(struct BigInteger a,struct BigInteger  b){
    struct  BigInteger divisor=newtemp();
    divisor.head= NULL;
    int count =0;
    while(compare(a,divisor)==0){
        count++;
        divisor.head= addition_of_ll(divisor.head,b.head);
        divisor.length= length_of_ll(divisor.head);
    }
    if(compare(a,divisor)==1){
        count--;
    }

    struct node*head=NULL,*temp;
   while(count>0){
       struct node *newnode =(struct node *)malloc(sizeof(struct node));
        newnode->data= count%10;
        newnode->next=NULL;
        if(head==NULL){
            head=newnode;
            temp=newnode;
        }
        else{
            temp->next=newnode;
            temp=newnode;
        }
        count/=10;
   }
   struct BigInteger res =newtemp();
   res.head=head;
   res.length=length_of_ll(head);

   return res;

}

struct node* addzeros(struct node*head,int len){
    while(len--){
        struct node* n = (struct node*)malloc(sizeof(struct node));
        n->data=0;
        n->next=head;
        head=n;
    }
    return head;
}

struct BigInteger tenpower(int len){
    struct node* head = NULL,*temp;
    while(len--){
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data=0;
    n->next=NULL;
    if(head==NULL){
        head=n;
        temp=n;
    }
    else{
        temp->next=n;
        temp=n;
    }

    }
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data=1;
    n->next=NULL;
    temp->next=n;
    struct BigInteger r = newtemp();
    r.head=head;
    r.length=length_of_ll(head);

    return r;

}
struct BigInteger addofdiv(struct BigInteger a,struct BigInteger b){
    
    struct BigInteger temp=newtemp();
    struct node *h1=a.head,*h2=b.head;
    temp.head = NULL;
    struct node *t;
    int carry=0,sum;
    while(h1!=NULL||h2!=NULL||carry){
        sum = carry;
        if(h1!=NULL){
            sum+=h1->data;
            h1=h1->next;
        }
        if(h2!=NULL){
            sum +=h2->data;
            h2=h2->next;
        }
        carry = sum/10;
        sum = sum%10;
        
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data= sum;
        newnode->next = NULL;
        if(temp.head==NULL){
            temp.head = newnode;
            t = newnode;
        }
        else{
            t->next = newnode;
            t = t->next;
        }
    }
    temp.length = length_of_ll(temp.head);
    return temp;

}

struct BigInteger reccursion(struct BigInteger a,struct BigInteger b){
struct BigInteger temp;
temp.head= copy(b.head); temp.length=b.length; temp.sign=b.sign;
int len = a.length-b.length;
if(len<2){    //use multiple adiition
return divRepeatedAddition(a,b);
}
b.head = addzeros(b.head,len);
b.length+=len;
if(compare(a,b)==1){
    struct node*g =b.head;
    b.head=g->next;
    b.length--;
    len--;
    free(g);
}
struct BigInteger res = tenpower(len);
res.length=length_of_ll(res.head);

struct BigInteger nex =subofadd(a,b);
nex.head = truncate(nex.head);
nex.length=length_of_ll(nex.head);

return addofdiv(res,reccursion(nex,temp));
	
}


struct BigInteger div1(struct BigInteger a,struct BigInteger b){
    if(b.length==1&&(b.head)->data==0){
        return newtemp();
    }
   
    if(compare(a,b)==1||(a.length==1&&(a.head)->data==0)){
        struct BigInteger temp= newtemp();
        temp.head = (struct node*)malloc(sizeof(struct node));
        temp.length=1;
        (temp.head)->next=NULL;
        (temp.head)->data=0;

        return temp;
    }

struct BigInteger res = reccursion(a,b);
res.length=length_of_ll(res.head);
if(a.sign!=b.sign) res.sign =-1;
return res;

	
}


//****************************************************************************************************

//modulus

struct node* multiplication_of_ll(struct node *head1,struct node *head2){
	struct node *result = NULL;
	int i=0;
	while(head2!=NULL){
		struct node* pro=single_multiply(head1,head2->data);
		int j=i;
		while(j!=0){
			struct node *zero= (struct node *)malloc(sizeof(struct node));
			zero->data=0;
			zero->next=pro;
			pro=zero;
			j--;
		}
		result = addition_of_multiplication(result,pro);
		head2 = head2->next;
		i++;
	}
	return result;

}


struct BigInteger mod(struct BigInteger a,struct BigInteger b){
    if(b.length==1&&(b.head)->data==0){
        return newtemp();
    }
   
    if(compare(a,b)==1||(a.length==1&&(a.head)->data==0)){
        struct BigInteger temp= newtemp();
        temp.head = (struct node*)malloc(sizeof(struct node));
        temp.length=1;
        (temp.head)->next=NULL;
        (temp.head)->data=0;

        return temp;
    }

struct BigInteger fromdiv = reccursion(a,b);
fromdiv.length=length_of_ll(fromdiv.head);

struct node *modulus = NULL;
   modulus= multiplication_of_ll(fromdiv.head,b.head);
   modulus= subtraction_of_ll(a.head,modulus);
   struct BigInteger res =newtemp();
   res.head=modulus;
   res.head= truncate(res.head);
   res.length=length_of_ll(res.head);
   res.sign = a.sign;
   return res;

	
}
