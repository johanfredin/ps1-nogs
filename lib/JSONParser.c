#include "stdlib.h"
#include "stdio.h"

#include "JSONParser.h"

#include <stdbool.h>
#include <stdint.h>

#include "Heap.h"
#include "StrUtils.h"
#include "Logger.h"

static size_t g_index = 0;
static char *g_content = NULL;

static void get_value(JSON_Data *);
static void get_str(JSON_Data *entry, uint8_t type);
static void get_array(JSON_Data *);
static void get_object(JSON_Data *);
static void get_number(JSON_Data *);
static void get_bool(JSON_Data *);
static void print_recursive(const JSON_Data *root, int indents);
static void ff_to_start();
static char skip_irrelevant_chars();
static char *get_numeric_str();
static char *read_until(char end_char, bool include_end_char);
static char curr_ch();
static char next_ch();
static JSON_Data *malloc_json_entry();
static bool is_num();

JSON_Data *JSON_Parse(char *file_content) {
    // Calc length of content
    size_t content_length = 0;

    SET_STR_LEN(content_length, file_content);

    g_content = file_content;
    JSON_Data *root = malloc_json_entry();
    JSON_Data *curr = root;
    ff_to_start();
    while (g_index < content_length) {
        skip_irrelevant_chars();

        get_str(curr, 'k');
        skip_irrelevant_chars();
        get_value(curr);
        skip_irrelevant_chars();

        // Go to next if we have not reached the end yet
        size_t next_idx = g_index + 1;
        const char next_char = g_content[next_idx];
        if (next_idx >= content_length || next_char == '\0' || (next_char == '}' && g_content[++next_idx] == '\0')) {
            break;
        }
        curr->next = malloc_json_entry();
        curr = curr->next;
        skip_irrelevant_chars();
        g_index++;
    }

    return root;
}

void JSON_Print(const JSON_Data *root) {
    printf("{\n");
    print_recursive(root, 2);
    printf("}\n");
}

