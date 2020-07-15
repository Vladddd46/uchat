#include "crypt.h"
#include <stdio.h>
#include "../libmx/inc/libmx.h"

int main() {
	char *msg = "Hello World";

	char *res = mx_rsa_encode(msg);
	printf("res = %s\n", res);

	char *decoded = mx_rsa_decode(res);
	printf(">%s\n", decoded);
}
