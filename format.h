typedef struct
{
 char signature[12];
 unsigned char version[4];
 unsigned int amount;
 unsigned int first_offset;
 char comment[488];
} head;

typedef struct
{
 unsigned int next_offset;
 unsigned int legth;
 unsigned int group;
 unsigned int sample;
} subhead;