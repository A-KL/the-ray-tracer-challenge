#pragma once

enum epd_mode_t : int
{
  epd_quality = 1,
  epd_text    = 2,
  epd_fast    = 3,
  epd_fastest = 4,
};

class TFT_eSPI_T_HMI_Display : public TFT_eSPI
{
  public:
    TFT_eSPI_T_HMI_Display()
    {
      pinMode(PWR_EN_PIN, OUTPUT);
      digitalWrite(PWR_EN_PIN, HIGH);

      pinMode(PWR_ON_PIN, OUTPUT);
      digitalWrite(PWR_ON_PIN, HIGH);

      pinMode(TFT_BLK_PIN, OUTPUT);
      digitalWrite(TFT_BLK_PIN, HIGH);
    }

    inline void display()
    { }

    inline bool isEPD() {
      return false;
    }

    inline void setEpdMode(epd_mode_t epd_mode)
    {}
};
