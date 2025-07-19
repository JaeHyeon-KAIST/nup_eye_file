#include <LilyGo_RGBPanel.h>
#include <lvgl.h>
#include <LV_Helper.h>
#include <ui.h>
#include <TFT_eSPI.h>

LilyGo_RGBPanel panel;
TFT_eSPI tft = TFT_eSPI(); 

// 애니메이션 전환 함수들
void showGIF0() {
    lv_obj_clear_flag(uic_eye0, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye3, LV_OBJ_FLAG_HIDDEN);
    EyeAni0_Animation(uic_eye0, 0);
    if (Serial) Serial.println("GIF0 shown");
}

void showGIF1() {
    lv_obj_clear_flag(uic_eye1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye0, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye3, LV_OBJ_FLAG_HIDDEN);
    EyeAni1_Animation(uic_eye1, 0);
    if (Serial) Serial.println("GIF1 shown");
}

void showGIF2() {
    lv_obj_clear_flag(uic_eye2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye0, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye3, LV_OBJ_FLAG_HIDDEN);
    EyeAni2_Animation(uic_eye2, 0);
    if (Serial) Serial.println("GIF2 shown");
}

void showIMG3() {
    lv_obj_clear_flag(uic_eye3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye0, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(uic_eye2, LV_OBJ_FLAG_HIDDEN);
    if (Serial) Serial.println("IMG3 shown");
}

// 단일 키 입력 즉시 처리
void handleSerialInput() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c == '0') {
            showGIF0();
        } else if (c == '1') {
            showGIF1();
        } else if (c == '2') {
            showGIF2();
        } else if (c == '3') {
            showIMG3();
        } else if (c != '\r' && c != '\n') {
            // 무의미한 키는 무시
            Serial.print("Unknown key: ");
            Serial.println(c);
            Serial.println("Valid keys: 1, 2, 3");
        }
    }
}

// void handleSerialInput() {
//     while (Serial.available()) {
//         int byteVal = Serial.read();  // 바이트 그대로 읽기

//         switch (byteVal) {
//             case 0:
//                 showGIF0();
//                 break;
//             case 1:
//                 showGIF1();
//                 break;
//             case 2:
//                 showGIF2();
//                 break;
//             case 3:
//                 showIMG3();
//                 break;
//             default:
//                 Serial.print("Unknown byte: ");
//                 Serial.println(byteVal);
//                 Serial.println("Valid bytes: 0, 1, 2, 3");
//                 break;
//         }
//     }
// }

void setup() {
    Serial.begin(115200);

    if (!panel.begin()) {
        while (1) {
            if (Serial) Serial.println("Error, failed to initialize T-RGB");
            delay(1000);
        }
    }

    beginLvglHelper(panel);
    ui_init();
    lv_task_handler();

    panel.setBrightness(16);

    showGIF0();  // 기본 GIF0 실행

    if (Serial) Serial.println("Ready. Press '1', '2', or '3' — no ENTER needed.");
}

void loop() {
    lv_task_handler();
    handleSerialInput();
    delay(5);
}