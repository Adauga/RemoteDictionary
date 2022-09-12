#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <unistd.h>
#include <string.h>
#include <error_codes.h>
#include <client_engine.h>

static void on_close(uv_handle_t* handle);
static void on_connect(uv_connect_t* req, int status);
static void on_write(uv_write_t* req, int status);

static uv_loop_t *loop;
uv_connect_t *pConn = NULL;
uv_stream_t* stream = NULL;

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

char* rand_string_alloc(size_t size)
{
    char *s = malloc(size + 1);
    if (s) {
        rand_string(s, size);
    }
    return s;
}

static void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
    *buf = uv_buf_init(malloc(size), size);
}

void on_close(uv_handle_t* handle)
{
    printf("closed.");
}

void on_write(uv_write_t* req, int status)
{
    if (status) {
        perror( "uv_write error ");
        return;
    }
    printf("wrote.\n");
    free(req);
}

void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
    printf("on_read. %p\n",tcp);

    if(nread >= 0) {
        //printf("read: %s\n", tcp->data);

        printf("read: %s\n", buf->base);
        uv_close((uv_handle_t*)tcp, on_close);
    }
    else {
        uv_close((uv_handle_t*)tcp, on_close);
    }

    free(buf->base);
}

void write_req(uv_stream_t* stream, char *data, int len) {
    uv_buf_t buffer[] = {
            {.base = data, .len = len}
    };

    uv_write_t *req = malloc(sizeof(uv_write_t));
    uv_write(req, stream, buffer, 1, on_write);
}

void on_connect(uv_connect_t* connection, int status)
{
    if (status < 0) {
        printf("failed to connect\n"); return;
    }
    printf("connected. %p %d\n",connection, status);

    char *key = rand_string_alloc(rand() % 30);
    char *value = rand_string_alloc(rand() % 30);
    char *req_buf_set = NULL;

    client_set(key, value, &req_buf_set);

    uv_stream_t* stream = connection->handle;
    free(connection);
    write_req(stream, req_buf_set, strlen(req_buf_set));
    uv_read_start(stream, alloc_cb, on_read);
}

void client_connect(char *host, int port) {
    loop = uv_default_loop();
    uv_tcp_t *pSock = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, pSock);
    uv_tcp_keepalive(pSock, 1, 60);

    struct sockaddr_in dest;
    uv_ip4_addr(host, port, &dest);

    pConn = malloc(sizeof(uv_connect_t));
    printf("allocated %p\n", pConn);
    uv_tcp_connect(pConn, pSock, (const struct sockaddr*)&dest, on_connect);
    uv_run(loop, UV_RUN_DEFAULT);
}