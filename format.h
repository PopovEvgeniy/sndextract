typedef struct
{
 char signature[12];
 unsigned char verhi:4;
 unsigned char verhi2:4;
 unsigned char verhi3:4;
 unsigned char verhi4:4;
 unsigned char verlo:4;
 unsigned char verlo2:4;
 unsigned char verlo3:4;
 unsigned char verlo4:4;
 unsigned long int nb_sound:32;
 unsigned long int first_offset:32;
 char comment[488];
} head;

typedef struct
{
 unsigned long int next_offset:32;
 unsigned long int legth:32;
 unsigned long int nb_group:32;
 unsigned long int nb_sample:32;
} subhead;