extern "C" {
    #include "parser.tab.h"
    #include <cstdio>
    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    extern YY_BUFFER_STATE yy_scan_string(const char * str);
    extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);
    extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
    extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
}
#include "lang.h"
#include <iostream>
#include <fstream>

Engine *hawk_engine;

void from_stream(std::string command, std::basic_ifstream<char> *stream){
    hawk_engine = new Engine(' ', stream);
    // for line in input code
    auto input_line = std::string(command) + "\n";

    while(hawk_engine->parse_line()){
        YY_BUFFER_STATE line_buf = yy_scan_string(input_line.c_str());
        yy_switch_to_buffer(line_buf);
        yyparse();
        yy_delete_buffer(line_buf);
    }
    hawk_engine->reset_stream();
    delete hawk_engine;
}

void from_file(std::string command, std::string filename){
    auto s = std::ifstream(filename);
    from_stream(command, &s);
}

void code_from_file(std::string code_file, std::string filename){
    auto c = std::ifstream (code_file);
    std::string line;
    while(std::getline(c, line)){
        from_file(line, filename);
    }
}

void help(){
    std::cout << "Usage: hawk [command] <data_file>   - run inline with data from file" << std::endl;
    std::cout << "       hawk <code_file> <data_file> - code and data are in files" << std::endl;
    std::cout << "       hawk [command]               - run inline from stdin" << std::endl;
}

int main(int argc, char** argv) {
    /*
     * Examples:
     * 1. List file: hawk "$0" input.txt
     * 2. Filter by field or with constant:  hawk "$1 == 123 { $3 }" input.txt
     * 3. GT/LT filtering:  hawk "$1 > $2 { $3 }" input.txt
     * 4. Stdin input: cat input2.txt | hawk "$1 == $2 {$0}"
     * 5. All from files: hawk code.txt input2.txt
     * 6. Print va_args: hawk "$1 > 1 {print($1, $2, $3)}" input2.txt
     * 7. Conditions: hawk "$1 == 1 || $1 == 2 {print(\$0)}" input2.txt
     *
     * next todo:
     * 1. Conditions order ($1 == 1 || $2 == 3) && $3 < 5
     * 2. Need to find how to disable env vars usage (to not do \$X
        FIXME process argv without env vars
        hawk "$0" - processed as env var $0
        awk "$0" processed as string $0
     * */
    if(argc < 2){
        help();
        return 0;
    }
    if (argc == 2){
        std::string op1 = std::string(argv[1]);
        from_stream(op1, (std::basic_ifstream<char>*)(&(std::cin)));
        return 0;
    }
    if(argc > 3){
        help();
        return 0;
    }

    std::string op1 = std::string(argv[1]);
    std::string op2 = std::string(argv[2]);

    std::ifstream input_code(op1.c_str());
    if(input_code.good()){
        code_from_file(op1, op2);
        return 0;
    }

    from_file(op1, op2);
    return 0;
}
