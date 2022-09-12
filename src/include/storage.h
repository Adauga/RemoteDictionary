#include <bits/stdint-uintn.h>
#include "Judy.h"

#ifndef REMOTEDICTIONARY_STORAGE_H
#define REMOTEDICTIONARY_STORAGE_H

int storage_get_value(const uint8_t *key, uint8_t **value);
int storage_set_value(const uint8_t *key, uint8_t *value);

#endif //REMOTEDICTIONARY_STORAGE_H
