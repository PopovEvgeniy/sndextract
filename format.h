typedef struct
{
 char signature[12];
 unsigned char version[4];
 unsigned long int amount:32;
 unsigned long int first_offset:32;
 char comment[488];
} head;

typedef struct
{
 unsigned long int next_offset:32;
 unsigned long int legth:32;
 unsigned long int group:32;
 unsigned long int sample:32;
} subhead;