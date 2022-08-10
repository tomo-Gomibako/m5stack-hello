#include <M5Stack.h>
#include <math.h>

const int16_t CELL_WIDTH = 32;
const int16_t CELL_HEIGHT = 24;

int16_t WIDTH;
int16_t HEIGHT;
int t = 0;

struct Cell
{
  u_int16_t x;
  u_int16_t y;
  bool alive;
  bool alive_next;
};

Cell cell_map[CELL_WIDTH][CELL_HEIGHT];

void setup()
{
  M5.begin();

  WIDTH = M5.Lcd.width();   // 320
  HEIGHT = M5.Lcd.height(); // 240

  // M5.Lcd.printf("(%d, %d)", WIDTH, HEIGHT);

  for (uint16_t cx = 0; cx < CELL_WIDTH; cx++)
  {

    for (uint16_t cy = 0; cy < CELL_HEIGHT; cy++)
    {
      cell_map[cx][cy] = {
          cx,
          cy,
          bool(random() % 2),
          false};
    }
  }
}

void loop()
{
  uint16_t lw = WIDTH / CELL_WIDTH;
  uint16_t lh = HEIGHT / CELL_HEIGHT;

  // draw & calc next state
  for (uint16_t cx = 0; cx < CELL_WIDTH; cx++)
  {

    for (uint16_t cy = 0; cy < CELL_HEIGHT; cy++)
    {
      uint32_t color = TFT_BLACK;
      int8_t alive_cells_around = 0;

      // 1 2 3
      // 4 _ 5
      // 6 7 8

      if (cx > 0 && cy > 0 && cell_map[cx - 1][cy - 1].alive) // 1
      {
        alive_cells_around++;
      }
      if (cy > 0 && cell_map[cx][cy - 1].alive) // 2
      {
        alive_cells_around++;
      }
      if (cx < CELL_WIDTH - 1 && cy > 0 && cell_map[cx + 1][cy - 1].alive) // 3
      {
        alive_cells_around++;
      }
      if (cx > 0 && cell_map[cx - 1][cy].alive) // 4
      {
        alive_cells_around++;
      }
      if (cx < CELL_WIDTH - 1 && cell_map[cx + 1][cy].alive) // 5
      {
        alive_cells_around++;
      }
      if (cx > 0 && cy < CELL_HEIGHT - 1 && cell_map[cx - 1][cy + 1].alive) // 6
      {
        alive_cells_around++;
      }
      if (cy < CELL_HEIGHT - 1 && cell_map[cx][cy + 1].alive) // 7
      {
        alive_cells_around++;
      }
      if (cx < CELL_WIDTH - 1 && cy < CELL_HEIGHT - 1 && cell_map[cx + 1][cy + 1].alive) // 8
      {
        alive_cells_around++;
      }

      if (cell_map[cx][cy].alive)
      {
        color = TFT_GREEN;

        if (alive_cells_around < 2 || 3 < alive_cells_around)
        {
          cell_map[cx][cy].alive_next = false;
        }
      }
      else
      {
        color = TFT_BLACK;

        if (alive_cells_around == 3)
        {
          cell_map[cx][cy].alive_next = true;
        }
      }

      M5.Lcd.drawRect(cx * lw, cy * lh, lw, lh, color);
    }
  }

  // update state
  for (uint16_t cx = 0; cx < CELL_WIDTH; cx++)
  {

    for (uint16_t cy = 0; cy < CELL_HEIGHT; cy++)
    {
      cell_map[cx][cy].alive = cell_map[cx][cy].alive_next;
    }
  }

  delay(250);
  t++;
}
