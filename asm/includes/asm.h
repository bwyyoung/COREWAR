typedef struct  s_location
{
    int     line;
    int     col;
}               t_location;

typedef struct          s_token
{
    t_location          *pos;
    char                type;
    char                *value;
    struct s_token      *next;
}                       t_token;

// typedef struct  s_symbol
// {
//     char        *value;
//     char        *type;
//     s_symbol    *next;
// }               t_symbol;

// typedef struct  s_symbol
// {
//     char    **opcode;
//     char    **label;
// }               t_symbol;

typedef struct  s_op
{
    char        *op;
    int         pcount;
    char        ptypes[3];
    char        opcode;
    char        code_byte;
    char        label_size;
}               t_op;

typedef struct  s_label
{
    t_token *name;
    int     addr;
}               t_label;

typedef struct  s_inst
{
    // t_label         *label;
    int             size;
    char            opcode;
    unsigned char   type;
    int             pcount;
    t_token         *params;
    // t_token         *p1;
    // t_token         *p2;
    // t_token         *p3;
    struct s_inst   *next;
}               t_inst;

typedef struct  s_env
{
    int         line;
    header_t    *header;
    t_token     *token;
    t_token     *last;
    // t_symbol    *symbol;
    t_label     **labels;
    t_inst      *inst;
    int         label_count;
    int         pc;
}               t_env;
