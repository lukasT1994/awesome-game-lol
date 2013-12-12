#include "defs.h"

void writeScore(char* name,int score, FILE* stream){

fputs(name,stream);
fputc(' ',stream);
fputc((char)score,stream);
fputc('\n',stream);

return;
}
