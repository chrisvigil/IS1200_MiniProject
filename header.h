void user_isr(void);

// Declaration of init functions
void system_init(void);
void oledhost_init(void);
void btn_init(void);
void interupt_init(void);
void i2c_init(void);
void init(void);

// Deceleration of const data (numbers and letters)
extern const uint8_t const number[40];
extern const uint8_t const letter[104];

// Display functions
uint8_t spi_send_recv(uint8_t data);
void display_init(void);
void display_image(const uint8_t *data);
void draw_point(uint8_t x, uint8_t y, uint8_t *cframe);
void drawnumbers(int numbers, int start, int inv, uint8_t *frame, int offset);
int drawletter(char c, int start, uint8_t *frame, uint8_t shift);
void drawword(char *word, int start, uint8_t *frame, uint8_t shift, int len);

// Input functions
int getbtns( void );
void quicksleep(int cyc);

// Important global variables
int stage;
uint16_t temp_highscore;
uint8_t highscore_list[4][5];
uint8_t frame[512];
int highscore; // Keeps track of game sessions current best score
int adr_offset; // highscorelist offset

// main functions
void user_isr( void );
void read_highscores();
int main( void );

// Stage 0 - Main Menu
uint8_t pos_0;
void new_frame_0(void);
void stage0_int(void);

//Stage 1 - Game
uint8_t speed;
uint8_t pipespacing;
void random_pipes(void);
int pipe_collision(int pipe);
void scores(void);
int collision(void);
void new_frame_1(void);
void bird_reset(void);
void draw_pipe(uint8_t x_point, uint8_t y_point);
void draw (void);
void start(void);
void stage1_int(void);
void stage1_work(void);

//Stage 2 - Settings menu
uint8_t pos_2;
void new_frame_2(void);
void stage2_int(void);
void stage2_work(void);

//Stage 3 - Speed menu
void new_frame_3(void);
void stage3_int(void);
void stage3_work(void);

//Stage 4 - Info menu
uint8_t pos_4;
void new_frame_4(void);
void stage4_int(void);
void stage4_work(void);

//Stage 5 - Highscores menu
void new_frame_5(void);
void stage5_int(void);
void stage5_work(void);

//Stage 6 - Credits
void new_frame_6(void);
void stage6_int(void);
void stage6_work(void);

//Stage 7 - Spacing
void new_frame_7(void);
void stage7_int(void);
void stage7_work(void);

//Stage 8 - Highscore entry
uint8_t pos_8;
void new_frame_8(void);
int check_highscore(void);
void stage8_int(void);
void stage8_work(void);
