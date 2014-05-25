typedef struct _pair {
  int sequence[100];
  int sequence_length;
  } Pair;

typedef struct _var_table_record {
  char name[256];
  char type;
  int is_declared;
  int is_assigned;
  union {
    int i_value;
  } value;
} VarTableRecord;

typedef struct _var_table_node {
  VarTableRecord record;
  struct _var_table_node* next;
  } VarTableNode;

typedef struct _var_table {
  VarTableNode* head;
} VarTable;

typedef enum { con, var, oper } SynTreeNodeType;

typedef struct _oper_node {
    int lexem_name;
    int operands_number;
    struct _tree_node** operands;
} OperNode;

typedef struct _tree_node {
    SynTreeNodeType type;
    union {
        int con_value;
        VarTableRecord* var_pointer;
        OperNode oper_node;
    } value;
} MyTreeNode;

typedef union _result {
    int i_value;
    Pair* a_value;
} Result;

VarTableRecord * addRecord(const char *);
VarTableRecord * findRecord(const char *);
 