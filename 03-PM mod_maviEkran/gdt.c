typedef struct
{
    int 0;

}Nulldesc;

typedef struct 
{
    int P_present;
    int PDL_privilege;
    int S_type;
    int E_code;
    int DC_conforming;
    int RW_readable;
    int A_accessed;

}AccessByte;

typedef struct
{
    int G_granularity;
    int DB_32bits;
    int L_longmode;
    int AVL_reserved;
}Flags;

typedef struct 
{
    int limit_0;
    int base_0;
    int base_1;
    AccessByte accessByte;
    int limit_1;
    Flags flags;
    int base_2;
}Codedesc;

struct GDT
{
    Nulldesc nulldes;
    Codedesc codedes;
};