void JSON_Destroy(JSON_Data *root) {
    JSON_Data *curr = root;
    while (curr != NULL) {
        const uint8_t is_nested = curr->type.arr | curr->type.obj;
        if (is_nested) {
            JSON_Destroy(curr->value);
        }
        JSON_Data *aux = curr;
        curr = curr->next;
        if (is_nested) {
            aux->value = NULL;
        } else {
            Heap_Free(aux->value);
        }
        Heap_Free(aux->key);
        Heap_Free(aux);
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
static void print_recursive(const JSON_Data *root, const int indents) {
    char padding[32];
    for (int i = 0; i < indents; i++) {
        padding[i] = ' ';
    }
    padding[indents] = '\0'; // Add null terminator

    for (const JSON_Data *curr = root; curr != NULL; curr = curr->next) {
        char *comma = curr->next == NULL ? "" : ",";
        printf("%s", padding);
        if (curr->key != NULL) {
            printf("\"%s\": ", curr->key);
        }
        // Check value
        if (curr->type.str) {
            printf("\"%s\"%s\n", (char *) curr->value, comma);
        } else if (curr->type.decimal) {
            printf("%.2f%s\n", *(float *) curr->value, comma);
        } else if (curr->type.integer) {
            printf("%i%s\n", *(int *) curr->value, comma);
        } else if (curr->type.boolean) {
            printf("%s%s\n", *(unsigned char *) curr->value == 1 ? "true" : "false", comma);
        } else if (curr->type.arr) {
            printf("[\n");
            print_recursive(curr->value, indents + 2);
            printf("%s]%s\n", padding, comma);
        } else if (curr->type.obj) {
            printf("{\n");
            print_recursive(curr->value, indents + 2);
            printf("%s}%s\n", padding, comma);
        }
    }
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
static void get_value(JSON_Data *entry) {
    const char c = curr_ch();
    if (c == '\"') {
        get_str(entry, 'v');
    } else if (c == '[') {
        g_index++;
        skip_irrelevant_chars();
        get_array(entry);
    } else if (c == '{') {
        g_index++;
        skip_irrelevant_chars();
        get_object(entry);
    } else if (is_num()) {
        get_number(entry);
    } else if (c == 't' || c == 'f') {
        get_bool(entry);
    } else {
        g_index++;
        skip_irrelevant_chars();
        get_value(entry);
    }
}
#pragma clang diagnostic pop

static void get_str(JSON_Data *entry, const uint8_t type) {
    if (curr_ch() == '\"') {
        next_ch();
    }

    char *str = read_until('\"', 0);
    if (type == 'k') {
        entry->key = str;
    } else if (type == 'v') {
        entry->value = str;
        entry->type.str = 1;
    } else {
        logr_log(ERROR, "JSONParser.c", "get_str", "value=%c not one of 'k', 'v'\n", type);
        exit(1);
    }
}

static void get_number(JSON_Data *entry) {
    char *num_str = get_numeric_str();
    if (strchr(num_str, '.')) {
        logr_log(TRACE, "JSONParser.c", "get_number", "Floating point not implemented for ps1 and will not be parsed, key=%s", entry->key);
    } else {
        int *i_ptr = Heap_Malloc(sizeof(int));
        *i_ptr = (int) strtol(num_str, NULL, 10);
        entry->value = i_ptr;
        entry->type.integer = 1;
    }
    Heap_Free(num_str);
}

static void get_bool(JSON_Data *entry) {
    char *str_bool = read_until('e', true);    // true and false both end at 'e'
    bool *bool_ptr = Heap_Malloc(sizeof(bool));
    *bool_ptr = STR_EQ(str_bool, "true");
    Heap_Free(str_bool);
    entry->value = bool_ptr;
    entry->type.boolean = 1;
}

static void get_array(JSON_Data *entry) {
    JSON_Data *root = malloc_json_entry();
    JSON_Data *curr = root;
    entry->type.arr = 1;
    char c = curr_ch();
    while (c != ']') {
        JSON_Data *next = NULL;
        skip_irrelevant_chars();
        get_value(curr);
        c = skip_irrelevant_chars();

        if (c == ']') {
            break;
        }

        next = malloc_json_entry();
        curr->next = next;
        curr = curr->next;
    }
    entry->value = root;
    next_ch(); // So that we iterate past the last ] char
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
static void get_object(JSON_Data *entry) {
    JSON_Data *root = malloc_json_entry();
    JSON_Data *curr = root;
    entry->type.obj = 1;
    char c = curr_ch();
    while (c != '}') {
        skip_irrelevant_chars();
        get_str(curr, 'k');
        skip_irrelevant_chars();
        get_value(curr);
        c = skip_irrelevant_chars();

        if (c == '}') {
            break;
        }

        curr->next = malloc_json_entry();
        curr = curr->next;
    }
    entry->value = root;
    next_ch(); // So that we iterate past the last } char
}
#pragma clang diagnostic pop

static JSON_Data *malloc_json_entry() {
    return Heap_Malloc(sizeof(JSON_Data));
}

static char *read_until(const char end_char, const bool include_end_char) {
    const uint8_t size = 100;
    char *str = Heap_Calloc(size, sizeof(char));

    size_t i = 0;
    char c = curr_ch();
    while (c != end_char) {
        str[i] = c;
        c = next_ch();
        if (i >= size) {
            logr_log(ERROR, "JSONParser.c", "read_until", "String exceeded max length of %i, accumulated string=%s\n", size, str);
            exit(1);
        }
        i++;
    }

    if (include_end_char) {
        str[i] = end_char;
        i++;
    }

    str[i] = '\0';
    next_ch(); // So that we iterate past the last " char
    return str;
}

static char *get_numeric_str() {
    const size_t size = 15;
    char *str = Heap_Calloc(size, sizeof(char));
    size_t i = 0;
    for (i = 0; is_num(); i++) {
        str[i] = curr_ch();
        next_ch();
        if (i >= size) {
            logr_log(ERROR, "JSONParser.c", "get_numeric_str", "Numeric string exceeded max length of %i, accumulated string=%s\n", size, str);
            exit(1);
        }
    }
    str[i] = '\0';
    return str;
}

static bool is_num() {
    const char c = curr_ch();
    return strstr(&c, "0123456789.");
}

static void ff_to_start() {
    while (g_content[g_index]) {
        if (g_content[g_index++] == '{') {
            return;
        }
    }
}

static char skip_irrelevant_chars() {
    char c = curr_ch();
    while (c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == ',') {
        c = next_ch();
    }
    return c;
}

static char curr_ch() {
    return g_content[g_index];
}

static char next_ch() {
    if (curr_ch()) {
        return g_content[++g_index];
    }
    return curr_ch();
}