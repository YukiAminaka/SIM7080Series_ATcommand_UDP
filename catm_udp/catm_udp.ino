#include <Arduino.h>

bool sendATCommand(const char* command ,int delay_time = 500) {
  Serial1.write(command);
  delay(delay_time);
  unsigned long startTime = millis();
  String response = "";  // 応答を蓄積するための文字列バッファ
  
  while (Serial1.available()) {
    
    char c = Serial1.read();
    response += c;  // 応答をバッファに追加
    Serial.print(c);  // デバッグのためにシリアルモニタに出力

    
    if (response.indexOf("ERROR") != -1) {
      Serial.println();
      return false;  // 失敗
    }
    if (response.indexOf("OK") != -1) {
      Serial.println();
      return true;  // 成功
    }
  }
  
  Serial.println();
  return true;
}

void serial_send(String data) {

  char command[100];
  sprintf(command,"%s%d%s","AT+CASEND=0,",data.length(),"\r\n");
  if (!sendATCommand(command)){
    Serial.println("Error: AT+CASEND");
  }

  if (!sendATCommand(data.c_str(),1000)){
    Serial.println("Error: Data could not be sent");
  }

  if (!sendATCommand("AT+CAACK=0\r\n")) {
    Serial.println("Error: AT+CAACK=0");
  }

  if (!sendATCommand("AT+CARECV=0,100\r\n")) {
    Serial.println("Error: AT+CARECV");
  }
  
  Serial.println("done");
}



// bool sendATCommand(const char* command) {
//   Serial1.write(command);
//   delay(3500);  // 応答を待つための適切な遅延を設定

//   while (Serial1.available()) {
//     char response = Serial1.read();
//     Serial.print(response);

//     // エラーチェック
//     if (strstr(&response, "ERROR") != NULL) {
//       return false;  // エラーが検出された場合
//     }
//   }

//   return true;  // エラーがなかった場合
// }



void setup() {
  Serial.begin(115200);
  Serial1.begin(115200,SERIAL_8N1,D7,D6);  // ATコマンドシリアル

  if (!sendATCommand("AT+CNACT=0,0\r\n")) {
    Serial.println("Error: AT+CNACT");
  }

  if (!sendATCommand("AT+CGDCONT=1,\"IP\",\"soracom.io\"\r\n")) {
    Serial.println("Error: AT+CGDCONT=1,\"IP\",\"soracom.io\"");
  }

  if (!sendATCommand("AT+CGDCONT?\r\n")) {
    Serial.println("Error: AT+CGDCONT?");
  }

  if (!sendATCommand("AT+CFUN=1\r\n")) {
    Serial.println("Error: AT+CFUN=1");
  }

  if (!sendATCommand("AT+CGATT=1\r\n")) {
    Serial.println("Error: AT+CGATT?");
  }

  if (!sendATCommand("AT+CGATT?\r\n")) {
    Serial.println("Error: AT+CGATT?");
  }

  if (!sendATCommand("AT+CGACT=1,1\r\n")) {
    Serial.println("Error: AT+CGACT=?");
  }

  if (!sendATCommand("AT+CGACT=?\r\n")) {
    Serial.println("Error: AT+CGACT=?");
  }


  if (!sendATCommand("AT+CPIN?\r\n")) {
    Serial.println("Error: AT+CPIN");
  }

  if (!sendATCommand("AT+CSQ\r\n")) {
    Serial.println("Error: AT+CSQ");
  }

  if (!sendATCommand("AT+CASTATE?\r\n")) {
    Serial.println("Error: AT+CASTATE?");
  }

  if (!sendATCommand("AT+COPS?\r\n")) {
    Serial.println("Error: AT+COPS?");
  }

  if (!sendATCommand("AT+CGNAPN\r\n")) {
    Serial.println("Error: AT+CGNAPN");
  }
  
  if (!sendATCommand("AT+CNCFG=0,1,\"soracom.io\" \r\n")) {
    Serial.println("Error: AT+CNCFG=0,1,\"soracom.io\" ");
  }

  if (!sendATCommand("AT+CNCFG?\r\n")) {
    Serial.println("Error: AT+CNCFG?");
  }

  if (!sendATCommand("AT+CNACT=0,1\r\n")) {
    Serial.println("Error: AT+CNACT");
  }

  if (!sendATCommand("AT+CNACT?\r\n")) {
    Serial.println("Error: AT+CNACT?");
  }
  
  if (!sendATCommand("AT+CACID=0\r\n")) {
    Serial.println("Error: AT+CACID=0");
  }

  if (!sendATCommand("AT+CACID?\r\n")) {
    Serial.println("Error: AT+CACID?");
  }

  if (!sendATCommand("AT+CASSLCFG=0,\"SSL\",0\r\n")) {
    Serial.println("Error: AT+CASSLCFG?");
  }

  if (!sendATCommand("AT+CAOPEN=0,0,\"UDP\",\"harvest.soracom.io\",8514\r\n")) {
    Serial.println("Error: AT+CAOPEN");
  }

}

void loop() {
    String data_sample = "{ \"a\" : \"1\" }";
    serial_send(data_sample);
    delay(500);
}