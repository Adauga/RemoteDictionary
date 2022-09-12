#ifndef REMOTEDICTIONARY_CLIENT_ENGINE_H
#define REMOTEDICTIONARY_CLIENT_ENGINE_H

/**
 * Generate JSON req to set value
 *
 * @param key key to store
 * @param value value to store
 * @param req_str (out) JSON request string
 *
 * @return error code
 */
int client_set(char *key, char *value, char **req_str);

/**
 * Generate JSON req to get value
 *
 * @param key key to store
 * @param req_str (out) JSON request string
 *
 * @return error code
 */
int client_get(char *key, char **req_str);

/**
 * Generate JSON req to get server stats
 *
 * @param req_str (out) JSON request string
 */
void client_stats(char **req_str);

#endif //REMOTEDICTIONARY_CLIENT_ENGINE_H
