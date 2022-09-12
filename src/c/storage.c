#include <Judy.h>
#include <stdio.h>

#include "storage.h"
#include "error_codes.h"
#include "macro.h"


static Pvoid_t PJSLArray = (Pvoid_t) NULL;  // initialize JudySL array

int storage_load_state(char *path)
{
    //TODO
    return 0;
}

int storage_save_state(char *path)
{
    //TODO:
    return 0;
}

int storage_get_value(const uint8_t *key, uint8_t **value)
{
    int ret = RET_OK;
    Word_t * PValue = NULL;

    JSLG(PValue, PJSLArray, key);
    CHECK_NOT_NULL(PValue);

    *value = (uint8_t *)*PValue;

cleanup:

    return ret;
}

int storage_set_value(const uint8_t *key, uint8_t *value)
{
    int ret = RET_OK;
    Word_t * PValue = NULL;

    JSLI( PValue,  PJSLArray, (uint8_t *)key);
    if (PValue == PJERR) {
        ret = RET_MEMORY_ALLOC_ERROR;
        goto cleanup;
    }
    *PValue=(Word_t)value;

cleanup:

    return ret;
}

