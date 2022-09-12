#include "client.h"

static void utest_client(void)
{
    char *host = "127.0.0.1";
    int port = 7000;


    for (int i = 0; i < 1000; i++) {
        client_connect(host, port);
    }
}

int main()
{
    utest_client();
}