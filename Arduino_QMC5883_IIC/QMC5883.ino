#include <DFRobot_QMC5883.h>

DFRobot_QMC5883 compass(&Wire, 0x0D);

unsigned long lastUpdateTime = 0;  // 时间戳，用于跟踪上次更新的时间
unsigned long lastReportTime = 0;  // 记录上次报告时间
const unsigned long timeSlice = 10;  // 时间片为100毫秒
int countPerSecond = 0;  // 记录每秒的输出次数

void setup() {
  Wire.setPins(6, 7);
  Wire.begin();
  Serial.begin(9600);
  while (!compass.begin()) {
    Serial.println("Could not find a valid 5883 sensor, check wiring!");
    delay(500);
  }

  if (compass.isHMC()) {
    Serial.println("Initialize HMC5883");
  } else if (compass.isQMC()) {
    Serial.println("Initialize QMC5883");
  } else if (compass.isVCM()) {
    Serial.println("Initialize VCM5883L");
  }
  delay(1000);
}

void loop() {
  unsigned long currentTime = millis(); // 获取当前时间
  
  // 检查是否到达报告时间，即每秒钟
  if (currentTime - lastReportTime >= 1000) {
    Serial.print("Outputs per second: ");
    Serial.println(countPerSecond);
    countPerSecond = 0;  // 重置计数器
    lastReportTime = currentTime;
  }
  
  if (currentTime - lastUpdateTime >= timeSlice) { // 检查是否达到时间片
    lastUpdateTime = currentTime; // 更新时间戳
    
    float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
    compass.setDeclinationAngle(declinationAngle);
    sVector_t mag = compass.readRaw();
    compass.getHeadingDegrees();

    Serial.print("X:");
    Serial.print(mag.XAxis);
    Serial.print(" Y:");
    Serial.print(mag.YAxis);
    Serial.print(" Z:");
    Serial.println(mag.ZAxis);
    Serial.print("Degress = ");
    Serial.println(mag.HeadingDegress);

    countPerSecond++;  // 增加每秒输出的次数
  }
}
