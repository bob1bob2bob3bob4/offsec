

#include <iostream>
#include <Windows.h>
#include <winerror.h>


typedef struct
{
    unsigned int i;
    unsigned int j;
    unsigned char s[256];
} Rc4Context;


int RC4Init(Rc4Context* context, const unsigned char* key, size_t length)
{
    unsigned int i;
    unsigned int j;
    unsigned char temp;

    if (context == NULL || key == NULL)
        return ERROR_INVALID_PARAMETER;

    context->i = 0;
    context->j = 0;

    for (i = 0; i < 256; i++)
    {
        context->s[i] = i;
    }

    for (i = 0, j = 0; i < 256; i++)
    {
        j = (j + context->s[i] + key[i % length]) % 256;
        temp = context->s[i];
        context->s[i] = context->s[j];
        context->s[j] = temp;
    }
}

void RC4Cipher(Rc4Context* context, const unsigned char* input, unsigned char* output, size_t length)
{
    unsigned char temp;
    unsigned int i = context->i;
    unsigned int j = context->j;
    unsigned char* s = context->s;

    while (length > 0)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        if (input != NULL && output != NULL)
        {
            *output = *input ^ s[(s[i] + s[j]) % 256];
            input++;
            output++;
        }
        length--;

    }
    context->i = i;
    context->j = j;

}

int main()
{

    //RC4 encrpytion
    Rc4Context ctx = { 0 };
    const unsigned char plaintext[] = "c2 : 127.0.0.1";
    unsigned char ciphertext[sizeof(plaintext)];
    size_t length = sizeof(plaintext) - 1;

    unsigned char key[] = "william123";
    RC4Init(&ctx, key, sizeof(key));
    RC4Cipher(&ctx, plaintext, ciphertext, length);


    //RC4 decryption
    unsigned char outputtext[sizeof(ciphertext)];
    Rc4Context ctx1 = { 0 };
    RC4Init(&ctx1, key, sizeof(key));
    RC4Cipher(&ctx1, ciphertext, outputtext, sizeof(ciphertext));

    size_t len = sizeof(outputtext) - 1;

    for (size_t i = 0; i < len; ++i) {
        std::cout << outputtext[i];
    }
    std::cout << std::endl;
}
