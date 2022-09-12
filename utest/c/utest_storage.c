#include <Judy.h>
#include "storage.h"

void utest_storage(void) {
    char *text_1 = "Text 1 test";
    char *key_1 = "Key 1";

    char *get_value_1 = NULL;

    storage_set_value((uint8_t *)key_1, (uint8_t *)text_1);
    storage_get_value((uint8_t *)key_1, (uint8_t **)&get_value_1);
}

int main()
{
    utest_storage();
}