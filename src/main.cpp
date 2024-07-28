#include <M5StickCPlus2.h>

M5Canvas canvas(&M5.Lcd);

#define LED 19 // 本体LED

void setup()
{
    auto cfg = M5.config(); // 本体初期化
    StickCP2.begin(cfg);

    // 出力設定
    pinMode(LED, OUTPUT);   // 本体LED赤
    digitalWrite(LED, LOW); // 本体LED初期値OFF（LOW）

    gpio_pulldown_dis(GPIO_NUM_25);
    gpio_pullup_dis(GPIO_NUM_25);

    M5.Lcd.setRotation(0);
    M5.Lcd.setTextSize(1);

    canvas.setTextWrap(false);
    canvas.createSprite(M5.Lcd.width(), M5.Lcd.height());
}

void loop()
{
    M5.update(); // 本体ボタン状態更新
    M5.Lcd.fillScreen(BLACK);

    canvas.setFont(&fonts::lgfxJapanGothicP_16);
    canvas.setCursor(30, 110);

    if (M5.BtnA.isPressed())
    {
        // SerialBT.println("1");

        canvas.setTextColor(ORANGE, BLACK); // 文字色指定(文字色, 背景)
        canvas.print("とまります");
        canvas.startWrite();
        canvas.drawRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), ORANGE);
        canvas.endWrite();
        canvas.pushSprite(&M5.Lcd, 0, 0);
        digitalWrite(LED, HIGH);
        tone(GPIO_NUM_2, 1318.510, 400); // 4000Hzを1000ms(1秒)
        delay(500);
        tone(GPIO_NUM_2, 1046.502, 650); // 4000Hzを1000ms(1秒)
    }
    else
    {
        digitalWrite(LED, LOW);
    }
    if (M5.BtnB.isPressed())
    {
        canvas.startWrite();
        canvas.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), BLACK);
        canvas.endWrite();
        canvas.pushSprite(&M5.Lcd, 0, 0);
    }

    canvas.pushSprite(&M5.Lcd, 0, 0);
    delay(10);
}