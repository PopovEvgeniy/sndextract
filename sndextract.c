#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_intro();
void command_line_help();
void show_start_message();
void show_end_message();
void show_progress(unsigned long int start, unsigned long int stop);
FILE *open_input_file(char *name);
FILE *create_output_file(char *name);
void data_dump(FILE *input, FILE *output, unsigned long int length);
void write_output_file(FILE *input, char *name, unsigned long int length);
void go_offset(FILE *file, unsigned long int offset);
unsigned long int get_file_size(FILE *file);
char *get_string_memory(unsigned long int length);
unsigned long int get_extension_position(char *source);
char *get_short_name(char *name);
char *get_name(unsigned long int index,char *short_name, char *extension);
head read_head(FILE *file);
subhead read_subhead(FILE *file);
void extract(FILE *input,char *name);
void extract_last(FILE *input,char *name,unsigned long int snd_size);
void work(char *file);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  command_line_help();
 }
 else
 {
  show_start_message();
  work(argv[1]);
  show_end_message();
 }
 return 0;
}

void show_intro()
{
 puts(" ");
 puts("SND EXTRACT");
 puts("Version 2.3.1");
 puts("Mugen sound extractor by Popov Evgeniy Alekseyevich, 2008-2016 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void command_line_help()
{
 puts(" ");
 puts("You must give a target file name as command line argument!");
}

void show_start_message()
{
 puts(" ");
 puts("Extracting a sounds... Please wait");
}

void show_end_message()
{
 puts(" ");
 puts("Work finish");
}

void show_progress(unsigned long int start, unsigned long int stop)
{
 unsigned long int progress;
 progress=start+1;
 progress*=100;
 progress/=stop;
 printf("\r");
 printf("Amount of extracted files: %ld from %ld.Progress:%ld%%",start+1,stop,progress);
}

FILE *open_input_file(char *name)
{
 FILE *file;
 file=fopen(name,"rb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

FILE *create_output_file(char *name)
{
 FILE *file;
 file=fopen(name,"wb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

void data_dump(FILE *input, FILE *output, unsigned long int length)
{
 unsigned char single_byte;
 unsigned long int index;
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,1);
 if (buffer==NULL)
 {
  for(index=0;index<length;index++)
  {
   fread(&single_byte,1,1,input);
   fwrite(&single_byte,1,1,output);
  }

 }
 else
 {
  fread(buffer,length,1,input);
  fwrite(buffer,length,1,output);
  free(buffer);
 }

}

void write_output_file(FILE *input, char *name, unsigned long int length)
{
 FILE *output;
 output=create_output_file(name);
 data_dump(input,output,length);
 fclose(output);
}

void go_offset(FILE *file, unsigned long int offset)
{
 fseek(file,offset,SEEK_SET);
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

char *get_string_memory(unsigned long int length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,1);
 if(memory==NULL)
 {
  puts(" ");
  puts("Can't allocate memory");
  exit(1);
 }
 return memory;
}

unsigned long int get_extension_position(char *source)
{
 unsigned long int index;
 for(index=strlen(source);index>0;index--)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(char *name)
{
 unsigned long int length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char *get_name(unsigned long int index,char *short_name, char *extension)
{
 char *name=NULL;
 char *result=NULL;
 unsigned long int length;
 length=strlen(short_name)+strlen(extension)+12;
 name=get_string_memory(length);
 sprintf(name,"%s%ld%s",short_name,index,extension);
 length=strlen(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 free(name);
 return result;
}

head read_head(FILE *file)
{
 head snd_head;
 fread(&snd_head,sizeof(head),1,file);
 if (strncmp(snd_head.signature,"ElecbyteSnd",12)!=0)
 {
  puts(" ");
  puts("Bad signature of a mugen sound pseudo-archive");
  exit(3);
 }
 return snd_head;
}

subhead read_subhead(FILE *file)
{
 subhead snd_subhead;
 fread(&snd_subhead,sizeof(subhead),1,file);
 return snd_subhead;
}

void extract(FILE *input,char *name)
{
 subhead snd_subhead;
 unsigned long int length;
 snd_subhead=read_subhead(input);
 length=snd_subhead.next_offset-ftell(input);
 write_output_file(input,name,length);
 go_offset(input,snd_subhead.next_offset);
}

void extract_last(FILE *input,char *name,unsigned long int snd_size)
{
 unsigned long int length;
 length=ftell(input)+sizeof(subhead);
 go_offset(input,length);
 length=snd_size-ftell(input);
 write_output_file(input,name,length);
}

void work(char *file)
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
 for (index=0;index<snd_head.nb_sound-1;index++)
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