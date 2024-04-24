#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAPE_SIZE 30000

typedef enum {
    PULL,
    RECOVER,
    STROKE,
    BOW,
    CATCH,
    RELEASE,
    LOOP_START,
    LOOP_END,
    END_OF_FILE
} TokenType;

typedef struct {
    TokenType type; 
    int value;
} Token;

Token nextToken(FILE *);

void emitCode(Token);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
        return 1;
    }
    FILE *source = fopen(argv[1], "r");
    if (!source) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }
    printf("#include <stdio.h>\n\nint main() {\n");
    printf("unsigned char tape[%d] = {0};\nunsigned char *memory = tape;\n", TAPE_SIZE);

    int loopDepth = 0;
    Token token;
    while ((token = nextToken(source)).type != END_OF_FILE) {
        if (token.type == LOOP_START) {
            printf("int loop%d = 0;\n", loopDepth);
            printf("while (*memory) {\n");
            loopDepth++;
        } else if (token.type == LOOP_END) {
            printf("}\n");
            loopDepth--;
        } else {
            emitCode(token);
        }
    }
    if (loopDepth != 0) {
        printf("Error: Unmatched loop brackets.\n");
        return 1;
    }
    printf("\nreturn 0;\n}");
    fclose(source);
    return 0;
}

Token nextToken(FILE *source) {
    Token token;
    char c = fgetc(source);
    switch (c) {
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
        case EOF:
            token.type = END_OF_FILE;
            break;
        default:
            return nextToken(source);
    }
    if ((c = fgetc(source)) >= '0' && c <= '9') {
        ungetc(c, source);
        fscanf(source, "%d", &token.value);
    } else {
        ungetc(c, source);
        token.value = 1;
    }
    return token;
}


void emitCode(Token token) {
    switch (token.type) {
        case PULL:
            printf("memory += %d;", token.value);
            break;
        case RECOVER:
            printf("memory -= %d;", token.value);
            break;
        case STROKE:
            printf("(*memory) += %d;", token.value);
            break;
        case BOW:
            printf("(*memory) -= %d;", token.value);
            break;
        case CATCH:
            printf("putchar(*memory);");
            break;
        case RELEASE:
            printf("*memory = getchar();");
            break;
        case LOOP_START:
            printf("while (*memory) {");
            break;
        case LOOP_END:
            printf("}");
            break;
        default:
            break;
    }
}
