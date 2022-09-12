#include <string.h>

#include "macro.h"
#include "error_codes.h"
#include "server_engine.h"
#include "tags.h"
#include "storage.h"
#include "cJSON.h"

static int operation_get = 0;
static int s_operation_get = 0;
static int f_operation_get = 0;

static void gen_stat(char **response)
{
    cJSON *resp_obj = NULL;

    resp_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(resp_obj, COUNT_ALL, operation_get);
    cJSON_AddNumberToObject(resp_obj, COUNT_S, s_operation_get);
    cJSON_AddNumberToObject(resp_obj, COUNT_F, f_operation_get);

    *response = cJSON_Print(resp_obj);

cleanup:

    cJSON_Delete(resp_obj);
}

static int gen_resp(char *operation, char *key, char *value, char *status, char **response)
{
    int ret = RET_OK;
    cJSON *resp_obj = NULL;

    resp_obj = cJSON_CreateObject();
    cJSON_AddStringToObject(resp_obj, OPERATION_TAG, operation);
    cJSON_AddStringToObject(resp_obj, KEY_TAG, key);
    cJSON_AddStringToObject(resp_obj, VALUE_TAG, value);
    cJSON_AddStringToObject(resp_obj, STATUS_TAG, status);

    *response = cJSON_Print(resp_obj);

cleanup:

    cJSON_Delete(resp_obj);

    return ret;
}

int parse_req(char *req_json, char **resp_json)
{
    int ret = RET_OK;
    cJSON *json_obj = NULL;
    cJSON *operation = NULL;
    cJSON *key = NULL;
    cJSON *value = NULL;
    char *resp_json_internal = NULL;
    char *value_str = NULL;

    CHECK_PARAM(req_json);

    json_obj = cJSON_Parse(req_json);
    operation = cJSON_GetObjectItemCaseSensitive(json_obj, OPERATION_TAG);
    if (!strcmp(operation->valuestring, OPERATION_SET)) {
        key = cJSON_GetObjectItemCaseSensitive(json_obj, KEY_TAG);
        value = cJSON_GetObjectItemCaseSensitive(json_obj, VALUE_TAG);
        ret = storage_set_value((uint8_t *)key->valuestring, (uint8_t *)value->valuestring);
        gen_resp(operation->valuestring, key->valuestring, value->valuestring,
                 ret == RET_OK ? STATUS_DONE : STATUS_FAIL, &resp_json_internal);
    } else if (!strcmp(operation->valuestring, OPERATION_GET)) {
        key = cJSON_GetObjectItemCaseSensitive(json_obj, KEY_TAG);
        ret = storage_get_value((uint8_t *)key->valuestring, (uint8_t **)&value_str);
        gen_resp(operation->valuestring, key->valuestring, value_str,
                 ret == RET_OK ? STATUS_DONE : STATUS_FAIL, &resp_json_internal);
        operation_get++;
        ret == RET_OK ? s_operation_get++ : f_operation_get++;
    } else if (!strcmp(operation->valuestring, OPERATION_ST)) {
        gen_stat(&resp_json_internal);
    }

    *resp_json = resp_json_internal;

cleanup:

    cJSON_Delete(json_obj);
    if (value_str) {
        free(value_str);
    }

    return ret;
}