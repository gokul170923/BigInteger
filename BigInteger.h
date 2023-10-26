#ifndef BigInteger_H
#define BigInteger_H
//struct
struct node{
    int data;
    struct node *next;
};
struct BigInteger{
    struct node *head;
    int length;
    int sign;
};
void revdisplay(struct node*,int);
void display(struct BigInteger );
int length_of_ll(struct node *);
//compare
int compare(struct BigInteger , struct BigInteger );
struct node*copy(struct node *);
//insert at begin
void insert_at_begin(struct BigInteger *,int );
struct node* insert0(struct node*);
//initailize
struct BigInteger initialize(char *);

//truncate
struct node* reverse(struct node* ) ;
struct node*truncate(struct node*);

//newtemp
struct BigInteger newtemp();
//add of ll
struct node *addition_of_ll(struct node *,struct node *);

//sub of ll
struct node *subtraction_of_ll(struct node *,struct node *);



//add
struct BigInteger add(struct BigInteger ,struct BigInteger );
struct BigInteger subofadd(struct BigInteger ,struct BigInteger );
//sub
struct BigInteger subhelp(struct BigInteger ,struct BigInteger );
struct BigInteger sub(struct BigInteger ,struct BigInteger );
//multiplication

struct node *single_multiply(struct node *,int );
struct node *addition_of_multiplication(struct node *,struct node *);
struct BigInteger mul(struct BigInteger ,struct BigInteger );

//divison

struct BigInteger divRepeatedAddition(struct BigInteger ,struct BigInteger  );
struct node* addzeros(struct node*,int );
struct BigInteger tenpower(int );
struct BigInteger addofdiv(struct BigInteger ,struct BigInteger );
struct BigInteger reccursion(struct BigInteger ,struct BigInteger );
struct BigInteger div1(struct BigInteger ,struct BigInteger );


///modulus

struct node* multiplication_of_ll(struct node *,struct node *);

struct BigInteger mod(struct BigInteger ,struct BigInteger );



#endif