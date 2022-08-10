#include <M5Stack.h>
#include <math.h>

int16_t WIDTH;
int16_t HEIGHT;
int t = 0;

void setup()
{
  M5.begin();

  WIDTH = M5.Lcd.width();
  HEIGHT = M5.Lcd.height();

  M5.Lcd.fillCircle(100, 100, 70, TFT_WHITE);
  M5.Lcd.fillCircle(110, 110, 70, TFT_RED);
  M5.Lcd.fillCircle(120, 120, 70, TFT_ORANGE);
  M5.Lcd.fillCircle(130, 130, 70, TFT_YELLOW);
  M5.Lcd.fillCircle(140, 140, 70, TFT_GREENYELLOW);
  M5.Lcd.fillCircle(150, 150, 70, TFT_GREEN);
  M5.Lcd.fillCircle(160, 160, 70, TFT_BLUE);
  M5.Lcd.fillCircle(170, 170, 70, TFT_NAVY);
  M5.Lcd.fillCircle(180, 180, 70, TFT_PURPLE);
  M5.Lcd.fillCircle(190, 190, 70, TFT_MAROON);
  M5.Lcd.drawString("Hello, World!", 150, 100);

  M5.Lcd.printf("(%d, %d)", WIDTH, HEIGHT);
}

void loop()
{
  for (uint32_t x = 0; x < WIDTH; x++)
  {
    for (uint32_t y = 0; y < HEIGHT; y++)
    {
      double_t u = 1. * x / WIDTH;
      double_t v = 1. * y / HEIGHT;

      uint32_t color = M5.Lcd.color565(255 * u, 255 * v, t % 256);

      M5.Lcd.fillRect(x, y, 1, 1, color);
    }
  }

  t++;
}
