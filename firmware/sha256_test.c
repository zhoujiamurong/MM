	/* Test sha256 core: 1 block data*/
uint8_t state[32];
const uint8_t sha256_in[] = {0x61, 0x62, 0x63};
const uint8_t sha256_in2[] = {
	0x61, 0x62, 0x63, 0x64, 0x62, 0x63, 0x64, 0x65,
	0x63, 0x64, 0x65, 0x66, 0x64, 0x65, 0x66, 0x67,
	0x65, 0x66, 0x67, 0x68, 0x66, 0x67, 0x68, 0x69,
	0x67, 0x68, 0x69, 0x6A, 0x68, 0x69, 0x6A, 0x6B,
	0x69, 0x6A, 0x6B, 0x6C, 0x6A, 0x6B, 0x6C, 0x6D,
	0x6B, 0x6C, 0x6D, 0x6E, 0x6C, 0x6D, 0x6E, 0x6F,
	0x6D, 0x6E, 0x6F, 0x70, 0x6E, 0x6F, 0x70, 0x71};
sha256(sha256_in, ARRAY_SIZE(sha256_in), state);
hexdump(state, 32);

/* The correct result is: */
/* ba 78 16 bf 8f 01 cf ea  41 41 40 de 5d ae 22 23 */
/* b0 03 61 a3 96 17 7a 9c  b4 10 ff 61 f2 00 15 ad */

/* echo -n ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad | xxd -r -p | sha256sum */


/* Test sha256 core: 2 block data*/
sha256(sha256_in2, ARRAY_SIZE(sha256_in2), state);
hexdump(state, 32);

/* The correct result is: */
/* 24 8d 6a 61 d2 06 38 b8  e5 c0 26 93 0c 3e 60 39 */
/* a3 3c e4 59 64 ff 21 67  f6 ec ed d4 19 db 06 c1 */

const uint8_t sha256_in3[] = {
	0x00, 0x00, 0x00, 0x02, 0xd5, 0xa0, 0xf8, 0xa5,
	0xb8, 0x2b, 0x43, 0xd5, 0x80, 0x90, 0xd4, 0x8d,
	0x41, 0xa0, 0x83, 0xe5, 0x71, 0x52, 0x80, 0x62,
	0xe8, 0xe3, 0xae, 0x5a, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x36, 0x9d, 0xab, 0x3f,
	0xbc, 0xe8, 0xd5, 0x4b, 0x23, 0xbf, 0xa1, 0xe4,
	0xdd, 0xd4, 0x3f, 0x5a, 0x92, 0x6e, 0x8a, 0x7a,
	0xcd, 0x1c, 0xc2, 0xa5, 0x35, 0x07, 0x30, 0xd2};

unsigned char data[64];
uint32_t *data32 = (uint32_t *)data;

flip64(data32, sha256_in3);

sha256_init();
sha256_update(data, 64);
sha256_final(state);

	/* FIXME: LM32 will crash if I direct use
	 * flip64(work->data, work->data);
	 */
memcpy(data, state, 32);
flip64(data32, data32);

hexdump(state, 32);
