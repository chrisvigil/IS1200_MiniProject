/* Declare init function */
void init(void);
void display_init(void);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void quicksleep(int cyc);
extern const uint8_t const displaydata[128];
extern const uint8_t const displaydata2[256];
extern const uint8_t const displaydata3[512];
void work(void);
void stage1_int(void);
void stage1_work(void);
int stage;
void draw_point(uint8_t x, uint8_t y, uint8_t *cframe);
int getbtns( void );
extern const uint8_t const number[40];
//void data_init(void);
