#include "error_codes.h"
#include "macro.h"
#include "client_engine.h"
#include "cJSON.h"
#include "tags.h"

int client_set(char *key, char *value, char **req_str)
{
    int ret = RET_OK;
    cJSON *set_req = NULL;

    CHECK_PARAM(key);
    CHECK_PARAM(value);

    set_req = cJSON_CreateObject();
    cJSON_AddStringToObject(set_req, OPERATION_TAG, OPERATION_SET);
    cJSON_AddStringToObject(set_req, KEY_TAG, key);
    cJSON_AddStringToObject(set_req, VALUE_TAG, value);

    *req_str = cJSON_Print(set_req);

    cleanup:

    cJSON_Delete(set_req);

    return ret;
}

int client_get(char *key, char **req_str)
{
    int ret = RET_OK;
    cJSON *set_req = NULL;

    CHECK_PARAM(key);

    set_req = cJSON_CreateObject();
    cJSON_AddStringToObject(set_req, OPERATION_TAG, OPERATION_GET);
    cJSON_AddStringToObject(set_req, KEY_TAG, key);

    *req_str = cJSON_Print(set_req);

    cleanup:

    cJSON_Delete(set_req);

    return ret;
}

void client_stats(char **req_str)
{
    int ret = RET_OK;
    cJSON *stat_req = NULL;

    stat_req = cJSON_CreateObject();
    cJSON_AddStringToObject(stat_req, OPERATION_TAG, OPERATION_GET);

    *req_str = cJSON_Print(stat_req);

    cJSON_Delete(stat_req);
}

