void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

/* ����д��ͬһ��Դ�ļ��������ڶ���ǰʹ�ã����Ǳ�����������һ�� */

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

void HariMain(void)
{
	int i; /* �ϐ��錾�Bi�Ƃ����ϐ��́A32�r�b�g�̐����^ */
	char *p; /* ����p��BYTE[...]�õĵ�ַ */

	init_palette(); /* �趨��ɫ�� */

	p = (char *) 0xa0000; /* ָ����ַ */

	for (i = 0; i <= 0xffff; i++) {
		p[i] = i & 0x0f;
	}

	for (;;) {
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:�� */
		0xff, 0x00, 0x00,	/*  1:���� */
		0x00, 0xff, 0x00,	/*  2:���� */
		0xff, 0xff, 0x00,	/*  3:���� */
		0x00, 0x00, 0xff,	/*  4:���� */
		0xff, 0x00, 0xff,	/*  5:���� */
		0x00, 0xff, 0xff,	/*  6:ǳ���� */
		0xff, 0xff, 0xff,	/*  7:�� */
		0xc6, 0xc6, 0xc6,	/*  8:���� */
		0x84, 0x00, 0x00,	/*  9:���� */
		0x00, 0x84, 0x00,	/* 10:���� */
		0x84, 0x84, 0x00,	/* 11:���� */
		0x00, 0x00, 0x84,	/* 12:���� */
		0x84, 0x00, 0x84,	/* 13:���� */
		0x00, 0x84, 0x84,	/* 14:ǳ���� */
		0x84, 0x84, 0x84	/* 15:���� */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* C�����е�static char ֻ���������ݣ��൱�ڻ���е�DBָ�� */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* ��¼�ж���ɵı�־ */
	io_cli(); 					/* ���ж���ɱ�־��Ϊ0����ֹ�ж� */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);	//��rgb[0]/4��Ϊʲô/4�����͵�0x03c9�˿�
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* ��ԭ�ж���ɱ�־ */
	return;
}
