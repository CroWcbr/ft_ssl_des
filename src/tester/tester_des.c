#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include <unistd.h>

//openssl
char	*openssl_base64(const char mode, const char *b64_encode_this, const size_t encode_this_many_bytes, size_t *out_len);
char	*openssl_base64_encode(const char *b64_encode_this, const size_t encode_this_many_bytes, size_t *out_len);
char	*openssl_base64_decode(const char *b64_decode_this, const size_t decode_this_many_bytes, size_t *out_len);

//my
char	*base64_main(const char mode, const char *input, const size_t inp_len, size_t *out_len);

//teste base 64
static void	tester_base64(char *cmd, char mode, int test, int print, \
					char *(*openssl_base64)(const char, const char *, const size_t, size_t *), \
					char *(*my_base64)(const char, const char *, const size_t, size_t *))
{
	int			err;
	char		str[test];
	char		*resylt_os;
	char		*resylt_my;
	size_t		out_len_os = 0;
	size_t		out_len_my = 0;
	int		random;
	char		b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	err = 0;
	for (int i = 0; i <= test; i++)
		str[i] = 0;
	for (int i = 0; i < test; i++)
	{
		if (mode == 'E')
		{
			random = rand() % 128;
			str[i] = random;
		}
		else // mode == 'D'
		{
			random = rand() % 64;
			str[i] = b64[random];
		}

		resylt_os = openssl_base64(mode, str, i, &out_len_os);
		resylt_my = my_base64(mode, str, i, &out_len_my);

		if (print == 1)
		{
			printf("%ld vs %ld\n", out_len_os, out_len_my);
			printf("%d\t", i);
			for (int ii = 0; ii < i; ii++)
				printf("%02x ", str[ii]);
			printf("\n");

			printf("%s openssl: \t", cmd);
			printf("|%s|", resylt_os);
			printf("\n");

			printf("%s my func: \t", cmd);
			printf("|%s|", resylt_my);
			printf("\n");
		}
		if (out_len_os != out_len_my)
		{
			err++;
			if (print == 0)
				;
			else
				exit(0);
		}
		else
		{
			for (size_t j = 0; j < out_len_os; j++)
				if (resylt_os[j] != resylt_my[j])
				{
					err++;
					if (print == 0)
						break ;
					else
						exit(0);
				}
		}
		free(resylt_os);
		free(resylt_my);
	}
	printf("-------------------------------------\n");
	printf("\tError in test %s %c: %d\n", cmd, mode, err);
	printf("-------------------------------------\n");
}

static void	tester_base64_full_random(char *cmd, char mode, int test, int str_len_test, int print, \
					char *(*openssl_base64)(const char, const char *, const size_t, size_t *), \
					char *(*my_base64)(const char, const char *, const size_t, size_t *))
{
	int			err;
	char		*str;
	char		*resylt_os;
	char		*resylt_my;
	size_t		out_len_os = 0;
	size_t		out_len_my = 0;
	int			random;
	int			random_char;
	char		b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	err = 0;
	for (int i = 0; i < test; i++)
	{
		if (mode == 'E')
			random = rand() % str_len_test;
		else
			random = (rand() % str_len_test) / 4 * 4;
		str = (char *)malloc((random + 1) * sizeof(char));
		str[random] = 0;
		for (int j = 0; j < random; j++)
		{
			if (mode == 'E')
			{
				random_char = rand() % 128;
				str[j] = random_char;
			}
			else
			{
				random_char = rand() % 64;
				str[j] = b64[random_char];
			}
		}

		resylt_os = openssl_base64(mode, str, random, &out_len_os);
		resylt_my = my_base64(mode, str, random, &out_len_my);

		if (print == 1)
		{
			printf("%ld vs %ld\n", out_len_os, out_len_my);
			printf("%d\t", i);
			for (int ii = 0; ii < random; ii++)
				printf("%c", str[ii]);
			printf("\n");

			printf("%s openssl: \t", cmd);
			printf("|%s|", resylt_os);
			printf("\n");

			printf("%s my func: \t", cmd);
			printf("|%s|", resylt_my);
			printf("\n");
		}
		if (out_len_os != out_len_my)
		{
			err++;
			if (print == 0)
				;
			else
				exit(0);
		}
		else
		{
			for (size_t j = 0; j < out_len_os; j++)
				if (resylt_os[j] != resylt_my[j])
				{
					err++;
					if (print == 0)
						break ;
					else
						exit(0);
				}
		}
		free(resylt_os);
		free(resylt_my);
	}
	printf("-------------------------------------\n");
	printf("\tError in test %s %c: %d\n", cmd, mode, err);
	printf("-------------------------------------\n");
}

