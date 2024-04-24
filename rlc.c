#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAPE_SIZE 30000
int stroke_delay = 0;
int loopDepth = 0;

typedef enum {
    PULL,
    RECOVER,
    STROKE,
    BOW,
    CATCH,
    RELEASE,
    LOOP_START,
    LOOP_END,
    STROKE_RATE_INC,
    STROKE_RATE_DEC,
    END_OF_FILE,
    NEW_LINE,
    ERROR
} TokenType;

typedef struct {
    TokenType type; 
    int value;
} Token;

Token nextToken(FILE *);

void emitCode(Token);

void formatter(void);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
        return 1;
    }
    FILE *source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }
    printf("#include <stdio.h>\n#include <unistd.h>\n\nint main() {\n");
    printf("\tunsigned char tape[%d] = {0};\n\tunsigned char *memory = tape;\n\n", TAPE_SIZE);

    Token token;
    while ((token = nextToken(source)).type != END_OF_FILE) {
        if (token.type == LOOP_START) {
            printf("\twhile (*memory) {\n");
            loopDepth++;
        } else if (token.type == LOOP_END) {
            printf("\t}\n");
            loopDepth--;
        } else {
            emitCode(token);
        }
    }
    if (loopDepth != 0) {
        printf("//Error: Unmatched loop brackets.\n");
        printf("\nreturn 1;\n}");
        fclose(source);
    }
    else if (token.type == ERROR){
        printf("//Error: Unrecognised command.\n");
        printf("\nreturn 1;\n}");
        fclose(source);
    }
    else{
        printf("\n\treturn 0;\n}");
        fclose(source);
    }
    return 0;
}

Token nextToken(FILE *file) {
    Token token;
    char ch = fgetc(file), rep;
    switch (ch) {
        case 'P':
            token.type = PULL;
            break;
        case 'R':
            token.type = RECOVER;
            break;
        case 'S':
            token.type = STROKE;
            break;
        case 'B':
            token.type = BOW;
            break;
        case '.':
            token.type = CATCH;
            break;
        case ',':
            token.type = RELEASE;
            break;
        case '[':
            token.type = LOOP_START;
            break;
        case ']':
            token.type = LOOP_END;
            break;
        case '^':
            token.type = STROKE_RATE_INC;
            break;
        case 'v':
            token.type = STROKE_RATE_DEC;
            break;
        case EOF:
            token.type = END_OF_FILE;
            break;
        case '\n':
            token.type = NEW_LINE;
            break;
        default:
            token.type = ERROR;
    }
    if (token.type != (END_OF_FILE || ERROR)){
        token.value = 1;
        rep=fgetc(file);
        if (isdigit(rep)) {
            ungetc(rep, file);
            fscanf(file, "%d", &token.value);
        }
        ungetc(rep, file);
    }
    return token;
}

void emitCode(Token token) {
    switch (token.type) {
        case PULL:
            formatter();
            printf("memory+=%d;\n", token.value);
            break;
        case RECOVER:
            formatter();
            printf("memory-=%d;\n", token.value);
            break;
        case STROKE:
            formatter();
            printf("*memory+=%d;\n", token.value);
            formatter();
            printf("sleep(%d);\n", stroke_delay);
            break;
        case BOW:
            formatter();
            printf("*memory-=%d;\n", token.value);
            formatter();
            printf("sleep(%d);\n", stroke_delay);
            break;
        case CATCH:
            formatter();
            printf("putchar(*memory);\n");
            break;
        case RELEASE:
            formatter();
            printf("*memory = getchar();\n");
            break;
        case LOOP_START:
            formatter();
            printf("while (*memory) {\n");
            break;
        case LOOP_END:
            formatter();
            printf("}\n");
            break;
        case STROKE_RATE_INC:
            stroke_delay -= token.value;
            if (stroke_delay < 0)
                stroke_delay = 0;
            break;
        case STROKE_RATE_DEC:
            stroke_delay += token.value;
            break;
        case END_OF_FILE:
            formatter();
            printf("// End of file\n");
            break;
        case NEW_LINE:
            break;
        default:
            break;
    }
}

void formatter(void){
    for (int i=0; i<= loopDepth; i++)
        printf("\t");
}