#include <fstream>
#include <iostream>
#include <iterator>
#include "TreeSitterParser.h"
#include <cstring>
#include <tree_sitter/api.h>

extern "C" const TSLanguage *tree_sitter_cpp();

vector<ParsedFunction> TreeSitterParser::parseFile(const string &path)
{
    vector<ParsedFunction> functions;

    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Cannot open file: " << path << endl;
        return functions;
    }

    string source(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>());

    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_cpp());

    TSTree *tree = ts_parser_parse_string(
        parser,
        nullptr,
        source.c_str(),
        source.size());

    TSNode root = ts_tree_root_node(tree);

    uint32_t childCount = ts_node_child_count(root);

    for (uint32_t i = 0; i < childCount; i++)
    {
        TSNode child = ts_node_child(root, i);

        if (strcmp(ts_node_type(child), "function_definition") != 0)
            continue;

        TSNode declarator =
            ts_node_child_by_field_name(
                child,
                "declarator",
                strlen("declarator"));

        TSNode name =
            ts_node_child_by_field_name(
                declarator,
                "declarator",
                strlen("declarator"));

        ParsedFunction fn;

        fn.name = source.substr(
            ts_node_start_byte(name),
            ts_node_end_byte(name) - ts_node_start_byte(name));

        fn.code = source.substr(
            ts_node_start_byte(child),
            ts_node_end_byte(child) - ts_node_start_byte(child));

        fn.file = path;

        fn.startLine = ts_node_start_point(child).row + 1;
        fn.endLine = ts_node_end_point(child).row + 1;

        functions.push_back(fn);
    }

    ts_tree_delete(tree);
    ts_parser_delete(parser);

    return functions;
}