char	*openssl_base64(const char mode, const char *b64_encode_this, const size_t encode_this_many_bytes, size_t *out_len)
{
	char	*result;

	if (mode == 'E')
		result = openssl_base64_encode(b64_encode_this, encode_this_many_bytes, out_len);
	else
		result = openssl_base64_decode(b64_encode_this, encode_this_many_bytes, out_len);
	return (result);
}

char	*openssl_base64_encode(const char *b64_encode_this, const size_t encode_this_many_bytes, size_t *out_len)
{
	BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
	BUF_MEM *mem_bio_mem_ptr;    //Pointer to a "memory BIO" structure holding our base64 data.
	b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
	mem_bio = BIO_new(BIO_s_mem());                           //Initialize our memory sink BIO.
	BIO_push(b64_bio, mem_bio);            //Link the BIOs by creating a filter-sink BIO chain.
	// BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);  //No newlines every 64 characters or less.
	BIO_write(b64_bio, b64_encode_this, encode_this_many_bytes); //Records base64 encoded data.
	BIO_flush(b64_bio);   //Flush data.  Necessary for b64 encoding, because of pad characters.
	BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);  //Store address of mem_bio's memory structure.
	BIO_set_close(mem_bio, BIO_NOCLOSE);   //Permit access to mem_ptr after BIOs are destroyed.
	BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
	BUF_MEM_grow(mem_bio_mem_ptr, (*mem_bio_mem_ptr).length + 1);   //Makes space for end null.
	(*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] = '\0';  //Adds null-terminator to tail.
	*out_len = (*mem_bio_mem_ptr).length - 1;
	return (*mem_bio_mem_ptr).data; //Returns base-64 encoded data. (See: "buf_mem_st" struct).
}

char	*openssl_base64_decode(const char *b64_decode_this, const size_t decode_this_many_bytes, size_t *out_len)
{
	BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
	char *base64_decoded = calloc( (decode_this_many_bytes*3)/4+1, sizeof(char) ); //+1 = null.
	b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
	mem_bio = BIO_new(BIO_s_mem());                         //Initialize our memory source BIO.
	BIO_write(mem_bio, b64_decode_this, decode_this_many_bytes); //Base64 data saved in source.
	BIO_push(b64_bio, mem_bio);          //Link the BIOs by creating a filter-source BIO chain.
	BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);          //Don't require trailing newlines.
	*out_len = BIO_read(b64_bio, base64_decoded, decode_this_many_bytes); //Once we're done reading decoded data
	BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
	return base64_decoded;        //Returns base-64 decoded data with trailing null terminator.
}

int	main(void)
{
	int	test;
	int	str_len_test;
	int	print;

	test = 1000;
	str_len_test = 100000;
	print = 0;
	srand(time(NULL));

	tester_base64("base64", 'E', test, print, openssl_base64, base64_main);
	tester_base64("base64", 'D', test, print, openssl_base64, base64_main);
	tester_base64_full_random("base64 full random", 'E', test, str_len_test, print, openssl_base64, base64_main);
	tester_base64_full_random("base64 full random", 'D', test, str_len_test, print, openssl_base64, base64_main);
}