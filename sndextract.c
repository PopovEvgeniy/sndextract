#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_intro();
void show_message(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void go_offset(FILE *file,const unsigned long int offset);
unsigned long int get_file_size(FILE *file);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *get_string_memory(const size_t length);
size_t get_extension_position(const char *source);
char *get_short_name(const char *name);
char *get_name(const unsigned long int index,const char *short_name,const char *extension);
void check_signature(const char *signature);
head read_head(FILE *file);
subhead read_subhead(FILE *file);
void extract(FILE *input,const char *name);
void extract_last(FILE *input,const char *name,const unsigned long int snd_size);
void work(const char *file);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  show_message("You must give a target file name as command line argument!");
 }
 else
 {
  show_message("Extracting a sounds... Please wait");
  work(argv[1]);
  show_message("Work finish");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("SND EXTRACT");
 puts("Version 2.5.4");
 puts("Mugen sound extractor by Popov Evgeniy Alekseyevich, 2008-2024 years");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 unsigned long int progress;
 progress=(start+1)*100;
 progress/=stop;
 putchar('\r');
 printf("Amount of extracted files: %lu from %lu.Progress:%lu%%",start+1,stop,progress);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_message("Can't create ouput file");
  exit(2);
 }
 return target;
}

void go_offset(FILE *file,const unsigned long int offset)
{
 if (fseek(file,offset,SEEK_SET)!=0)
 {
  show_message("Can't jump to target offset");
  exit(3);
 }

}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(4);
 }
 return memory;
}

size_t get_extension_position(const char *source)
{
 size_t index;
 for(index=strlen(source);index>0;--index)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(const char *name)
{
 size_t length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char *get_name(const unsigned long int index,const char *short_name,const char *extension)
{
 char *name=NULL;
 size_t length;
 length=strlen(short_name)+strlen(extension)+12;
 name=get_string_memory(length);
 sprintf(name,"%s%lu%s",short_name,index,extension);
 return name;
}

void check_signature(const char *signature)
{
 if (strncmp(signature,"ElecbyteSnd",12)!=0)
 {
  puts("Bad signature of a mugen sound pseudo-archive");
  exit(5);
 }

}

head read_head(FILE *file)
{
 head snd_head;
 fread(&snd_head,sizeof(head),1,file);
 check_signature(snd_head.signature);
 return snd_head;
}

subhead read_subhead(FILE *file)
{
 subhead snd_subhead;
 fread(&snd_subhead,sizeof(subhead),1,file);
 return snd_subhead;
}

void extract(FILE *input,const char *name)
{
 subhead snd_subhead;
 unsigned long int length;
 snd_subhead=read_subhead(input);
 length=snd_subhead.next_offset-ftell(input);
 write_output_file(input,name,(size_t)length);
 go_offset(input,snd_subhead.next_offset);
}

void extract_last(FILE *input,const char *name,const unsigned long int snd_size)
{
 unsigned long int length;
 length=ftell(input)+(unsigned long int)sizeof(subhead);
 go_offset(input,length);
 length=snd_size-ftell(input);
 write_output_file(input,name,(size_t)length);
}

void work(const char *file)
{
 FILE *input;
 head snd_head;
 unsigned long int index,snd_size;
 char *wave_name=NULL;
 char *short_name=NULL;
 short_name=get_short_name(file);
 input=open_input_file(file);
 snd_size=get_file_size(input);
 snd_head=read_head(input);
 go_offset(input,snd_head.first_offset);
 for (index=0;index<snd_head.nb_sound-1;++index)
 {
  show_progress(index,snd_head.nb_sound);
  wave_name=get_name(index+1,short_name,".wav");
  extract(input,wave_name);
  free(wave_name);
 }
 show_progress(index,snd_head.nb_sound);
 wave_name=get_name(index+1,short_name,".wav");
 extract_last(input,wave_name,snd_size);
 free(wave_name);
 free(short_name);
 fclose(input);
}